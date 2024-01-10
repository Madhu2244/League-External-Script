// Offsets.h
#ifndef OFFSETS_H
#define OFFSETS_H

#include <windows.h>

namespace Offset {
    extern DWORD64 MissileClient;
    extern DWORD64 MissileMapCount;
    extern DWORD64 MissileMapRoot;
    extern DWORD64 MissileStartPos;
    extern DWORD64 MissileEndPos;
    extern DWORD64 MissileMapKey;
    extern DWORD64 MissileMapVal;
    extern DWORD64 MissileSpellInfo;
    extern DWORD64 SpellEntityCaster;

    extern DWORD64 LocalPlayer;

    extern DWORD64 HeroList;
    extern DWORD64 HeroListArray;
    extern DWORD64 HeroListSize;

    extern DWORD64 ObjHealth;
    extern DWORD64 ObjTeam;
    extern DWORD64 ObjPos;
    extern DWORD64 ObjVisibility;
    extern DWORD64 ObjAtkRange;
    extern DWORD64 ObjAtkSpeedMulti;

    extern DWORD64 ViewProjMatrices;
    extern DWORD64 Renderer;
    extern DWORD64 RendererWidth;
    extern DWORD64 RendererHeight;

    extern DWORD64 ByteOffset;
}

#endif // OFFSETS_H
