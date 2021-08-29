#include <photon.h>

Sphere sphere_new(vec3 pos, float radius)
{
    Sphere sphere = {pos, radius};
    return sphere;
}

bool sphere_hit(Sphere sphere, const Ray3D* restrict ray, Hit3D* outHit)
{
    vec3 oc = _vec3_sub(ray->orig, sphere.pos);
    float b = _vec3_dot(oc, ray->dir);
    float c = _vec3_dot(oc, oc) - sphere.radius * sphere.radius;
    float discr = b * b - c;
    if (discr > 0.0f) {
        float t = (-b - sqrtf(discr));
        vec3 p = _ray3D_at(ray, t);
        *outHit = hit3D_new(t, vec3_mult(vec3_sub(p, sphere.pos), 1.0f / sphere.radius));
        return true;
    }
    return false;
}

bool sphere_point_overlap(Sphere sphere, vec3 p)
{
    return vec3_sqdist(sphere.pos, p) <= sphere.radius * sphere.radius;
}

bool sphere_point_overlap_offset(Sphere sphere, vec3 p, vec3 offset)
{
    p.x += offset.x;
    p.y += offset.y;
    p.z += offset.z;
    return vec3_sqdist(sphere.pos, p) <= sphere.radius * sphere.radius;
}

bool sphere_overlap(Sphere c1, Sphere c2)
{
    return vec3_sqdist(c1.pos, c2.pos) <= c1.radius * c1.radius + c2.radius * c2.radius;
}

bool sphere_overlap_offset(Sphere c1, Sphere c2, vec3 offset)
{
    c1.pos.x += offset.x;
    c1.pos.y += offset.y;
    c1.pos.z += offset.z;
    return vec3_sqdist(c1.pos, c2.pos) <= c1.radius * c1.radius + c2.radius * c2.radius;
}