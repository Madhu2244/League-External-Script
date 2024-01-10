// MissileReader.h
#ifndef MISSILEREADER_H
#define MISSILEREADER_H
#include "GetLolProcessBase.h"
#include "Point.h"
#include <vector>
#include <fstream>

std::vector<std::pair<Point, Point>> ReadMissiles(LoLProcessInfo lolInfo);

#endif // MISSILEREADER_H
