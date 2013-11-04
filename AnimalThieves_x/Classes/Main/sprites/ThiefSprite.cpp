//
//  ThiefSprite.cpp
//  AnimalThieves_x
//
//  Created by Zhang Baowen on 13-11-4.
//
//

#include "ThiefSprite.h"

#include "ThiefSprite.h"
#include "SimpleAudioEngine.h"
#include "AnimalThievesManager.h"
#include "Constants.h"
using namespace cocos2d;
using namespace CocosDenshion;

#define kTagThiefFall 1
#define kTagThiefStruggle 2

static void handleCollisionRemove(cpSpace *space, cpShape *shape, void *data)
{
	cpSpaceRemoveBody(space, shape->body);
	cpSpaceRemoveShape(space, shape);
}

void ThiefSprite::setIsFalling(bool falling)
{
    isFalling = falling;
    
    if (isFalling)
    {
        this->setOpacity(0);
        
        CCSprite *thiefFall = (CCSprite *)this->getChildByTag(kTagThiefFall);
        thiefFall->setVisible(true);
    }
    else
    {
        if (isStruggling)
        {
            this->setOpacity(0);
        }
        else
        {
            this->setOpacity(255);
        }
        
        CCSprite *thiefFall = (CCSprite *)this->getChildByTag(kTagThiefFall);
        thiefFall->setVisible(false);
    }

}

void ThiefSprite::setIsStruggling(bool struggling)
{
    isStruggling = struggling;
    
    if (isStruggling)
    {
        this->setOpacity(0);
        
        CCSprite *thiefStruggle = (CCSprite *)this->getChildByTag(kTagThiefStruggle);
        thiefStruggle->setVisible(true);
    }
    else
    {
        if (isFalling)
        {
            this->setOpacity(0);
        }
        else
        {
            this->setOpacity(255);
        }
        
        CCSprite *thiefStruggle = (CCSprite *)this->getChildByTag(kTagThiefStruggle);
        thiefStruggle->setVisible(false);
    }

}


CCString*  ThiefSprite::thiefName(ThiefType t)
{
    CCString *name;
    switch (t) {
		case kThiefTypeRatel:
			name->createWithFormat("ratel");
			break;
		case kThiefTypePanda:
			name->createWithFormat("panda");
			break;
		case kThiefTypeEagle:
			name->createWithFormat("eagle");
			break;
		case kThiefTypeRabbit:
			name->createWithFormat("rabbit");
			break;
		case kThiefTypeBear:
			name->createWithFormat("bear");
			break;
		default:
			name->createWithFormat("bear");
			break;
	}
	
	return name;

}

void* ThiefSprite::spriteWithType(ThiefType t)
{
    return this->initWithType(t);
}

void* ThiefSprite::initWithType(ThiefType t)
{
    CCString *thiefImageName = CCString::createWithFormat("%s.png",this->thiefName(t)->getCString());
    if (this == CCSprite::create(thiefImageName->getCString()))
    {
        type = t;
        isFalling = false;
        isStruggling = false;
        this->addThiefAction();
        this->addFallAction();
        this->addStruggleAction();
    }
    return this;
}

