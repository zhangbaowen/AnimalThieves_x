//
//  MainGameScene.cpp
//  AnimalThieves_x
//
//  Created by Zhang Baowen on 13-11-1.
//
//
#include "AnimalThievesManager.h"
#include "SimpleAudioEngine.h"
#include "MainGameScene.h"
#include "Constants.h"
#include "BombSprite.h"
#include "AutoSprite.h"
#include "ThiefSprite.h"

using namespace cocos2d;
using namespace CocosDenshion;
enum{
	kTagFloorCollisionType = 0,
	kTagBorderBottomCollisionType = 1,
	kTagBorderSideCollisionType = 2,
	kTagDoorCollisionType = 3,
	kTagBombCollisionType = 4,
	kTagThiefCollisionType = 5,
	kTagGoldCollisionType = 6,
	kTagCageCollisionType = 7,
	kTagStaticCollisionType = 8,
	kTagAutoCollisionType = 9
};

static void eachShape(void *ptr, void *unused)
{
	cpShape *shape = (cpShape *)ptr;
	CCSprite *sprite = (CCSprite *)shape->data;
	if (sprite)
    {
		cpBody *body = shape->body;
		// TIP: cocos2d and chipmunk uses the same struct to store it's position
		// chipmunk uses: cpVect, and cocos2d uses CGPoint but in reality the are the same
		// since v0.7.1 you can mix them if you want.
		sprite->setPosition(CCPoint(body->p.x, body->p.y));
		sprite->setRotation((float)CC_RADIANS_TO_DEGREES(-body->a));
	}
  
}

static void handleCollisionWithBomb(cpArbiter *arb, struct cpSpace *space, void *data)
{
	CP_ARBITER_GET_SHAPES(arb, a, b);
	
	MainGame *game = (MainGame *)data;
	
	if ((a->collision_type == kTagFloorCollisionType || a->collision_type == kTagStaticCollisionType) && b->body->v.y < 75)
    {
		return;
	}
	
	if (AnimalThievesManager::sharedMannager()->getIsSoundStopped())
    {
        SimpleAudioEngine::sharedEngine()->playEffect(kExplodeSoundName);
	}
	
	bool isEnhanced = false;
	
	CCArray *bombSpritesToRemove = new CCArray();
    game->bombSprites->removeObject((BombSprite *)b->data);
    for (int i = 0; i < game->bombSprites->count(); i ++)
    {
        BombSprite* bombSprite = (BombSprite*)game->bombSprites->objectAtIndex(i);
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		float bottomY = MainGame::stageBottomY(AnimalThievesManager::sharedMannager()->getStage());
		float r = MainGame::stageBombThiefR(AnimalThievesManager::sharedMannager()->getStage());
		float dist;
		
		if (((dist = ccpDistance(ccp(bombSprite->shape->body->p.x, bombSprite->shape->body->p.y),
                                 ccp(b->body->p.x,b->body->p.y))) < r) && !(bombSprite->shape->body->p.y < winSize.height - bottomY))
        {
			isEnhanced = true;
            bombSprite->explode();
            bombSpritesToRemove->addObject(bombSprite);
		}
	}
    
    for (int i = 0; i < game->autoSprites->count(); i ++)
    {
        AutoSprite* autoSprite = (AutoSprite*)game->autoSprites->objectAtIndex(i);
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		float bottomY = MainGame::stageBottomY(AnimalThievesManager::sharedMannager()->getStage());
		float r = MainGame::stageBombAutoR(AnimalThievesManager::sharedMannager()->getStage());
		float f = MainGame::stageBombF(AnimalThievesManager::sharedMannager()->getStage());
		float dist;
		
		if (isEnhanced)
        {
			r += 128;
		}
		
		if (((dist = ccpDistance(ccp(autoSprite->shape->body->p.x,autoSprite->shape->body->p.y), ccp(b->body->p.x,b->body->p.y))) < r) && !(autoSprite->shape->body->p.y < winSize.height - bottomY))
        {
            autoSprite->shape->body->v.x = 0;
            autoSprite->shape->body->v.y = 0;
			CCPoint target = ccpSub(CCPoint(autoSprite->shape->body->p.x,autoSprite->shape->body->p.y), CCPoint(b->body->p.x,b->body->p.y));
            CGPoint p;
            p.x = target.x / dist * f;
            p.y = target.y / dist * f;
            
            cpBodyApplyImpulse(autoSprite->shape->body, p, cpvzero);
		}
	}
	
    for (int i = 0; i < game->thiefSprites->count(); i ++)
    {
        ThiefSprite* thiefSprite = (ThiefSprite*)game->thiefSprites->objectAtIndex(i);
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		float bottomY = MainGame::stageBottomY(AnimalThievesManager::sharedMannager()->getStage());
		float r = MainGame::stageBombThiefR(AnimalThievesManager::sharedMannager()->getStage());
		float dist;
		
		if (isEnhanced)
        {
			r += 128;
		}
		
		if (((dist = ccpDistance(ccp(thiefSprite->shape->body->p.x,thiefSprite->shape->body->p.y), ccp(b->body->p.x,b->body->p.y))) < r) && !(thiefSprite->shape->body->p.y < winSize.height - bottomY))
        {
            thiefSprite->die();
            AnimalThievesManager::sharedMannager()->setGameState(kGameStateOver);
            game->schedule(schedule_selector(MainGame::lost), 2.5);
		}
	}
    ((BombSprite*)b->data)->explode();
	game->bombSprites->removeObjectsInArray(bombSpritesToRemove);
	bombSpritesToRemove->release();
}

float MainGame::stageBottomY(int stage)
{
}

void MainGame::lost()
{
}

