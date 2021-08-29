#include <photon.h>
#include <stdlib.h>

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
    if (((tri->c.x - tri->a.x) * y - (tri->c.y - tri->a.y) * x > 0.0) == ab) return false;
    if (((tri->c.x - tri->b.x) * (p.y - tri->b.y) - (tri->c.y - tri->b.y) * (p.x - tri->b.x) > 0.0) != ab) return false;
    return true;
}

bool tri2D_point_overlap_offset(const Tri2D* tri, vec2 p, vec2 offset)
{
    return tri2D_point_overlap(tri, vec2_add(p, offset));
}

bool tri2D_overlap(const Tri2D* t1, const Tri2D* t2)
{
    return  line2D_intersect(t1->a, t1->b, t2->a, t2->b, NULL) || 
            line2D_intersect(t1->a, t1->b, t2->a, t2->c, NULL) || 
            line2D_intersect(t1->a, t1->b, t2->b, t2->c, NULL) || 
            line2D_intersect(t1->a, t1->c, t2->a, t2->b, NULL) || 
            line2D_intersect(t1->a, t1->c, t2->a, t2->c, NULL) || 
            line2D_intersect(t1->a, t1->c, t2->b, t2->c, NULL) || 
            line2D_intersect(t1->b, t1->c, t2->a, t2->b, NULL) ||
            line2D_intersect(t1->b, t1->c, t2->a, t2->c, NULL); 
}

bool tri2D_overlap_offset(const Tri2D* t1, const Tri2D* t2, vec2 offset)
{
    Tri2D t = tri2D_new(vec2_add(t1->a, offset), vec2_add(t1->b, offset), vec2_add(t1->c, offset));
    return  line2D_intersect(t.a, t.b, t2->a, t2->b, NULL) || 
            line2D_intersect(t.a, t.b, t2->a, t2->c, NULL) || 
            line2D_intersect(t.a, t.b, t2->b, t2->c, NULL) || 
            line2D_intersect(t.a, t.c, t2->a, t2->b, NULL) || 
            line2D_intersect(t.a, t.c, t2->a, t2->c, NULL) || 
            line2D_intersect(t.a, t.c, t2->b, t2->c, NULL) || 
            line2D_intersect(t.b, t.c, t2->a, t2->b, NULL) ||
            line2D_intersect(t.b, t.c, t2->a, t2->c, NULL); 
}

#define BIGF 100000000.0
bool tri2D_hit(const Tri2D* restrict tri, const Ray2D* restrict ray, Hit2D* outHit)
{
    bool hit = false;
    vec2 p, n, v = ray2D_at(ray, BIGF);
    float sqdist = BIGF;

    if (line2D_intersect(tri->a, tri->b, ray->orig, v, &p)) {
        float d = vec2_sqdist(ray->orig, p);
        if (d < sqdist) {
            sqdist = d;
            n = vec2_cross(tri->a, tri->b);
        }
        hit = true;
    }

    if (line2D_intersect(tri->a, tri->c, ray->orig, v, &p)) {
        float d = vec2_sqdist(ray->orig, p);
        if (d < sqdist) {
            sqdist = d;
            n = vec2_cross(tri->a, tri->c);
        }
        hit = true;
    }

    if (line2D_intersect(tri->b, tri->c, ray->orig, v, &p)) {
        float d = vec2_sqdist(ray->orig, p);
        if (d < sqdist) {
            sqdist = d;
            n = vec2_cross(tri->b, tri->c);
        }
        hit = true;
    }
    if (!hit) return false;

    outHit->t = sqrtf(sqdist);
    outHit->normal = vec2_normal(n);
    return true;
}

bool tri2D_hit_range(const Tri2D* restrict tri, const Ray2D* restrict ray, Hit2D* outHit, float max)
{
    bool hit = false;
    vec2 p, n, v = ray2D_at(ray, BIGF);
    float sqdist = BIGF;

    if (line2D_intersect(tri->a, tri->b, ray->orig, v, &p)) {
        float d = vec2_sqdist(ray->orig, p);
        if (d < sqdist) {
            sqdist = d;
            n = vec2_cross(tri->a, tri->b);
        }
        hit = true;
    }

    if (line2D_intersect(tri->a, tri->c, ray->orig, v, &p)) {
        float d = vec2_sqdist(ray->orig, p);
        if (d < sqdist) {
            sqdist = d;
            n = vec2_cross(tri->a, tri->c);
        }
        hit = true;
    }

    if (line2D_intersect(tri->b, tri->c, ray->orig, v, &p)) {
        float d = vec2_sqdist(ray->orig, p);
        if (d < sqdist) {
            sqdist = d;
            n = vec2_cross(tri->b, tri->c);
        }
        hit = true;
    }
    if (!hit || sqdist > max * max) return false;

    outHit->t = sqrtf(sqdist);
    outHit->normal = vec2_normal(n);
    return true;
}
