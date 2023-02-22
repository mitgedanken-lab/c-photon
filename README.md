# photon

> Rays and geometries for graphics and physics in 2D and 3D.
> Various implementations of ray casting and intersections algorithms between
> different primitives.

* 2D and 3D Ray Casting
* 2D and 3D Triangle Implementations
* Basic Shapes and Intersection Algorithms

> The complete API can be found in the single header of the library, photon.h.

## Example

```C

#include <photon.h>

/* Check if a ray intersects a triangle in 3D */

int main(void)
{
    /* ... */

    Hit3D hit;
    Ray3D ray = ray3D_new(origin, direction);
    Tri3D tri = {p1, p2, p3};

    if (tri2D_hit(&tri, &ray, &hit)) {
        vec3 p = ray3D_at(&ray, hit.t);
        printf("Hit At: %f, %f, %f\n", p.x, p.y, p.z);
        printf("Normal: %f, %f, %f\n", hit.normal.x, hit.normal.y, hit.normal.z);
    } else {
        printf("Ray did not hit triangle\n");
    }
    
    return 0;
}

```

## Dependencies

> The single project on which photon depend is pretty tiny and depends only
> on the standard C math library, so it can be built easily.

* [fract](https://github.com/LogicEu/fract.git): Small 2D and 3D math library for games and graphics

## Clone

> Be sure to clone [fract](https://github.com/LogicEu/fract.git) into the
> repository, otherwise you won't be able to link successfully.

```shell
git clone --recursive https://github.com/LogicEu/photon.git
```

## Build

> You can compile the library with either of the two build scripts in this repo
> using make or bash. The compiled library will be placed at /bin

```shell
make all -j # or ./build.sh all
```
> There is a simple installation function that builds the
> library and puts it in the /usr/local directory:

```shell
sudo make install # or sudo ./build.sh install
```

> Clean object files and binaries created during compilation in /tmp 
> and /bin with:

```shell
make clean # or ./build.sh clean
```

