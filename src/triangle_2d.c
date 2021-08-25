#include <photon.h>

Tri2D tri2D_new(vec2 a, vec2 b, vec2 c)
{
    Tri2D tri = {a, b, c};
    return tri;
}

bool tri2D_point_overlap(const Tri2D* restrict tri, vec2 p)
{
    float x = p.x - tri->a.x;
    float y = p.y - tri->a.y;
    bool ab = (tri->b.x - tri->a.x) * y - (tri->b.y - tri->a.y) * x > 0;
    if ((tri->c.x - tri->a.x) * y - (tri->c.y - tri->a.y) * x > 0.0 == ab) return false;
    if ((tri->c.x - tri->b.x) * (p.y - tri->b.y) - (tri->c.y - tri->b.y) * (p.x - tri->b.x) > 0.0 != ab) return false;
    return true;
}