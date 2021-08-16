#include <photon.h>

vec3 vec3_reflect(vec3 v, vec3 n)
{
    float f = 2.0 * _vec3_dot(v, n);
    vec3 ret = {v.x - n.x * f, v.y - n.y * f, v.z - n.z * f};
    return ret;
}

bool vec3_refract(vec3 v, vec3 n, float nint, vec3* outRefracted)
{
    float dt = _vec3_dot(v, n);
    float discr = 1.0f - nint * nint * (1.0f - dt * dt);
    if (discr > 0.0) {
        vec3 tmp = {(v.x - n.x * dt) * nint, (v.y - n.y * dt) * nint, (v.z - n.z * dt) * nint};
        *outRefracted = vec3_sub(tmp, vec3_mult(n, sqrtf(discr)));
        return true;
    }
    return false;
}