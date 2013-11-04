//
//  MainGameScene.h
//  AnimalThieves_x
//
//  Created by Zhang Baowen on 13-11-1.
//
//

#ifndef AnimalThieves_x_MainGameScene_h
#define AnimalThieves_x_MainGameScene_h
#include "cocos2d.h"
#include "chipmunk.h"
using namespace cocos2d;

#define kStageBgImageName "stage%dBg.jpg"
#define kTimeTotal 50
#define kScoreTotal 2000
#define kScoreDown 40

class MainGame : public CCLayer
{
    CC_SYNTHESIZE(float,timeLeft,TimeLeft);
    CC_SYNTHESIZE_RETAIN(CCProgressTimer*,timeBannerRed,TimeBannerRed);
    CC_SYNTHESIZE_RETAIN(CCLabelTTF*,scoreLabel,ScoreLabel);
    int lastTime;
    CCSprite* timeBannerBg;
	CCSprite *stageBar;
	CCLabelTTF *stageLabel;
	CCLabelTTF *bestScoreLabel;
    CCMenuItem *helpButton;
	CCMenuItemToggle *musicButton;
	CCMenuItemToggle *soundButton;
    int bestScore;
	int score;
	int scoreI;
	int scoreAdd;
	int *finalScoreLabel;
    CCArray *records;
	
	cpSpace *space;
	
    void initBackground();
    void step(CCTime delta);
    void win();
    void saveRecord();
    
public:
    CCMenuItem *backButton;
	CCMenuItem *replayButton;
	CCMenuItemToggle *pauseAndResumeButton;
	
	CCArray *doorSprites; // 静
	CCArray *bombSprites;
	CCArray *thiefSprites;
	CCArray *goldSprites; // 静
	CCArray *cageSprites; // 静
	CCArray *staticSprites; // 静
	CCArray *autoSprites;
    
    CCArray* stageLightsXY(int stage);
    static float stageGravityY(int stage);
    static float stageBottomY(int stage);
    static float stageBombThiefR(int stage);
    static float stageBombAutoR(int stage);
    static float stageBombF(int stage);
    CCScene scene();
    void lost();

};
#endif
