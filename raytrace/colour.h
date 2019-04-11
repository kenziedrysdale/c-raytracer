#ifndef COLOUR_H
#define COLOUR_H
#include <math.h>
extern float ambientLighting;
extern int maxDepth;
extern Vec3 lightPos;
extern float lightIntensity;


bool isShaded(Vec3 pt,hitable *world,Vec3 lightPos){
    hitRecord rec;
    float lightDist = (lightPos - pt).norm();
    ray r(pt,lightPos - pt);
    if(world->hit(r,0.001,lightDist,rec)){
        return true;
    }
    else{
        return false;
    }
}


Vec3 colour(const ray& r,hitable *world,int depth){
    hitRecord rec;
    if(world->hit(r,0.001,MAXFLOAT,rec)){
        Vec3 pt = rec.p;
        Vec3 n = rec.normal/(rec.normal.norm());
        Vec3 shadRec;
        //diffuse model
        if(rec.material == 0){
            //ambient
            shadRec = rec.ambientColour*ambientLighting;
            if(isShaded(pt,world,lightPos) == false){
                //lambertian
                Vec3 l = ((lightPos-pt)/(lightPos-pt).norm());
                shadRec += rec.diffuseColour*lightIntensity*fmax(0,n.dot(l));
                //specular
                Vec3 vNorm = (-r.pointAtValue(rec.t))/(-r.pointAtValue(rec.t)).norm();
                Vec3 h = (vNorm+l)/((vNorm+l).norm());
                h /=h.norm();
                shadRec += pow(n.dot(h),rec.phong)*rec.specularColour*lightIntensity;
                return shadRec;
          }
          return shadRec;
        }
        //reflective model
        if(rec.material == 1){
            if(depth >= maxDepth)
                return Vec3(0.5,0.7,1);
            Vec3 reflectDirection = (pt - r.origin()) -2*(pt - r.origin()).dot(n)*n;
            ray reflectRay(pt,reflectDirection);
            return 0.8 * colour(reflectRay,world,depth+1);
        }
        //reafraction model
        if(rec.material == 2){
            Vec3 nRefraction = n;
            float nDotI = nRefraction.dot(rec.p - r.origin());
            float etai = 1;
            float etat = 1.5;
            if(nDotI < 0){
                nDotI = - nDotI;
            }else{
                nRefraction = -n;
                std::swap(etai,etat);
            }
            float eta = etai/etat;
            float cosi = n.dot(rec.p - r.origin());
            if (cosi > 1){
                cosi = 1;
            }
            if (cosi < -1){
                cosi = -1;
            }

            float k = 1 - eta * eta*(1 - cosi*cosi);
            Vec3 vRefract;
            if (k < 0)
                vRefract = Vec3(0,0,0);
           vRefract = eta * (rec.p - r.origin()) + (eta * nDotI - sqrtf(k)) * nRefraction;
           ray refractRay(rec.p,vRefract+r.direction());
           return colour(refractRay,world,depth+1);
      }
        //checker diffuse
        if(rec.material == 3){
            //ambient
            shadRec = rec.ambientColour*ambientLighting;
            int xPoint = int (rec.p.x());
            int zPoint = int (rec.p.z());

            if((xPoint+zPoint)%2 && rec.p.x() > 0)
                shadRec+= Vec3(0.5,0.5,0.5);
            if((xPoint+zPoint+1)%2 && rec.p.x() < 0)
                shadRec+= Vec3(0.5,0.5,0.5);
            if(isShaded(pt,world,lightPos) == false){
                //lambertian
                Vec3 l = ((lightPos-pt)/(lightPos-pt).norm());
                shadRec += rec.diffuseColour*lightIntensity*fmax(0,n.dot(l));
                //specular
                Vec3 vNorm = (-r.pointAtValue(rec.t))/(-r.pointAtValue(rec.t)).norm();
                Vec3 h = (vNorm+l)/((vNorm+l).norm());
                h /=h.norm();
                shadRec += pow(n.dot(h),rec.phong)*rec.specularColour*lightIntensity;
                return shadRec;
          }
          return shadRec;
        }


        }


    //linear interpolation for a sky background
    else{
        return Vec3(0.5,0.7,1.0);
    }
};
#endif // COLOUR_H