void ThiefSprite::addThiefAction()
{
    int frameNum;
    int times;
    float delayTime;
    switch (type) {
		case kThiefTypeRatel:
            frameNum = 14;
			times = 3;
			delayTime = 1.5;
			break;
		case kThiefTypePanda:
            frameNum = 10;
			times = 3;
			delayTime = 3.0;
			break;
		case kThiefTypeEagle:
            frameNum = 10;
			times = 3;
			delayTime = 2.5;
			break;
		case kThiefTypeRabbit:
            frameNum = 10;
			times = 4;
			delayTime = 2.0;
			break;
		case kThiefTypeBear:
            frameNum = 10;
			times = 3;
			delayTime = 2.0;
			break;
		default:
            frameNum = 10;
			times = 3;
			delayTime = 2.0;
			break;
	}
    CCAnimation *thiefAnimation = CCAnimation::create();
    thiefAnimation->setDelayPerUnit(0.12f);
    for (int i = 0; i <= frameNum; i++)
    {
        thiefAnimation->addSpriteFrameWithFileName(CCString::createWithFormat("%s_%d.png",thiefName(type)->getCString(),i)->getCString());
    }
    thiefAnimation->addSpriteFrameWithFileName(CCString::createWithFormat("%s.png",thiefName(type)->getCString())->getCString());
    CCAnimate* actionThiefAnimation = CCAnimate::create(thiefAnimation);
    CCCallFunc* actionThiefSound = CCCallFunc::create(this, callfunc_selector(ThiefSprite::playThiefSound));
	CCSequence* actionThiefSeq = CCSequence::create(actionThiefSound,actionThiefAnimation,nil);
    CCRepeat* actionThiefRepeat = CCRepeat::create(actionThiefSeq, times);
    
    int times1;
	float delayTime1;
    
    switch (type)
    {
		case kThiefTypeRatel:
			times1 = 4;
			delayTime1 = 1.3;
			break;
		case kThiefTypePanda:
			times1 = 4;
			delayTime1 = 1.1;
			break;
		case kThiefTypeEagle:
			times1 = 4;
			delayTime1 = 1.7;
			break;
		case kThiefTypeRabbit:
			times1 = 4;
			delayTime1 = 1.9;
			break;
		case kThiefTypeBear:
			times1 = 4;
			delayTime1 = 1.5;
			break;
		default:
			times1 = 4;
			delayTime1 = 1.5;
			break;
	}

    
    
    CCAnimation *originAnimation = CCAnimation::create();
    originAnimation->setDelayPerUnit(0.12f);
    for (int i = 1; i < 8; i++)
    {
        originAnimation->addSpriteFrameWithFileName(CCString::createWithFormat("%sOrigin_%d.png",thiefName(type)->getCString(),i)->getCString());
    }
    CCAnimate* actionOriginAnimation = CCAnimate::create(originAnimation);
    CCCallFunc* actionOriginSound = CCCallFunc::create(this, callfunc_selector(ThiefSprite::playOriginSound));
    CCDelayTime* actionOriginDelay = CCDelayTime::create(delayTime1);
	CCSequence* actionOriginSeq = CCSequence::create(actionOriginSound,actionOriginAnimation,actionOriginDelay,nil);
    CCRepeat* actionOriginRepeat = CCRepeat::create(actionOriginSeq, times1);
    
    CCDelayTime* actionThiefDelay = CCDelayTime::create(delayTime);
    CCSequence* actionThiefSeq1 = CCSequence::create(actionThiefRepeat,actionOriginRepeat,actionThiefDelay,nil);
    CCRepeatForever* actionThiefRepeatForever = CCRepeatForever::create(actionThiefSeq1);
    this->runAction(actionThiefRepeatForever);
}

void ThiefSprite::addFallAction()
{
    CCSprite *thiefFall = CCSprite::create(CCString::createWithFormat("%sFall_1.png",thiefName(type)->getCString())->getCString());
	thiefFall->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().width / 2));
    this->addChild(thiefFall, 1, kTagThiefFall);
    thiefFall->setVisible(false);
	
	CCAnimation *fallAnimation = CCAnimation::create();
	fallAnimation->setDelayPerUnit(0.12f);
	for (int i = 1; i < 3; i++)
    {
		fallAnimation->addSpriteFrameWithFileName(CCString::createWithFormat("%sFall_%d.png", thiefName(type)->getCString(), i)->getCString());
	}
	CCAnimate* actionFallAnimation = CCAnimate::create(fallAnimation);
	CCRepeatForever* actionFallRepeatForever = CCRepeatForever::create(actionFallAnimation);
	thiefFall->runAction(actionFallRepeatForever);
}

