#include "Point.h"
#include <cmath>

// Constructor for 2D points
Point::Point(float x, float y) : x(x), y(y), z(0.0f), w(0.0f) {}

// Constructor for 3D points
Point::Point(float x, float y, float z) : x(x), y(y), z(z), w(0.0f) {}

// Constructor for 4D points
Point::Point(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}


float Point::DistanceTo(const Point& other) const {
    return std::sqrt((x - other.x) * (x - other.x) +
                     (y - other.y) * (y - other.y) +
                     (z - other.z) * (z - other.z));
}
