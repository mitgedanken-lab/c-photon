#include <photon.h>

/*
-----------
 -> Rect <- 
-----------
*/

static inline Rect rect_half(Rect rect)
{
    Rect ret = {rect.x, rect.y, absf(rect.w) * 0.5f, absf(rect.h) * 0.5f};
    return ret;
}

Rect rect_new(float x, float y, float w, float h)
{
    Rect r = {x, y, w, h};
    return r;
}

Rect quad_to_rect(Quad2D q) 
{
    Rect r;
    r.w = q.a.x - q.c.x;
    r.h = q.a.y - q.b.y;
    r.x = q.a.x - r.w * 0.5;
    r.y = q.a.y - r.h * 0.5;
    return r;
}

bool rect_point_overlap(Rect r, vec2 p)
{
    r = rect_half(r);
    return  (p.x > r.x - r.w) &&
            (p.x < r.x + r.w) &&
            (p.y > r.y - r.h) &&
            (p.y < r.y + r.h);
}

bool rect_point_overlap_offset(Rect r, vec2 p, vec2 offset)
{
    p = vec2_add(p, offset);
    return  (p.x > r.x - r.w) &&
            (p.x < r.x + r.w) &&
            (p.y > r.y - r.h) &&
            (p.y < r.y + r.h);
}

bool rect_overlap(Rect r1, Rect r2)
{
    r1 = rect_half(r1);
    r2 = rect_half(r2);
    return  (r1.x - r1.w < r2.x + r2.w) &&
            (r1.x + r1.w > r2.x - r2.w) &&
            (r1.y - r1.h < r2.y + r2.h) &&
            (r1.y + r1.h > r2.y - r2.h);
}

bool rect_overlap_offset(Rect r1, Rect r2, vec2 offset)
{
    r1 = rect_half(r1);
    r2 = rect_half(r2);
    r1.x += offset.x;
    r1.y += offset.y;
    return  (r1.x - r1.w < r2.x + r2.w) &&
            (r1.x + r1.w > r2.x - r2.w) &&
            (r1.y - r1.h < r2.y + r2.h) &&
            (r1.y + r1.h > r2.y - r2.h);
}