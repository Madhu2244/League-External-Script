#ifndef WORLDTOSCREEN_H
#define WORLDTOSCREEN_H

#include "GetLolProcessBase.h"
#include "Point.h"

void LoadW2S(LoLProcessInfo lolInfo);
Point WorldToScreen(const Point& pos);

#endif // WORLDTOSCREEN_H
