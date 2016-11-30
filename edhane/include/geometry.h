#ifndef EDHANE_GEOMETRY_H
#define EDHANE_GEOMETRY_H

enum class Direction : short unsigned int {
    EAST = 0,
    NORTHEAST = 1,
    NORTH = 2,
    NORTHWEST = 3,
    WEST = 4,
    SOUTHWEST = 5,
    SOUTH = 6,
    SOUTHEAST = 7
};

struct Point {
    float x, y, z;
};

Point* direction_to_point(Direction);
Direction point_to_direction(Point*);

Point* translate(Point*, Direction, float);
Point* translate_in(Point*, Direction, float);

#endif // EDHANE_GEOMETRY_H
