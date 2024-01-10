#include "Input.h"
#include <windows.h>
#include <iostream>

void SimulateRightClickAndReset(int x, int y) {
    POINT originalPos;
    GetCursorPos(&originalPos);

    SetCursorPos(x, y);
    mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0); // Left button down
    mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);   // Left button up

    Sleep(10);

    SetCursorPos(originalPos.x, originalPos.y);
    SetCursorPos(originalPos.x, originalPos.y);
}

void SimulateRightClick() {
    POINT currentPos;
    GetCursorPos(&currentPos);
    mouse_event(MOUSEEVENTF_RIGHTDOWN, currentPos.x, currentPos.y, 0, 0);
    mouse_event(MOUSEEVENTF_RIGHTUP, currentPos.x, currentPos.y, 0, 0);
}

bool IsSpacebarHeldDown() {
    return (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0;
}

bool IsZKeyHeldDown() {
    return (GetAsyncKeyState(0x5A) & 0x8000) != 0;
}