void ThiefSprite::addStruggleAction()
{
    CCSprite *thiefStruggle = CCSprite::create(CCString::createWithFormat("%sStruggle_1.png",thiefName(type)->getCString())->getCString());
    thiefStruggle->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().width / 2));
    this->addChild(thiefStruggle, 1, kTagThiefStruggle);
    thiefStruggle->setVisible(false);
	
    CCAnimation *struggleAnimation = CCAnimation::create();
	struggleAnimation->setDelayPerUnit(0.12f);
	for (int i = 1; i < 4; i++)
    {
        struggleAnimation->addSpriteFrameWithFileName(CCString::createWithFormat("%sStruggle_%d.png", thiefName(type)->getCString(), i)->getCString());
	}
	CCAnimate* actionStruggleAnimation = CCAnimate::create(struggleAnimation);
    CCCallFunc* actionStruggleSound = CCCallFunc::create(this, callfunc_selector(ThiefSprite::playStruggleSound));
    CCSequence* actionStruggleSeq = CCSequence::create(actionStruggleSound, actionStruggleAnimation, nil);
	CCRepeat* actionStruggleRepeat = CCRepeat::create(actionStruggleSeq, 4);
	
    int times;
	CGFloat delayTime;
    
    switch (type) {
		case kThiefTypeRatel:
			times = 4;
			delayTime = 1.3;
			break;
		case kThiefTypePanda:
			times = 4;
			delayTime = 1.1;
			break;
		case kThiefTypeEagle:
			times = 4;
			delayTime = 1.7;
			break;
		case kThiefTypeRabbit:
			times = 4;
			delayTime = 1.9;
			break;
		case kThiefTypeBear:
			times = 4;
			delayTime = 1.5;
			break;
		default:
			times = 4;
			delayTime = 1.5;
			break;
	}
    
    CCAnimation* cageAnimation = CCAnimation::create();
    cageAnimation->setDelayPerUnit(0.12f);
    for (int i = 1; i < 8; i++)
    {
        cageAnimation->addSpriteFrameWithFileName(CCString::createWithFormat("%sCage_%d.png", thiefName(type)->getCString(), i)->getCString());
	}

	CCAnimate* actionCageAnimation = CCAnimate::create(cageAnimation);
    CCCallFunc* actionCageSound = CCCallFunc::create(this, callfunc_selector(ThiefSprite::playCageSound));
    CCDelayTime* actionCageDelay = CCDelayTime::create(delayTime);
    CCSequence* actionCageSeq = CCSequence::create(actionCageSound, actionCageAnimation, actionCageDelay, nil);
	CCRepeat* actionCageRepeat = CCRepeat::create(actionCageSeq,times);
    CCSequence* actionStruggleCageSeq = CCSequence::create(actionStruggleRepeat, actionCageRepeat, nil);
    CCRepeatForever* actionStruggleCageRepeatForever = CCRepeatForever::create(actionStruggleCageSeq);
    thiefStruggle->runAction(actionStruggleCageRepeatForever);
}


void ThiefSprite::playThiefSound()
{
    if (!AnimalThievesManager::sharedMannager()->getIsSoundStopped() && AnimalThievesManager::sharedMannager()->getGameState() != kGameStateOver && !isFalling && !isStruggling)
    {
        SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat(kThiefSoundName,thiefName(type)->getCString())->getCString());
    }
}

void ThiefSprite::playOriginSound()
{
    if (!AnimalThievesManager::sharedMannager()->getIsSoundStopped() && AnimalThievesManager::sharedMannager()->getGameState() != kGameStateOver && !isFalling && !isStruggling)
    {
        SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat(kOriginSoundName,thiefName(type)->getCString())->getCString());
    }
}

void ThiefSprite::playStruggleSound()
{
    if (!AnimalThievesManager::sharedMannager()->getIsSoundStopped() && AnimalThievesManager::sharedMannager()->getGameState() != kGameStateOver && !isFalling && !isStruggling)
    {
        SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat(kStruggleSoundName,thiefName(type)->getCString())->getCString());
    }
}

void ThiefSprite::playCageSound()
{
    if (!AnimalThievesManager::sharedMannager()->getIsSoundStopped() && AnimalThievesManager::sharedMannager()->getGameState() != kGameStateOver && !isFalling && !isStruggling)
    {
        SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat(kCageSoundName,thiefName(type)->getCString())->getCString());
    }
}

