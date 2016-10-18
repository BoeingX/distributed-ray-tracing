//
// Created by bysong on 26/04/15.
//

#include <stdexcept>
#include "Sphere.h"
#include <limits>
#include <stdlib.h>
#include <time.h>
const double epsilon = std::numeric_limits<double>::epsilon();

Sphere::Sphere() { }
Sphere::Sphere(const Vector &center, double radius, double r):center(center),radius(radius),r(r){
    srand(time(0));
    color = Color(random()%255,random()%255,random()%255);
}
Sphere::Sphere(const Vector &center, double radius, const Color &color, double r):
        center(center), radius(radius),color(color), r(r){
    if (radius < 0)
        throw std::invalid_argument("Received negative radius value. ");
}

const unsigned short Sphere::getBlue() const {
    return color.getBlue();
}

const unsigned short Sphere::getGreen() const {
    return color.getGreen();
}

const unsigned short Sphere::getRed() const {
    return color.getRed();
}

const Vector& Sphere::getCenter() const {
    return center;
}

const double Sphere::getRadius() const {
    return radius;
}

const bool Sphere::isIntersect(const Sphere &sphere) const {
    return (this->getCenter().distanceTo(sphere.getCenter())) - (this->getRadius() + sphere.getRadius()) <= epsilon;
}

const Color& Sphere::getColor() const {return color; }

const double Sphere::getR() const {return r; }
