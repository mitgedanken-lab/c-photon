#include <photon.h>

Ray3D ray3D_new(vec3 orig, vec3 dir) 
{
    Ray3D ray = {orig, dir};
    return ray;
}

vec3 ray3D_at(const Ray3D* restrict ray, float t) 
{ 
    vec3 v = {ray->orig.x + ray->dir.x * t, ray->orig.y + ray->dir.y * t, ray->orig.z + ray->dir.z * t};
    return v;
}