#include <photon.h>

vec3 random_in_disk()
{
    vec3 p = {randf_signed(), randf_signed(), 0.0};
    return p;
}

vec3 random_in_sphere()
{
    vec3 p = {randf_signed(), randf_signed(), randf_signed()};
    return p;
}