#ifndef HITABLE_H
#define HITABLE_H
#include "ray.h"
#include "material.h"

struct hitRecord{
    float t;
    Vec3 p;
    Vec3 normal;
    Vec3 ambientColour;
    Vec3 diffuseColour;
    Vec3 specularColour;
    int phong;
    int material;

};

class hitable {
    public:
        virtual bool hit(const ray& r,float tMin,float tMax,hitRecord& rec) const = 0;
};



#endif // HITABLE_H
