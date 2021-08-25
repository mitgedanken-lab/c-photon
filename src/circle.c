#include <photon.h>

Circle circle_new(vec2 pos, float radius)
{
    Circle c = {pos, radius};
    return c;
}

bool circle_point_overlap(const Circle* restrict circle, vec2 p)
{
    return vec2_sqdist(circle->pos, p) <= circle->radius * circle->radius;
}