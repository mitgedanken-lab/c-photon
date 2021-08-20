#include <photon.h>

Sphere sphere_new(vec3 pos, float radius)
{
    Sphere sphere = {pos, radius};
    return sphere;
}

bool sphere_hit(const Sphere* restrict sphere, const Ray3D* restrict ray, Hit3D* outHit, float tMin, float tMax)
{
    vec3 oc = _vec3_sub(ray->orig, sphere->pos);
    float b = _vec3_dot(oc, ray->dir);
    float c = _vec3_dot(oc, oc) - sphere->radius * sphere->radius;
    float discr = b * b - c;
    if (discr > 0.0f) {
        float discrSq = sqrtf(discr);
        
        float t = (-b - discrSq);
        if (t < tMax && t > tMin) {
            vec3 p = _ray3D_at(ray, t);
            *outHit = hit3D_new(t, vec3_mult(vec3_sub(p, sphere->pos), 1.0f / sphere->radius));
            return true;
        }
        
        t = (-b + discrSq);
        if (t < tMax && t > tMin) {
            vec3 p = _ray3D_at(ray, t);
            *outHit = hit3D_new(t, vec3_mult(vec3_sub(p, sphere->pos), 1.0f / sphere->radius));
            return true;
        }
    }
    return false;
}