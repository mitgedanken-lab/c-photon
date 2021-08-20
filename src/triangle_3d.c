#include <photon.h>

Tri3D tri3D_new(vec3 a, vec3 b, vec3 c)
{
    Tri3D tri = {a, b, c};
    return tri;
}

vec3 tri3D_norm(const Tri3D* restrict tri)
{
    vec3 e1 = _vec3_sub(tri->b, tri->a);
    vec3 e2 = _vec3_sub(tri->c, tri->a);
    vec3 c = _vec3_cross(e1, e2);
    vec3 ret = _vec3_normal(c);
    return ret;
}

bool _tri3D_hit(const Tri3D* restrict tri, const Ray3D* restrict ray, Hit3D* outHit, float tMin, float tMax)
{ 
    vec3 e1 = _vec3_sub(tri->b, tri->a);
    vec3 e2 = _vec3_sub(tri->c, tri->a);
    vec3 c = _vec3_cross(e1, e2);
    vec3 n = _vec3_normal(c);

    float nRayDir = _vec3_dot(n, ray->dir);
    if (_absf(nRayDir) < 0.01) return false; // parallel

    // compute t (equation P = O + tR, where P is intersection point, O is ray origin and R its direction)
    float d = _vec3_dot(n, tri->a);
    float t = -(_vec3_dot(n, ray->orig) - d) / nRayDir; 

    if (t < tMin || t > tMax) return false; // triangle is outside depth field

    vec3 P = _ray3D_at(ray, t);
    *outHit = hit3D_new(t, n);

    {
        vec3 v = _vec3_sub(P, tri->a);
        vec3 C = _vec3_cross(e1, v); 
        if (_vec3_dot(n, C) < 0) return false; // P is on the right side 
    }

    {
        vec3 v = _vec3_sub(P, tri->b);
        vec3 C = _vec3_cross(e2, v); 
        if (_vec3_dot(n, C) < 0) return false; // P is on the right side 
    }

    {
        vec3 e3 = _vec3_sub(tri->a, tri->c);
        vec3 v = _vec3_sub(P, tri->c); 
        vec3 C = _vec3_cross(e3, v);
        if (_vec3_dot(n, C) < 0) return false; // P is on the right side; 
    }

    return true; // Hit!
} 


#define EPSILON 0.0000001

// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
// Moller-Trumbore algorithm

bool tri3D_hit(const Tri3D* restrict tri, const Ray3D* restrict ray, Hit3D* outHit, float tMin, float tMax)
{
    vec3 vertex0 = tri->a;
    vec3 vertex1 = tri->b;  
    vec3 vertex2 = tri->c;
    float a, f, u, v;

    vec3 edge1 = _vec3_sub(vertex1, vertex0);
    vec3 edge2 = _vec3_sub(vertex2, vertex0);
    vec3 c = _vec3_cross(edge1, edge2);
    vec3 n = _vec3_normal(c);

    vec3 h = _vec3_cross(ray->dir, edge2);
    a = _vec3_dot(edge1, h);
    if (a > -EPSILON && a < EPSILON) return false; // parallel
    
    f = 1.0 / a;
    vec3 s = _vec3_sub(ray->orig, vertex0);
    u = f * _vec3_dot(s, h);
    vec3 q = _vec3_cross(s, edge1);
    v = f * _vec3_dot(ray->dir, q);
    if ((u < 0.0 ) | (u > 1.0) | (v < 0.0) | (u + v > 1.0)) return false;

    float t = f * _vec3_dot(edge2, q);
    if (t > EPSILON && t < tMax && t > tMin) {
        *outHit = hit3D_new(t, n);
        return true;
    }
    return false;
}
