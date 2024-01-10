// GameObject.cpp
#include "GameObject.h"
#include "Offsets.h"
#include <sstream>
#include <iostream>

float BASE_ATTACK_SPEED = 0.644;
float AS_RATIO = 1;

GameObject::GameObject(LoLProcessInfo& lolInfo, DWORD64 currentGameObjectPointer)
    : lolInfo(lolInfo), currentGameObject(0) {
        ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(currentGameObjectPointer), &currentGameObject, Offset::ByteOffset, NULL);
}

GameObject::GameObject(const GameObject& other) 
    : lolInfo(other.lolInfo), currentGameObject(other.currentGameObject) {
}

float GameObject::ReadHeroHealth() {
    float health;
    ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(currentGameObject + Offset::ObjHealth), &health, sizeof(health), NULL);
    return health;
}

DWORD64 GameObject::ReadHeroTeam() {
    int team = 0;
    ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(currentGameObject + Offset::ObjTeam), &team, 4, NULL);
    return team;
}

bool GameObject::ReadHeroVisibility() {
    bool isVisible;
    ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(currentGameObject + Offset::ObjVisibility), &isVisible, sizeof(isVisible), NULL);
    return isVisible;
}

Point GameObject::ReadHeroPosition() {
    Point position;
    ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(currentGameObject + Offset::ObjPos), &position, sizeof(position), NULL);
    return position;
}

float GameObject::ReadHeroAttackRange() {
    float attackRange;
    ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(currentGameObject + Offset::ObjAtkRange), &attackRange, sizeof(attackRange), NULL);
    return attackRange;
}

float GameObject::ReadHeroAttackSpeedMultiplier() {
    float attackSpeedMultiplier;
    ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(currentGameObject + Offset::ObjAtkSpeedMulti), &attackSpeedMultiplier, sizeof(attackSpeedMultiplier), NULL);
    return attackSpeedMultiplier;
}

float GameObject::ReadHeroAttackSpeed() {
    #undef min

    // std::cout << BASE_ATTACK_SPEED * (AS_RATIO * ReadHeroAttackSpeedMultiplier()) << std::endl;
    return BASE_ATTACK_SPEED * (AS_RATIO * ReadHeroAttackSpeedMultiplier()); 
}