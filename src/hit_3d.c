#include <photon.h>

Hit3D hit3D_new(float t, vec3 normal)
{
    Hit3D hit = {t, normal};
    return hit;
}