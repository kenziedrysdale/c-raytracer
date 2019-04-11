#ifndef RAY_H
#define RAY_H
using namespace OpenGP;

class ray{
    public:
        ray(){}
        ray(const Vec3& a,const Vec3& b) {A = a; B=b/b.norm(); }
        Vec3 origin() const {return A;}
        Vec3 direction() const {return B;}
        Vec3 pointAtValue(float t) const {return A + (t*B);}
        Vec3 A;
        Vec3 B;
};
#endif // RAY_H
