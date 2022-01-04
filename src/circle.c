#include <photon.h>

Circle circle_new(vec2 pos, float radius)
{
    Circle c = {pos, radius};
    return c;
}

bool circle_point_overlap(Circle circle, vec2 p)
{
    return vec2_sqdist(circle.pos, p) <= circle.radius * circle.radius;
}

bool circle_point_overlap_offset(Circle circle, vec2 p, vec2 offset)
{
    p.x += offset.x;
    p.y += offset.y;
    return vec2_sqdist(circle.pos, p) <= circle.radius * circle.radius;
}

bool circle_overlap(Circle c1, Circle c2)
{
    float r = c1.radius + c2.radius;
    return vec2_sqdist(c1.pos, c2.pos) <= r * r;
}

bool circle_overlap_offset(Circle c1, Circle c2, vec2 offset)
{
    c1.pos.x += offset.x;
    c1.pos.y += offset.y;
    float r = c1.radius + c2.radius;
    return vec2_sqdist(c1.pos, c2.pos) <= r * r;
}
