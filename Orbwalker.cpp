#include "Orbwalker.h"
#include "HeroData.h"
#include "Offsets.h"
#include "Input.h"
#include "WorldToScreen.h"
#include "TargetSelector.h"
#include "MissileReader.h"
#include <iostream>
#include <stdlib.h>

float WINDUP = 0.16108;
float PING = 28.0;

Orbwalker::Orbwalker(LoLProcessInfo& lolInfo)
    : lolInfo(lolInfo), heroListArray(ReadHeroListArray(lolInfo)), heroListSize(ReadHeroListSize(lolInfo)),
    localHero(GameObject(lolInfo, (lolInfo.baseAddress + Offset::LocalPlayer))),
    localHeroTeam(localHero.ReadHeroTeam()),
    currentTick(0), lastMove(0), lastAttack(0), windupPercentage(WINDUP) {
}

float Orbwalker::GetAttackDelay()
{
    return (int)(1000.0f / localHero.ReadHeroAttackSpeed());
}

float Orbwalker::GetWindupTime()
{
    return (1.0 / localHero.ReadHeroAttackSpeed() * 1000) * windupPercentage;
}

void Orbwalker::ResetAutoAttackTimer()
{
    lastAttack = 0;
}

bool Orbwalker::CanAttack()
{
    return lastAttack + GetAttackDelay() + PING / 2 < GetTickCount();
}

bool Orbwalker::CanMove()
{
    return lastMove < GetTickCount();
}

void Orbwalker::Orbwalk() {
    while (true) {
        if (IsSpacebarHeldDown()) {
            if (CanAttack()) {
                GameObject* target = FindLowestHPTarget(lolInfo, heroListArray, heroListSize, localHero);
                if (target != nullptr) {
                    LoadW2S(lolInfo);
                    Point AttackPosition = WorldToScreen(target->ReadHeroPosition());
                    SimulateRightClickAndReset(AttackPosition.x, AttackPosition.y);
                    lastAttack = GetTickCount()+33;
                    lastMove = GetTickCount() + GetWindupTime()+33;
                }
            }
            if (CanMove()) {
                SimulateRightClick();
                lastMove = GetTickCount() + rand() % 30 + 50;
            }
        } else if (IsZKeyHeldDown()) {
            if (CanMove()) {
                SimulateRightClick();
                lastMove = GetTickCount() + rand() % 30 + 50;
            }
        }
    }
}
