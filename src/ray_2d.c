#include <photon.h>

Ray2D ray2D_new(vec2 orig, vec2 dir) 
{
    Ray2D ray = {orig, dir};
    return ray;
}

Hit2D hit2D_new(float t, vec2 normal)
{
    Hit2D hit = {t, normal};
    return hit;
}

vec2 ray2D_at(const Ray2D* restrict ray, float t) 
{ 
    vec2 p = {ray->orig.x + ray->dir.x * t, ray->orig.y + ray->dir.y * t};
    return p;
}