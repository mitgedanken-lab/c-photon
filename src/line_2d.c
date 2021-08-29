#include <photon.h>
#include <stdlib.h>

bool line2D_intersect(vec2 p0, vec2 p1, vec2 p2, vec2 p3, vec2* out)
{
    vec2 s1 = _vec2_sub(p1, p0);
    vec2 s2 = _vec2_sub(p3, p2);

    float s = (-s1.y * (p0.x - p2.x) + s1.x * (p0.y - p2.y)) / (-s2.x * s1.y + s1.x * s2.y);
    float t = ( s2.x * (p0.y - p2.y) - s2.y * (p0.x - p2.x)) / (-s2.x * s1.y + s1.x * s2.y);

    if (out != NULL) *out = vec2_add(p0, vec2_mult(s1, t));
    return (s >= 0.0 && s <= 1.0 && t >= 0.0 && t <= 1.0);
}