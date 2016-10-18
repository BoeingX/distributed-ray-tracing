//
// Created by bysong on 17/05/15.
//

#ifndef PROJET_PLANE_H
#define PROJET_PLANE_H


#include "Vector.h"

class Plane {
private:
    //Ax+By+Cz+D=0
    double A, B, C, D;
    //normal vector of the plane
    Vector normal;
public:
    Plane(const Vector &point, const Vector &normal);
    double getA() const;
    double getB() const;
    double getC() const;
    double getD() const;
    const Vector& getNormal() const;
};


#endif //PROJET_PLANE_H
