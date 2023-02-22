#include <photon.h>

static inline float fmin3(float a, const float b, const float c)
{
    a = a <= b ? a : b;
    return a <= c ? a : c;
}

static inline float fmax3(float a, const float b, const float c)
{
    a = a >= b ? a : b;
    return a >= c ? a : c;
}

static inline void fswap(float* restrict a, float* restrict b)
{
    float tmp = *b;
    *b = *a;
    *a = tmp;
}

Box3D box3D_new(const vec3 min, const vec3 max)
{
    Box3D box = {min, max};
    return box;
}

Box3D box3D_move(const Box3D box, const vec3 v)
{
    return (Box3D) {
        _vec3_add(box.min, v),
        _vec3_add(box.max, v)
    };
}

Box3D box3D_from_triangle(const Tri3D* t)
{
    return (Box3D){
        {fmin3(t->a.x, t->b.x, t->c.x), fmin3(t->a.y, t->b.y, t->c.y), fmin3(t->a.z, t->b.z, t->c.z)},
        {fmax3(t->a.x, t->b.x, t->c.x), fmax3(t->a.y, t->b.y, t->c.y), fmax3(t->a.z, t->b.z, t->c.z)}
    };
}

Box3D box3D_from_mesh(const vec3* v, const size_t count)
{
    /*                min                max              */
    Box3D box = {_vec3_uni(1000.0), _vec3_uni(-1000.0)};

    for (size_t i = 0; i < count; ++i, ++v) {
        
        if (v->x < box.min.x) box.min.x = v->x;
        if (v->y < box.min.y) box.min.y = v->y;
        if (v->z < box.min.z) box.min.z = v->z;

        if (v->x > box.max.x) box.max.x = v->x;
        if (v->y > box.max.y) box.max.y = v->y;
        if (v->z > box.max.z) box.max.z = v->z;

    }

    return box;
}

bool box3D_overlap(const Box3D a, const Box3D b)
{
    return (
        a.min.x <= b.max.x &&
        a.max.x >= b.min.x &&
        a.min.y <= b.max.y &&
        a.max.y >= b.min.y &&
        a.min.z <= b.max.z &&
        a.max.z >= b.min.z
    );
}

bool box3D_hit(const Box3D* restrict box, const Ray3D* restrict ray, Hit3D* restrict outHit)
{
    float tmin = (box->min.x - ray->orig.x) / ray->dir.x; 
    float tmax = (box->max.x - ray->orig.x) / ray->dir.x; 
 
    if (tmin > tmax) {
        fswap(&tmin, &tmax);
    }
 
    float tymin = (box->min.y - ray->orig.y) / ray->dir.y; 
    float tymax = (box->max.y - ray->orig.y) / ray->dir.y; 
 
    if (tymin > tymax) {
        fswap(&tymin, &tymax); 
    }
 
    if ((tmin > tymax) || (tymin > tmax)) {
        return false; 
    }
 
    if (tymin > tmin) {
        tmin = tymin; 
    }
 
    if (tymax < tmax) {
        tmax = tymax; 
    }
 
    float tzmin = (box->min.z - ray->orig.z) / ray->dir.z; 
    float tzmax = (box->max.z - ray->orig.z) / ray->dir.z; 
 
    if (tzmin > tzmax) {
        fswap(&tzmin, &tzmax);
    } 
 
    if ((tmin > tzmax) || (tzmin > tmax)) {
        return false; 
    }
 
    if (tzmin > tmin) {
        tmin = tzmin; 
    }
 
    if (tzmax < tmax) {
        tmax = tzmax; 
    }
 
    outHit->t = tmin;
    
    vec3 p = _ray3D_at(ray, tmin);
    vec3 min = _vec3_sub(p, box->min);
    vec3 max = _vec3_sub(p, box->max);

    vec3 d = {
        absf(min.x) < absf(max.x) ? -absf(min.x) : absf(max.x),
        absf(min.y) < absf(max.y) ? -absf(min.y) : absf(max.y),
        absf(min.z) < absf(max.z) ? -absf(min.z) : absf(max.z)
    };

    if (absf(d.x) < absf(d.y) && absf(d.x) < absf(d.z)) {
        outHit->normal = vec3_new(signf(d.x), 0.0, 0.0);
    } else if (absf(d.y) < absf(d.x) && absf(d.y) < absf(d.z)) {
        outHit->normal = vec3_new(0.0, signf(d.y), 0.0);
    } else {
        outHit->normal = vec3_new(0.0, 0.0, signf(d.z));
    }

    return true; 
}

bool box3D_hit_fast(const Box3D* restrict box, const Ray3D* restrict ray, float* restrict tOut)
{
    float tmin = (box->min.x - ray->orig.x) / ray->dir.x; 
    float tmax = (box->max.x - ray->orig.x) / ray->dir.x; 
 
    if (tmin > tmax) {
        fswap(&tmin, &tmax);
    }
 
    float tymin = (box->min.y - ray->orig.y) / ray->dir.y; 
    float tymax = (box->max.y - ray->orig.y) / ray->dir.y; 
 
    if (tymin > tymax) {
        fswap(&tymin, &tymax); 
    }
 
    if ((tmin > tymax) || (tymin > tmax)) {
        return false; 
    }
 
    if (tymin > tmin) {
        tmin = tymin; 
    }
 
    if (tymax < tmax) {
        tmax = tymax; 
    }
 
    float tzmin = (box->min.z - ray->orig.z) / ray->dir.z; 
    float tzmax = (box->max.z - ray->orig.z) / ray->dir.z; 
 
    if (tzmin > tzmax) {
        fswap(&tzmin, &tzmax);
    } 
 
    if ((tmin > tzmax) || (tzmin > tmax)) {
        return false; 
    }
 
    if (tzmin > tmin) {
        tmin = tzmin; 
    }
 
    *tOut = tmin;
    return true; 
}
