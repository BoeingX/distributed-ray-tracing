//
// Created by bysong on 27/04/15.
//

#ifndef PROJET_CAMERA_H
#define PROJET_CAMERA_H


#include "Vector.h"
#include <vector>

class Camera {
private:
    Vector eye;
    Vector target;
    Vector upVector;
    std::vector<std::vector<Vector> > screen;
    double height;
    double width;

    //number of pixels on horizontal and vertical direction
    int nbr_h;
    int nbr_v;
public:
    Camera(const Vector &eye, const Vector &upVector, double height, double width, int nbr_h = 1000, int nbr_v = 1000);
    Vector& getEye();
    void setTarget(const Vector &position);
    int getNbr_h();
    int getNbr_v();
    std::vector<std::vector<Vector> >& getScreen();
    Vector& getTarget();

    //write to BMP image
    void toImg(int resolution_h, int resolution_v, int depth, bool writeToFile, const char* filename) const;
};


#endif //PROJET_CAMERA_H
