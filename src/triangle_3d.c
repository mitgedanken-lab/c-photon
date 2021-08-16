#include <photon.h>

#define _ray3D_at(ray, t) {ray->orig.x + ray->dir.x * t, ray->orig.y + ray->dir.y * t, ray->orig.z + ray->dir.z * t}

vec3 tri3D_norm(const Tri3D* restrict tri)
{
    vec3 e1 = _vec3_sub(tri->b, tri->a);
    vec3 e2 = _vec3_sub(tri->c, tri->a);
    vec3 c = _vec3_cross(e1, e2);
    vec3 ret = _vec3_normal(c);
    return ret;
}

bool tri3D_hit(const Tri3D* restrict tri, const Ray3D* restrict ray, Hit3D* outHit, float tMin, float tMax)
{ 
    float nRayDir = _vec3_dot(tri->n, ray->dir);
    if (_absf(nRayDir) < 0.01) return false; // parallel

    // compute t (equation P = O + tR, where P is intersection point, O is ray origin and R its direction)
    float d = _vec3_dot(tri->n, tri->a);
    float t = -(_vec3_dot(tri->n, ray->orig) - d) / nRayDir; 

    if (t < tMin || t > tMax) return false; // triangle is outside depth field

    vec3 P = _ray3D_at(ray, t);
    
    outHit->pos = P;
    outHit->t = t;
    outHit->normal = tri->n;

    {
        vec3 e = _vec3_sub(tri->b, tri->a);
        vec3 v = _vec3_sub(P, tri->a);
        vec3 C = _vec3_cross(e, v); 
        if (_vec3_dot(tri->n, C) < 0) return false; // P is on the right side 
    }

    {
        vec3 e = _vec3_sub(tri->c, tri->b);
        vec3 v = _vec3_sub(P, tri->b);
        vec3 C = _vec3_cross(e, v); 
        if (_vec3_dot(tri->n, C) < 0) return false; // P is on the right side 
    }

    {
        vec3 e = _vec3_sub(tri->a, tri->c);
        vec3 v = _vec3_sub(P, tri->c); 
        vec3 C = _vec3_cross(e, v);
        if (_vec3_dot(tri->n, C) < 0) return false; // P is on the right side; 
    }

    return true; // Hit!
} 