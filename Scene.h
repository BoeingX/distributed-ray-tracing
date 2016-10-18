//
// Created by bysong on 26/04/15.
//
#include <vector>
#include "Sphere.h"
#include "Vector.h"
#include <ctime>
#include "Plane.h"

#ifndef PROJET_SCENE_H
#define PROJET_SCENE_H


class Scene {
private:
    Vector center;
    double width;
    double height;
    double distance_to_screen;
    std::vector<Sphere> scene;
    Plane ground;
public:
    Scene(const Vector &center, double width, double height, double distance_to_screen = 0.0);
    const int numberSpheres() const;
    const std::vector<Sphere>& getScene() const;
    void addSphere(int n, double focus_length);
    void addSphere(const Sphere& sphere);
    const Plane& getGround() const;
    void addSphereOnGround(int n, const Vector& eye, double width, double height);
};

//method to generate a uniform distribution from 0 to 1
double zeroone();

//method to generate 0, 1, 2, 3, 4, 5, 6 with equal probability
int seven();

#endif //PROJET_SCENE_H
