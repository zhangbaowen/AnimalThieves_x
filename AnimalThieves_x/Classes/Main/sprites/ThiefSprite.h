//
//  ThiefSprite.h
//  AnimalThieves_x
//
//  Created by Zhang Baowen on 13-11-4.
//
//

#ifndef AnimalThieves_x_ThiefSprite_h
#define AnimalThieves_x_ThiefSprite_h

#include "cocos2d.h"
#include "chipmunk.h"

#define kThiefSoundName "%sSound.mp3"
#define kStruggleSoundName "%sStruggleSound.mp3"
#define kCageSoundName "%sCageSound.mp3"
#define kOriginSoundName kCageSoundName

typedef enum
{
	kThiefTypeRatel = 1,
	kThiefTypePanda,
	kThiefTypeEagle,
	kThiefTypeRabbit,
	kThiefTypeBear
} ThiefType;

class ThiefSprite : public cocos2d::CCSprite
{
    CC_SYNTHESIZE(ThiefType,type,Type);
    CC_SYNTHESIZE_READONLY(bool,isFalling,IsFalling);
    CC_SYNTHESIZE_READONLY(bool,isStruggling,IsStruggling);
public:
    cpSpace *space;
	cpBody *body;
	cpShape *shape;
    
    cocos2d::CCString* thiefName(ThiefType t);
    void* spriteWithType(ThiefType t);
    void* initWithType(ThiefType t);
    void addThiefAction();
    void addFallAction();
    void addStruggleAction();
    void playThiefSound();
    void playOriginSound();
    void playStruggleSound();
    void playCageSound();
    void remove();
    void die();
    void setIsFalling(bool falling);
    void setIsStruggling(bool struggling);
};


#endif
