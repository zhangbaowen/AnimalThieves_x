//
//  AnimalThievesManager.h
//  AnimalThieves_x
//
//  Created by Zhang Baowen on 13-11-1.
//
//

#ifndef AnimalThieves_x_AnimalThievesManager_h
#define AnimalThieves_x_AnimalThievesManager_h
#include "cocos2d.h"

typedef enum
{
	kGameStateNormal = 1,
	kGameStateStarting,
	kGameStateTesting,
	kGameStatePaused,
	kGameStateOver
} GameState;

class AnimalThievesManager : public cocos2d::CCObject
{
    
public:
    CC_SYNTHESIZE(bool,isMusicStopped,IsMusicStopped);
    CC_SYNTHESIZE(bool,isSoundStopped,IsSoundStopped);
    CC_SYNTHESIZE(GameState,gameState,GameState);
    CC_SYNTHESIZE(int,stage,Stage);
    static AnimalThievesManager* sharedMannager();
};

#endif
