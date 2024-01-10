// Orbwalker.h
#ifndef ORBWALKER_H
#define ORBWALKER_H

#include "GetLolProcessBase.h"
#include "GameObject.h"

class Orbwalker {
public:
    Orbwalker(LoLProcessInfo& lolInfo);

    float GetAttackDelay();
    float GetWindupTime();
    void ResetAutoAttackTimer();
    bool CanAttack();
    bool CanMove();

    void Orbwalk();

private:
    LoLProcessInfo& lolInfo;
    DWORD64 heroListArray;
    DWORD64 heroListSize;
    GameObject localHero;

    DWORD64 localHeroTeam;

    DWORD currentTick;
    DWORD lastMove;
    DWORD lastAttack;
    float windupPercentage;
};


#endif // ORBWALKER_H
