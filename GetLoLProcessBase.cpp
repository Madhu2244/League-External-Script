#include "GetLoLProcessBase.h"


// Internal function to get the process ID
static DWORD GetLeagueOfLegendsPID() {
    HWND hWnd = FindWindowA(nullptr, "League of Legends (TM) Client");

    DWORD processID;
    GetWindowThreadProcessId(hWnd, &processID);

    return processID;
}

// Internal function to get the base address
static DWORD_PTR GetLeagueOfLegendsBaseAddress(HANDLE hProcess) {
    HMODULE hMods[1024];
    DWORD cbNeeded;

    // Get the list of all modules in the process
    if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
        for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
            TCHAR szModName[MAX_PATH];

            // Get the full path to the module's file
            if (GetModuleFileNameEx(hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR))) {
                if (_tcsstr(szModName, TEXT("League of Legends.exe"))) {
                    MODULEINFO modInfo;
                    if (GetModuleInformation(hProcess, hMods[i], &modInfo, sizeof(modInfo))) {
                        return (DWORD_PTR)modInfo.lpBaseOfDll;
                    }
                }
            }
        }
    }

    return 0;
}

HWND FindLeagueOfLegendsWindow() {
    HWND hwndTarget = FindWindowW(L"RiotWindowClass",L"League of Legends (TM) Client");
    std::cout << hwndTarget << std::endl;
    return hwndTarget;
}

// Exported function
LoLProcessInfo GetLeagueOfLegendsInfo() {
    LoLProcessInfo info = {NULL, 0};

    DWORD processID = GetLeagueOfLegendsPID();

    info.hwndTarget = FindLeagueOfLegendsWindow();
    info.hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    info.baseAddress = GetLeagueOfLegendsBaseAddress(info.hProcess);

    std::cout << info.hProcess << std::endl;
    std::cout << info.baseAddress << std::endl;

    return info;  
}