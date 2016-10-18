//
// Created by bysong on 26/04/15.
//
#ifndef PROJET_VECTOR_H
#define PROJET_VECTOR_H
#include <iostream>
#include "Color.h"
class Vector{
private:
    double x;
    double y;
    double z;
    Color color;
public:
    //constructor
    Vector();
    Vector(double x,double y,double z,const Color& color);
    Vector(double x, double y, double z);
    //get coordinates
    double getX() const;
    double getY() const;
    double getZ() const;
    //calculate squared norm and norm
    double normeSquared() const;
    double norme() const;
    //unitvector
    Vector UnitVector() const;
    //overload operator
    Vector operator + (const Vector &a) const ;
    Vector operator - (const Vector &a) const;
    //s*Vector, Vector/s
    Vector operator * (double s) const;
    Vector operator / (double s) const;
    //(-Vector)=-Vector
    Vector operator - () const ;
    //two products
    double dotProduct (const Vector& a) const;
    Vector crossProduct (const Vector& a) const;
    double distanceTo (const Vector& a) const;
    //determine if this is a zero vector
    bool isNull() const;
    //overload <<
    friend std::ostream& operator<<(std::ostream& out, const Vector& vec);

    void setColor(const Color& color);
    void setR(const unsigned short r);
    void setG(const unsigned short g);
    void setB(const unsigned short b);

    const Color& getColor() const;
};
#endif //PROJET_VECTOR_H
