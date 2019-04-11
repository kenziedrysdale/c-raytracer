#ifndef SPHERE_H
#define SPHERE_H
#include "hitable.h"
#include "material.h"


class sphere : public hitable{
    public :
        sphere(){}
        sphere(Vec3 cen, float r,Vec3 ambientColour,Vec3 diffuseColour,Vec3 specularColour,int phong,int material) : centre(cen), radius(r),ambientColour(ambientColour),diffuseColour(diffuseColour),specularColour(specularColour),phong(phong),material(material) {};
        virtual bool hit(const ray& r,float tMin,float tMax,hitRecord& rec) const;
        Vec3 centre;
        float radius;
        Vec3 ambientColour;
        Vec3 diffuseColour;
        Vec3 specularColour;
        int phong;
        int material;
        float n = 1.5;

};

bool sphere::hit(const ray& r, float t_min, float t_max, hitRecord& rec) const {
    Vec3 oc = r.origin() - centre;
    float a = (r.direction().dot(r.direction()));
    float b = oc.dot(r.direction());
    float c = oc.dot(oc) - radius*radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant))/a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.pointAtValue(rec.t);
            rec.normal = (rec.p - centre) / radius;
            rec.ambientColour = ambientColour;
            rec.diffuseColour = diffuseColour;
            rec.specularColour = specularColour;
            rec.phong = phong;
            rec.material = material;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.pointAtValue(rec.t);
            rec.normal = (rec.p - centre) / radius;
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




#endif // SPHERE_H
