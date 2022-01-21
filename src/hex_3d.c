#include <photon.h>

Hex3D hex3D_new(vec3 dimension, vec3 position)
{
    Hex3D h = {dimension, position};
    return h;
}

bool hex3D_overlap(Hex3D a, Hex3D b)
{
    vec3 da = vec3_mult(a.dimension, 0.5);
    vec3 db = vec3_mult(b.dimension, 0.5);
    vec3 pa = a.position;
    vec3 pb = b.position;
    
    return  (pa.x - da.x < pb.x + db.x) &&
            (pa.x + da.x > pb.x - db.x) &&
            (pa.y - da.y < pb.y + db.y) &&
            (pa.y + da.y > pb.y - db.y) &&
            (pa.z - da.z < pb.z + db.z) &&
            (pa.z + da.z > pb.z - db.z);
}