#include <cmath>
#include "../include/geometry.h"

Point* direction_to_point(Direction d) {
    Point* p = new Point();
    p->x = ((d < Direction::NORTH || d > Direction::SOUTH) ? 1 :        // EAST
            ((d > Direction::NORTH && d < Direction::SOUTH) ? -1 : 0)); // WEST
    p->y = ((d > Direction::EAST && d < Direction::WEST) ? -1 :         // NORTH
            (d > Direction::WEST ? 1 : 0));                             // SOUTH
    return p;
}

Direction point_to_direction(Point* p) {
    int a = (int)round(atan2(-p->y, p->x)*4/3.1415926535);
    return static_cast<Direction>((a+8)%8);
}

Point* translate(Point* p, Direction d, float dist) {
    Point* t = direction_to_point(d);
    t->x += p->x;
    t->y += p->y;
    t->z += p->z;
    return t;
}

Point* translate_in(Point* p, Direction d, float dist) {
    Point* t = direction_to_point(d);
    p->x += t->x;
    p->y += t->y;
    p->z += t->z;
    delete t;
    return p;
}
