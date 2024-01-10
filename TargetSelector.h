// TargetSelector.h
#ifndef TARGETSELECTOR_H
#define TARGETSELECTOR_H

#include "GameObject.h"

GameObject* FindClosestTarget(LoLProcessInfo& lolInfo, DWORD64 heroListArray, DWORD64 heroListSize, GameObject localHero);

GameObject* FindLowestHPTarget(LoLProcessInfo& lolInfo, DWORD64 heroListArray, DWORD64 heroListSize, GameObject localHero);


#endif // TARGETSELECTOR_H