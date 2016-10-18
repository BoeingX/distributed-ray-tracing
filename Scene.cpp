//
// Created by bysong on 26/04/15.
//

#include "Scene.h"
#include <stdlib.h>
#include <ctime>
#include <limits>

const Color blue(0,0,255);
const Color red(255,0,0);
const Color green(0,255,0);
const Color orange(255,127,0);
const Color yellow(255,255,0);
const Color indigo(75,0,130);
const Color violet(143,0,255);
const double epsilon = std::numeric_limits<double>::epsilon();
Scene::Scene(const Vector &center, double width, double height, double distance_to_screen):
        center(center), width(width), height(height), distance_to_screen(distance_to_screen), ground(Plane(Vector(0,0,-4.5),Vector(0,0,1))){
}

void Scene::addSphere(const Sphere& sphere) {
    bool intersectWithOthers = false;
    for(int i = 0; i < this->numberSpheres(); i++){
        if(sphere.isIntersect(scene[i])) {
            intersectWithOthers = true;
            break;
        }
    }
    if(intersectWithOthers)
        std::cout<<"Error : Intersect with spheres existed"<<std::endl;
    else
        scene.push_back(sphere);
}

const int Scene::numberSpheres() const {
    return scene.size();
}

const std::vector<Sphere>& Scene::getScene() const{
    return scene;
}

void Scene::addSphere(int n, double focus_length) {
    int length_h = width;
    int length_v = height;
    int depth = length_v;
    srand(time(0));
    while(this->numberSpheres()<n){
        bool intersectWithOthers = false;
        int radius = 5*rand()%2;
        Vector center(rand()%length_h, rand()%length_v, rand()%depth);

        Sphere toAdd(center, radius);
        for(int i = 0; i < this->numberSpheres(); i++){
            if(toAdd.isIntersect(scene[i]))
                intersectWithOthers = true;
        }
        if(intersectWithOthers)
            continue;
        else
            this->addSphere(toAdd);
    }
}

const Plane& Scene::getGround() const {return ground; }

double zeroone(){
	return (random() / (double) RAND_MAX);
}

int seven(){
	return random()%7;
}
void Scene::addSphereOnGround(int n, const Vector& eye, double width, double height){
    srand(time(0));
    std::vector<Color> rainbow;
    rainbow.push_back(red);rainbow.push_back(orange);rainbow.push_back(yellow);
    rainbow.push_back(green);rainbow.push_back(blue);rainbow.push_back(indigo);
    rainbow.push_back(violet);

    while(this->numberSpheres() < n){
        bool intersectWithOthers = false;
        double y= distance_to_screen  + zeroone()*n*0.7;

        double z = 0.3 + 0.3*height*zeroone() - 0.5*height;

        double x = 1.2*(width*zeroone())-0.6*width;
        Color color = rainbow[seven()];
        unsigned short r = color.getRed() > 0 ? color.getRed() + 2*seven() - 7 : 0;
        unsigned short b = color.getBlue() > 0 ? color.getBlue() + 2*seven() - 7 : 0;
        unsigned short g = color.getGreen() > 0 ? color.getGreen() + 2*seven() - 7 : 0;
        Sphere toAdd(Vector(x,y,z), z + height/2, Color(r,g,b));
        for(int i = 0; i < this->numberSpheres(); i++){
            if(toAdd.isIntersect(scene[i])) {
                intersectWithOthers = true;
                break;
            }
        }
        if(intersectWithOthers)
            continue;
        else
            this->addSphere(toAdd);
    }

}
