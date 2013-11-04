//
//  AutoSprite.cpp
//  AnimalThieves_x
//
//  Created by Zhang Baowen on 13-11-4.
//
//

#include "AutoSprite.h"
#include "AnimalThievesManager.h"
#include "Constants.h"
using namespace std;
using namespace cocos2d;
void* AutoSprite::spriteWithType(int t)
{
    return this->initWithType(t);
}

void* AutoSprite::initWithType(int t)
{
    CCString *autoImageName;
    switch (t)
    {
        case kAutoTypeBarrel:
            autoImageName->createWithFormat(CCString::create("barrel.png")->getCString(),type);
            break;
        case kAutoTypeBoard:
			autoImageName->createWithFormat(CCString::create("board.png")->getCString(), type);
			break;
		case kAutoTypeBox:
			autoImageName->createWithFormat(CCString::create("box.png")->getCString(), type);
			break;
		case kAutoTypeWheel:
			autoImageName->createWithFormat(CCString::create("wheel.png")->getCString(), type);
			break;
		default:
			break;
    }
    if (this == CCSprite::create((char *)autoImageName))
    {
        type = t;
    }
    return this;
}

void AutoSprite::melt()
{
    this->runAction(CCHide::create());
}