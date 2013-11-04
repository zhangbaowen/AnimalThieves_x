//
//  AutoSprite.h
//  AnimalThieves_x
//
//  Created by Zhang Baowen on 13-11-4.
//
//

#ifndef AnimalThieves_x_AutoSprite_h
#define AnimalThieves_x_AutoSprite_h

#include "cocos2d.h"
#include "chipmunk.h"

#define kAutoTypeBarrel 1
#define kAutoTypeBoard 2
#define kAutoTypeBox 3
#define kAutoTypeWheel 4

class AutoSprite : public cocos2d::CCSprite
{
    CC_SYNTHESIZE(int,type,Type);
    
public:
    cpSpace *space;
	cpBody *body;
	cpShape *shape;
    void* spriteWithType(int t);
    void* initWithType(int t);
    void melt();
};

#endif
