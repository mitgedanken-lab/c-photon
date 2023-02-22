#include <photon.h>

vec2 vec2_rand(void)
{
    return (vec2){frand_signed(), frand_signed()};
}

vec3 vec3_rand(void)
{
    return (vec3){frand_signed(), frand_signed(), frand_signed()};
}

vec2 vec2_reflect(const vec2 v, const vec2 n)
{
    const float f = 2.0 * _vec2_dot(v, n);
    return (vec2){v.x - n.x * f, v.y - n.y * f};
}

vec3 vec3_reflect(const vec3 v, const vec3 n)
{
    const float f = 2.0 * _vec3_dot(v, n);
    return (vec3){v.x - n.x * f, v.y - n.y * f, v.z - n.z * f};
}

bool vec3_refract(const vec3 v, const vec3 n, const float nint, vec3* outRefracted)
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
