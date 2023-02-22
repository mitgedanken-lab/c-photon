#include <photon.h>

Quad2D quad2D_new(vec2 a, vec2 b, vec2 c, vec2 d)
{
    Quad2D q = {a, b, c, d};
    return q;
}

Quad2D rect_to_quad(Rect r)
{
    Quad2D q = {
        {r.x + r.w, r.y + r.h},
        {r.x + r.w, r.y - r.h},
        {r.x - r.w, r.y - r.h},
        {r.x - r.w, r.y + r.h}
    };
    return q;
}
