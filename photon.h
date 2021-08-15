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

/*
-----------
 -> Rect <- 
-----------
*/

Rect rect_new(float x, float y, float w, float h);
bool rect_point_overlap(vec2 v, Rect r);
bool rect_point_overlap_offset(vec2 v, Rect r, vec2 offset);
bool rect_overlap(Rect r1, Rect r2);
bool rect_overlap_offset(Rect r1, Rect r2, vec2 offset);

#ifdef __cplusplus
}
#endif
#endif
