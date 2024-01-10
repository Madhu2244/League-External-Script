// Point.h
#ifndef POINT_H
#define POINT_H

class Point {
public:
    float x, y, z, w;

    // Constructor for 2D points
    Point(float x = 0.0f, float y = 0.0f);

    // Constructor for 3D points
    Point(float x, float y, float z);

    // Constructor for 4D points
    Point(float x, float y, float z, float w);

    // Method to calculate the distance to another Point
    float DistanceTo(const Point& other) const;
};

#endif // POINT_H
