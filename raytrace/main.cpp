#include "OpenGP/Image/Image.h"
#include "bmpwrite.h"
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "hitableList.h"
#include "colour.h"

using namespace OpenGP;
using Colour = Vec3; // RGB Value
//width must be twice height because of how camera is defined
const int wResolution = 600;
const int hResolution = 300;
const int sample = 15;
extern int maxDepth = 20;
extern float ambientLighting =1.0;
extern Vec3 lightPos(0,0.9,-2);
extern float lightIntensity = 1.0;



int main(int, char**){
    // #rows = hResolution, #cols = wResolution
    Image<Colour> image(hResolution, wResolution);
    Vec3 lowerLeftCorner(-2.0,-1.0,-1.0);
    Vec3 horizontal(4.0,0.0,0.0);
    Vec3 vertical(0.0,2.0,0.0);
    Vec3 origin(0.0,0.0,0.0);
    hitable *list[2];
    list[0] = new sphere(Vec3(0,-0.5,-2),0.5,Vec3(0,0.3,0.3),Vec3(0,0.3,0.3),Vec3(0,0.3,0.3),400,0);
    //floor y=-1, white
    list[1] = new plane(Vec3(0,1,0),Vec3(0,-1,0),Vec3(0.1,0.1,0.1),Vec3(0.1,0.1,0.1),Vec3(0.1,0.1,0.1),400,3);


    hitable *world = new hitableList(list,2);

    for (int row = 0; row < image.rows(); ++row) {
        for (int col = 0; col < image.cols(); ++col) {
            Vec3 colourVal(0.0f,0.0f,0.0f);
            for(int s = 0;s < sample; s++){
                float u = float(col + drand48())/float(wResolution);
                float v = float(row + drand48())/float(hResolution);
                ray r(origin,lowerLeftCorner + u*horizontal+v*vertical);
                colourVal += colour(r,world,0);
            }
                image(row,col) = (colourVal/sample);
       }
    }

    bmpwrite("../../out.bmp", image);
    imshow(image);

    return EXIT_SUCCESS;
}




