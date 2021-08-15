#include <photon.h>

bool sphere_hit(const Sphere* restrict sphere, const Ray3D* restrict ray, Hit3D* outHit, float tMin, float tMax)
{
    vec3 oc = vec3_sub(ray->orig, sphere->pos);
    float b = vec3_dot(oc, ray->dir);
    float c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
    float discr = b * b - c;
    if (discr > 0.0f) {
        float discrSq = sqrtf(discr);
        
        float t = (-b - discrSq);
        if (t < tMax && t > tMin) {
            outHit->pos = ray3D_at(ray, t);
            outHit->normal = vec3_mult(vec3_sub(outHit->pos, sphere->pos), 1.0f / sphere->radius);
            outHit->t = t;
            return true;
        }
        
        t = (-b + discrSq);
        if (t < tMax && t > tMin) {
            outHit->pos = ray3D_at(ray, t);
            outHit->normal = vec3_mult(vec3_sub(outHit->pos, sphere->pos), 1.0f / sphere->radius);
            outHit->t = t;
            return true;
        }
    }
    return false;
}