#ifndef CAMERA_H
#define CAMERA_H
#include "ray.h"
class camera{
    public:
        camera(){
            Vec3 lowerLeftCorner(-2.0,-1.0,-1.0);
            Vec3 horizontal(4.0,0.0,0.0);
            Vec3 vertical(0.0,2.0,0.0);
            Vec3 origin(0.0,0.0,0.0);
        }
        ray getRay(float u, float v){return ray(origin, lowerLeftCorner+u*horizontal+v*vertical - origin); }

        Vec3 origin;
        Vec3 lowerLeftCorner;
        Vec3 horizontal;
        Vec3 vertical;
};



#endif // CAMERA_H
