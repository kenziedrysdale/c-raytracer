#ifndef PLANE_H
#define PLANE_H
#include "hitable.h"
#include "material.h"

class plane : public hitable{
    public :
        plane(){}
        plane(Vec3 normal,Vec3 origin,Vec3 ambientColour,Vec3 diffuseColour,Vec3 specularColour,int phong,int material) : normal(normal), origin(origin),ambientColour(ambientColour),diffuseColour(diffuseColour),specularColour(specularColour),phong(phong),material(material) {};
        virtual bool hit(const ray& r,float tMin,float tMax,hitRecord& rec) const;
        Vec3 normal;
        Vec3 origin;
        Vec3 ambientColour;
        Vec3 diffuseColour;
        Vec3 specularColour;
        int phong;
        int material;

};

bool plane::hit(const ray& r, float t_min, float t_max, hitRecord& rec) const {
    float denom = (r.direction()).dot(normal/normal.norm());
    if (denom != 0){
        float t = ((origin- r.origin()).dot(normal/normal.norm()))/denom;
        if(t <= 0){
            return false;
        }
        if (t < t_max && t > t_min) {
            rec.t = t;
            rec.p = r.pointAtValue(rec.t);
            rec.normal = normal;
            rec.ambientColour = ambientColour;
            rec.diffuseColour = diffuseColour;
            rec.specularColour = specularColour;
            rec.phong = phong;
            rec.material = material;
            return true;
        }
    }
    return false;
};


#endif // PLANE_H



