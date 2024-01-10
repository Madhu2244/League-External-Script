// Input.h
#ifndef INPUT_H
#define INPUT_H

// Function to simulate a right-click at a given screen coordinate
void SimulateRightClickAndReset(int x, int y);

void SimulateRightClick();

// Function to check if the spacebar is currently held down
bool IsSpacebarHeldDown();
bool IsZKeyHeldDown();

#endif // INPUT_H
