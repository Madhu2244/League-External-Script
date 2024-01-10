#include "TargetSelector.h"
#include "HeroData.h"
#include "Offsets.h"
#include <vector>

GameObject* FindClosestTarget(LoLProcessInfo& lolInfo, DWORD64 heroListArray, DWORD64 heroListSize, GameObject localHero) {
    std::vector<GameObject*> allHeros;
    GameObject* closestTarget = nullptr;

    for (int i = 0; i < ReadHeroListSize(lolInfo); i++) {
        DWORD64 currentHeroOffset = Offset::ByteOffset * i;
        GameObject* currentHero = new GameObject(lolInfo, (heroListArray + currentHeroOffset));
        allHeros.push_back(currentHero);

        float currentHeroHealth = currentHero->ReadHeroHealth();
        DWORD64 currentHeroTeam = currentHero->ReadHeroTeam();
        bool currentHeroIsVisible = currentHero->ReadHeroVisibility();
        Point currentHeroPos = currentHero->ReadHeroPosition();

        if (
            currentHeroTeam != localHero.ReadHeroTeam() && 
            currentHeroHealth > 0 && 
            currentHeroIsVisible && 
            currentHeroPos.DistanceTo(localHero.ReadHeroPosition()) < localHero.ReadHeroAttackRange() &&
            (closestTarget == nullptr || (closestTarget->ReadHeroPosition()).DistanceTo(localHero.ReadHeroPosition()))
        ) {
            closestTarget = currentHero;
        }
    }
    return closestTarget;
}

GameObject* FindLowestHPTarget(LoLProcessInfo& lolInfo, DWORD64 heroListArray, DWORD64 heroListSize, GameObject localHero) {
    std::vector<GameObject*> allHeros;
    GameObject* closestTarget = nullptr;
    for (int i = 0; i < heroListSize; i++) {
        DWORD64 currentHeroOffset = Offset::ByteOffset * i;
        GameObject* currentHero = new GameObject(lolInfo, (heroListArray + currentHeroOffset));
        allHeros.push_back(currentHero);

        float currentHeroHealth = currentHero->ReadHeroHealth();
        DWORD64 currentHeroTeam = currentHero->ReadHeroTeam();
        bool currentHeroIsVisible = currentHero->ReadHeroVisibility();
        Point currentHeroPos = currentHero->ReadHeroPosition();

        if (
            currentHeroTeam != localHero.ReadHeroTeam() && 
            currentHeroHealth > 0 && 
            currentHeroIsVisible && 
            currentHeroPos.DistanceTo(localHero.ReadHeroPosition()) < localHero.ReadHeroAttackRange() + 80 &&
            (closestTarget == nullptr || currentHeroHealth < (closestTarget->ReadHeroHealth()))
        ) {
            closestTarget = currentHero;
        }
    }
    return closestTarget;
}