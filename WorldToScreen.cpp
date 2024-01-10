#include "WorldToScreen.h"
#include "Offsets.h"
#include <iostream>
#include <windows.h>

// Global variables for view and projection matrices
static float viewProjMatrix[16] = {0};

// Function to multiply matrices for generating the ViewProjMatrix
void MultiplyMatrices(float* out, float* a, int row1, int col1, float* b, int row2, int col2) {
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            float sum = 0.f;
            for (int k = 0; k < col1; k++) {
                sum += a[i * col1 + k] * b[k * col2 + j];
            }
            out[i * col2 + j] = sum;
        }
    }
}

// Load all relevant values from memory
void LoadW2S(LoLProcessInfo lolInfo) {
    char buff[128];
    DWORD_PTR baseAddressWithOffset = lolInfo.baseAddress + Offset::ViewProjMatrices;

    ReadProcessMemory(lolInfo.hProcess, (LPCVOID)baseAddressWithOffset, buff, sizeof(buff), NULL);

    float viewMatrix[16];
    float projMatrix[16];

    memcpy(viewMatrix, buff, 16 * sizeof(float));
    memcpy(projMatrix, &buff[16 * sizeof(float)], 16 * sizeof(float));

    MultiplyMatrices(viewProjMatrix, viewMatrix, 4, 4, projMatrix, 4, 4);
}

// Convert a point from world coordinates to screen coordinates
Point WorldToScreen(const Point& pos) {
    Point out = { 0.f, 0.f };
    Point screen = { (float)2560, (float)1440 };

    Point clipCoords;
    clipCoords.x = pos.x * viewProjMatrix[0] + pos.y * viewProjMatrix[4] + pos.z * viewProjMatrix[8] + viewProjMatrix[12];
    clipCoords.y = pos.x * viewProjMatrix[1] + pos.y * viewProjMatrix[5] + pos.z * viewProjMatrix[9] + viewProjMatrix[13];
    clipCoords.z = pos.x * viewProjMatrix[2] + pos.y * viewProjMatrix[6] + pos.z * viewProjMatrix[10] + viewProjMatrix[14];
    clipCoords.w = pos.x * viewProjMatrix[3] + pos.y * viewProjMatrix[7] + pos.z * viewProjMatrix[11] + viewProjMatrix[15];

    if (clipCoords.w < 1.0f)
        clipCoords.w = 1.f;

    Point M;
    M.x = clipCoords.x / clipCoords.w;
    M.y = clipCoords.y / clipCoords.w;

    out.x = (screen.x / 2.f * M.x) + (M.x + screen.x / 2.f);
    out.y = -(screen.y / 2.f * M.y) + (M.y + screen.y / 2.f);

    return out;
}
