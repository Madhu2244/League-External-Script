#include "HeroData.h"
#include "Offsets.h"

DWORD64 ReadHeroList(LoLProcessInfo lolInfo) {
    DWORD64 heroList;
    ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(lolInfo.baseAddress + Offset::HeroList), &heroList, Offset::ByteOffset, NULL);
    return heroList;
}


DWORD64 ReadHeroListArray(LoLProcessInfo lolInfo) {
    DWORD64 heroListArray = 0;
    ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(ReadHeroList(lolInfo) + Offset::HeroListArray), &heroListArray, Offset::ByteOffset, NULL);
    return heroListArray;
}

DWORD64 ReadHeroListSize(LoLProcessInfo lolInfo) {
    DWORD64 heroListSize = 0;
    ReadProcessMemory(lolInfo.hProcess, (LPCVOID)(ReadHeroList(lolInfo) + Offset::HeroListSize), &heroListSize, 1, NULL);
    return heroListSize;
}