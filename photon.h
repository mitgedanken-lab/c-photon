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

typedef struct Hit2D {
    float t;
    vec2 normal;
} Hit2D;

typedef struct Ray3D {
    vec3 orig;
    vec3 dir;
} Ray3D;

typedef struct Hit3D {
    float t;
    vec3 normal;
} Hit3D;

typedef struct Circle {
    vec2 pos;
    float radius;
} Circle;

typedef struct Sphere {   
    vec3 pos;
    float radius;
} Sphere;

typedef struct Tri2D {
    vec2 a, b, c;
} Tri2D;

typedef struct Tri3D {
    vec3 a, b, c;
} Tri3D;

#define _ray3D_at(ray, t) {ray->orig.x + ray->dir.x * t, ray->orig.y + ray->dir.y * t, ray->orig.z + ray->dir.z * t}
#define _ray2D_at(ray, t) {ray->orig.x + ray->dir.x * t, ray->orig.y + ray->dir.y * t}

/*******************
 -> Vec Extension <- 
*******************/

vec2 vec2_rand();
vec3 vec3_rand();
vec2 vec2_reflect(vec2 v, vec2 n);
vec3 vec3_reflect(vec3 v, vec3 n);
bool vec3_refract(vec3 v, vec3 n, float nint, vec3* outRefracted);

/********
 -> 2D <-
********/

Circle circle_new(vec2 pos, float radius);
bool circle_point_overlap(const Circle* circle, vec2 p);

Tri2D tri2D_new(vec2 a, vec2 b, vec2 c);
bool tri2D_point_overlap(const Tri2D* tri, vec2 p);

Rect rect_new(float x, float y, float w, float h);
bool rect_point_overlap(vec2 v, Rect r);
bool rect_point_overlap_offset(vec2 v, Rect r, vec2 offset);
bool rect_overlap(Rect r1, Rect r2);
bool rect_overlap_offset(Rect r1, Rect r2, vec2 offset);

Hit2D hit2D_new(float t, vec2 normal);
Ray2D ray2D_new(vec2 orig, vec2 dir);
vec2 ray2D_at(const Ray2D* ray, float t);

/********
 -> 3D <-
********/

Sphere sphere_new(vec3 pos, float radius);
bool sphere_hit(const Sphere* sphere, const Ray3D* ray, Hit3D* outHit);

Tri3D tri3D_new(vec3 a, vec3 b, vec3 c);
vec3 tri3D_norm(const Tri3D* tri);
bool tri3D_hit(const Tri3D* tri, const Ray3D* ray, Hit3D* outHit);
bool tri3D_hit_range(const Tri3D* tri, const Ray3D* ray, Hit3D* outHit, float tMin, float tMax);

Hit3D hit3D_new(float t, vec3 normal);
Ray3D ray3D_new(vec3 orig, vec3 dir);
vec3 ray3D_at(const Ray3D* ray, float t);

#ifdef __cplusplus
}
#endif
#endif