void ThiefSprite::remove()
{
    cpSpaceAddPostStepCallback(space, (cpPostStepFunc)handleCollisionRemove, shape,NULL);
    this->stopAllActions();
    this->setVisible(false);
}

void ThiefSprite::die()
{
    if (!AnimalThievesManager::sharedMannager()->getIsSoundStopped())
    {
        SimpleAudioEngine::sharedEngine()->playEffect(kBurnSoundName);
    }
    
    cpSpaceAddPostStepCallback(space, (cpPostStepFunc)handleCollisionRemove, shape,NULL);
    CCAnimation* dieAnimation = CCAnimation::create();
    dieAnimation->setDelayPerUnit(0.12f);
    for (int i = 1; i < 4; i++)
    {
        dieAnimation->addSpriteFrameWithFileName(CCString::createWithFormat("%sDie_%d.png",thiefName(type)->getCString(),i)->getCString());
    }
    CCAnimate* actionDieAnimation = CCAnimate::create(dieAnimation);
    CCRepeat* actionDieRepeat = CCRepeat::create(actionDieAnimation, 1);
    CCHide* actionDieFade = CCHide::create();
    CCSequence* actionDieSeq = CCSequence::create(actionDieRepeat,actionDieFade,nil);
    this->runAction(actionDieSeq);
    
    CCSprite* thiefSoul = CCSprite::create(CCString::createWithFormat("%sSoul_1.png",thiefName(type)->getCString())->getCString());
    thiefSoul->setPosition(ccp(this->getPositionX(), this->getPositionY() + 20));
    this->getParent()->addChild(thiefSoul, 2);
    thiefSoul->setVisible(false);
    
    CCAnimation* flyAnimation = CCAnimation::create();
    flyAnimation->setDelayPerUnit(0.12f);
    for (int i = 0; i < 4; i++)
    {
        flyAnimation->addSpriteFrameWithFileName(CCString::createWithFormat("%sSoul_%d.png",thiefName(type)->getCString(),i)->getCString());
    }
    
    CCAnimate* actionFlyAnimation = CCAnimate::create(flyAnimation);
    CCRepeatForever* actionFlyRepeatForever = CCRepeatForever::create(actionFlyAnimation);
    thiefSoul->runAction(actionFlyRepeatForever);
    
    CCDelayTime* actionSoulDelay = CCDelayTime::create(0.5f);
    CCShow* actionSoulShow = CCShow::create();
	CCMoveBy* actionSoulMove1 = CCMoveBy::create(1.0, ccp(-30, 100));
    CCMoveBy* actionSoulMove2 = CCMoveBy::create(2.0, ccp(60, 200));
	CCMoveBy* actionSoulMove3 = CCMoveBy::create(2.0, ccp(-60, 200));
	CCMoveBy* actionSoulMove4 = CCMoveBy::create(2.0, ccp(60, 200));
	CCMoveBy* actionSoulMove5 = CCMoveBy::create(2.0, ccp(-60, 200));
	CCMoveBy* actionSoulMove6 = CCMoveBy::create(1.0, ccp(30, 100));


	CCSequence* actionSoulSeq = CCSequence::create(actionSoulDelay, actionSoulShow, actionSoulMove1, actionSoulMove2, actionSoulMove3, actionSoulMove4, actionSoulMove5, actionSoulMove6, nil);
	thiefSoul->runAction(actionSoulSeq);
    CCSprite* thiefWing = CCSprite::create("wing_1.png");
    thiefWing->setPosition(ccp(thiefSoul->getContentSize().width / 2, thiefSoul->getContentSize().height / 2 + 18));
    thiefSoul->addChild(thiefWing,1);
    
    CCAnimation *wingAnimation = CCAnimation::create();
    for (int i = 0; i < 4; i++)
    {
        wingAnimation->addSpriteFrameWithFileName(CCString::createWithFormat("wing_%d.png",i)->getCString());
    }
    CCAnimate* actionWingAnimation = CCAnimate::create(wingAnimation);
    CCRepeatForever* actionWingRepeatForever = CCRepeatForever::create(actionWingAnimation);
    thiefWing->runAction(actionWingRepeatForever);
}