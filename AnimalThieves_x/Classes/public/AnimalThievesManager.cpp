//
//  AnimalThievesManager.cpp
//  AnimalThieves_x
//
//  Created by Zhang Baowen on 13-11-1.
//
//

#include "AnimalThievesManager.h"

static AnimalThievesManager* sharedAnimalThievesManager = NULL;


AnimalThievesManager* AnimalThievesManager::sharedMannager()
{
    if (sharedAnimalThievesManager == NULL)
    {
        sharedAnimalThievesManager = new AnimalThievesManager();
    }
    return sharedAnimalThievesManager;
}