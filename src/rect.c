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

static inline void rect_move(Rect* rect, vec2 add)
{
    rect->x += add.x;
    rect->y += add.y;
}

Rect rect_new(float x, float y, float w, float h)
{
    Rect r = {x, y, w, h};
    return r;
}

bool rect_point_overlap(vec2 v, Rect r)
{
    r = rect_half(r);
    return  (v.x > r.x - r.w) &&
            (v.x < r.x + r.w) &&
            (v.y > r.y - r.h) &&
            (v.y < r.y + r.h);
}

bool rect_point_overlap_offset(vec2 v, Rect r, vec2 offset)
{
    return rect_point_overlap(vec2_add(v, offset), r);
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
    rect_move(&r1, offset);
    return rect_overlap(r1, r2);
}