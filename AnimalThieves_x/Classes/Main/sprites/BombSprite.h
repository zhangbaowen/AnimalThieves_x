//
//  BombSprite.h
//  AnimalThieves_x
//
//  Created by Zhang Baowen on 13-11-1.
//
//

#ifndef AnimalThieves_x_BombSprite_h
#define AnimalThieves_x_BombSprite_h
#include "cocos2d.h"
#include "chipmunk.h"

class BombSprite : public cocos2d::CCSprite {

public:
    cpSpace *space;
	cpBody *body;
	cpShape *shape;
    void removeExplosion(void* sender);
    bool initWithFile(const char *filename);
    void explode();

};



#endif
