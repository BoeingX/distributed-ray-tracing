//
// Created by bysong on 26/04/15.
//

#ifndef PROJET_SPHERE_H
#define PROJET_SPHERE_H


#include "Color.h"
#include "Vector.h"
#include <cmath>

class Sphere {
private:
    Vector center;
    double radius;
    Color color;
    double r;
public:
    Sphere(const Vector& center, double radius, const Color &color, double r = 0.05);
    Sphere(const Vector& center, double radius, double r = 0.05);
    Sphere();
    const Vector& getCenter() const;
    const double getRadius() const;
    const unsigned short getRed() const;
    const unsigned short getBlue() const;
    const unsigned short getGreen() const;
    const Color& getColor() const;

    //determine if the sphere intersects another one
    const bool isIntersect(const Sphere &sphere) const;
    const double getR() const;
};

#endif //PROJET_SPHERE_H
