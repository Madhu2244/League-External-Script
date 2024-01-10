#pragma once
// GetLoLProcessBase.h
#ifndef GETLOLPROCESSBASE_H
#define GETLOLPROCESSBASE_H

#include <windows.h>
#include <psapi.h>
#include <tchar.h>
#include <iostream>

struct LoLProcessInfo {
    HANDLE hProcess;
    DWORD_PTR baseAddress;
    HWND hwndTarget;
};

LoLProcessInfo GetLeagueOfLegendsInfo();

#endif // GETLOLPROCESSBASE_H
