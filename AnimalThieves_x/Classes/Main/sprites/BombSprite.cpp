//
//  BombSprite.cpp
//  AnimalThieves_x
//
//  Created by Zhang Baowen on 13-11-1.
//
//

#include "BombSprite.h"
#include "SimpleAudioEngine.h"
#include "AnimalThievesManager.h"
#include "Constants.h"
using namespace cocos2d;
static void handleCollisionRemove(cpSpace *space, cpShape *shape, void *data)
{
	cpSpaceRemoveBody(space, shape->body);
	cpSpaceRemoveShape(space, shape);
}



bool BombSprite::initWithFile(const char *filename)
{
    if (this == CCSprite::create(filename))
    {
        CCAnimation *burnAnimation = CCAnimation::create();
        burnAnimation->setDelayPerUnit(0.03f);
        for (int i = 1; i < 4; i++)
        {
            burnAnimation->addSpriteFrameWithFileName(CCString::createWithFormat("bomb_%d.png",i)->getCString());
        }
        CCAnimate* actionBurnAnimation = CCAnimate::create(burnAnimation);
        CCRepeatForever* actionBurnRepeat = CCRepeatForever::create(actionBurnAnimation);
        this->runAction(actionBurnRepeat);
	}
	return this;
}



void BombSprite::explode()
{
	cpSpaceAddPostStepCallback(space, (cpPostStepFunc)handleCollisionRemove, shape, NULL);
	this->setOpacity(0);
    
	CCSprite *explosion = CCSprite::create("explode_1.png");
	explosion->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height));
	this->addChild(explosion, 1);
	CCAnimation *explodeAnimation = CCAnimation::create();
	explodeAnimation->setDelayPerUnit(0.1f);
	for (int i = 1; i < 5; i++) {
        explodeAnimation->addSpriteFrameWithFileName(CCString::createWithFormat("explode_%d.png",i)->getCString());
	}
	CCAnimate* actionExplodeAnimation = CCAnimate::create(explodeAnimation);
	CCRepeat* actionExplodeRepeat = CCRepeat::create((CCFiniteTimeAction*)actionExplodeAnimation,1);
	CCCallFuncN* actionExplodeDone = CCCallFuncN::create(this, callfuncN_selector(BombSprite::removeExplosion));
	CCSequence* actionExplodeSeq = CCSequence::create(actionExplodeAnimation,actionExplodeRepeat);
	explosion->runAction(actionExplodeSeq);
}

void BombSprite::removeExplosion(void* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
    sprite->removeAllChildrenWithCleanup(true);
}