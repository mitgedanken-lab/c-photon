#ifndef PHOTON_PHYSICS_H
#define PHOTON_PHYSICS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
=================================================
>>>>>>>>>>>>>>  PHOTON PHYSICS    >>>>>>>>>>>>>>>
Ray casting and primitive shapes for graphics and
physics calculations.
=======================================  @eulogic
*/

#include <stdbool.h>
#include <fract.h>

typedef struct Rect {
    float x, y, w, h;
} Rect;

typedef struct Ray2D {
    vec2 orig;
    vec2 dir;
} Ray2D;

typedef struct Ray3D {
    vec3 orig;
    vec3 dir;
} Ray3D;

typedef struct Hit3D {
    vec3 pos;
    vec3 normal;
    float t;
} Hit3D;

typedef struct Sphere {   
    vec3 pos;
    float radius;
} Sphere;

typedef struct Tri2D {
    vec2 a, b, c;
} Tri2D;

typedef struct Tri3D {
    vec3 a, b, c, n;
} Tri3D;

/********
 -> 2D <- 
********/

Rect rect_new(float x, float y, float w, float h);
bool rect_point_overlap(vec2 v, Rect r);
bool rect_point_overlap_offset(vec2 v, Rect r, vec2 offset);
bool rect_overlap(Rect r1, Rect r2);
bool rect_overlap_offset(Rect r1, Rect r2, vec2 offset);

/********
 -> 3D <- 
********/

vec3 vec3_reflect(vec3 v, vec3 n);
bool vec3_refract(vec3 v, vec3 n, float nint, vec3* outRefracted);

vec3 random_in_disk();
vec3 random_in_sphere();

Ray3D ray3D_new(vec3 orig, vec3 dir);
vec3 ray3D_at(const Ray3D* ray, float t);

bool sphere_hit(const Sphere* sphere, const Ray3D* ray, Hit3D* outHit, float tMin, float tMax);
bool tri3D_hit(const Tri3D* tri, const Ray3D* ray, Hit3D* outHit, float tMin, float tMax);
vec3 tri3D_norm(const Tri3D* tri);

#ifdef __cplusplus
}
#endif
#endif
