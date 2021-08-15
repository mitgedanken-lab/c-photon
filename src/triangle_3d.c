#include <photon.h>

vec3 tri3D_norm(const Tri3D* restrict tri)
{
    vec3 e1 = vec3_sub(tri->b, tri->a);
    vec3 e2 = vec3_sub(tri->c, tri->a);
    return vec3_normal(vec3_cross(e1, e2)); 
}

bool tri3D_hit(const Tri3D* restrict tri, const Ray3D* restrict ray, Hit3D* outHit, float tMin, float tMax)
{ 
    float nRayDir = vec3_dot(tri->n, ray->dir);
    if (fabs(nRayDir) < 0.01) return false; // parallel

    // compute t (equation P = O + tR, where P is intersection point, O is ray origin and R its direction)
    float d = vec3_dot(tri->n, tri->a);
    float t = -(vec3_dot(tri->n, ray->orig) - d) / nRayDir; 

    if (t < tMin || t > tMax) return false; // triangle is outside depth field

    vec3 P = vec3_add(ray->orig, vec3_mult(ray->dir, t));
    
    outHit->pos = P;
    outHit->t = t;
    outHit->normal = tri->n;

    // Step 2: inside-outside test
    vec3 C; 

    vec3 edge0 = vec3_sub(tri->b, tri->a);
    vec3 vp0 = vec3_sub(P, tri->a);
    C = vec3_cross(edge0, vp0); 
    if (vec3_dot(tri->n, C) < 0) return false; // P is on the right side 


    vec3 edge1 = vec3_sub(tri->c, tri->b);
    vec3 vp1 = vec3_sub(P, tri->b);
    C = vec3_cross(edge1, vp1); 
    if (vec3_dot(tri->n, C) < 0) return false; // P is on the right side 

    vec3 edge2 = vec3_sub(tri->a, tri->c);
    vec3 vp2 = vec3_sub(P, tri->c); 
    C = vec3_cross(edge2, vp2);
    if (vec3_dot(tri->n, C) < 0) return false; // P is on the right side; 
    
    return true; // Hit!
} 