//
// Created by bysong on 17/05/15.
//

#include "Plane.h"
Plane::Plane(const Vector &point, const Vector &normal):normal(normal) {
    A = normal.getX();
    B = normal.getY();
    C = normal.getZ();
    D = -normal.dotProduct(point);
}

double Plane::getA() const {return A; }
double Plane::getB() const {return B; }
double Plane::getC() const {return C; }
double Plane::getD() const {return D; }
const Vector& Plane::getNormal() const {return normal; }