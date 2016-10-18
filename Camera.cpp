//
// Created by bysong on 27/04/15.
//

#include <stdexcept>
#include <string>
#include "Camera.h"
#include "CImg.h"
using namespace cimg_library;
Camera::Camera(const Vector &eye, const Vector &upVector, double width, double height, int nbr_h, int nbr_v):
eye(eye), upVector(upVector), height(height), width(width), nbr_h(nbr_h), nbr_v(nbr_v) {
    if(height <=0 || width <= 0)
        throw std::invalid_argument("Screen dimension illegal!");
    target = Vector(0,0,0);
    double half_height = height/2;
    double half_width = width/2;
    double step_h = width/(nbr_h);
    double step_v = height/(nbr_v);

    for(int i = 0; i < nbr_v; i++){
        std::vector<Vector> toAdd;
        for(int j = 0; j < nbr_h; j++){
            toAdd.push_back(Vector(-half_width+j*step_h,0,half_height-i*step_v));
        }
        screen.push_back(toAdd);
    }
}


Vector& Camera::getEye() { return eye;}

void Camera::setTarget(const Vector &position) {
    this->target = position;
}

int Camera::getNbr_h() {return nbr_h;}
int Camera::getNbr_v() {return nbr_v;}

std::vector<std::vector<Vector> >& Camera::getScreen() {return screen; }
Vector& Camera::getTarget() {return target; }

void Camera::toImg(int resolution_h, int resolution_v, int depth, bool writeToFile, const char* filename) const{
    CImg<unsigned short> img(resolution_h,resolution_v,depth,3);
    for(int x = 0; x < img.width(); x++){
        for(int y = 0; y < img.height(); y++){
	        img(x,y,0,0) = screen[y][x].getColor().getRed();
            img(x,y,0,1) = screen[y][x].getColor().getGreen();
            img(x,y,0,2) = screen[y][x].getColor().getBlue();
        }
    }
    if(writeToFile) {
        img.save_bmp((filename+std::string(".bmp")).data());
    }
    else
        img.display(filename);
}
