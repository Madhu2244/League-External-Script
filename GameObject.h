// GameObject.h
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <windows.h>
#include "GetLolProcessBase.h"
#include "Point.h"

class GameObject {
public:
    GameObject(LoLProcessInfo& lolInfo, DWORD64 currentGameObject);
    GameObject(const GameObject& other);
    GameObject& operator=(const GameObject& other) {
        if (this != &other) {
            this->lolInfo = other.lolInfo;
            this->currentGameObject = other.currentGameObject;
        }
        return *this;
    }

    float ReadHeroHealth();
    DWORD64 ReadHeroTeam();
    bool ReadHeroVisibility();
    Point ReadHeroPosition();
    float ReadHeroAttackRange();
    float ReadHeroAttackSpeed();
    float ReadHeroAttackSpeedMultiplier();

    float GetWindupTime();

    LoLProcessInfo& lolInfo;
    DWORD64 currentGameObject;
};

#endif // GAMEOBJECT_H