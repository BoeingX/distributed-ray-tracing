//
// Created by bysong on 26/04/15.
//
#include "Vector.h"
#include <cmath>
Vector::Vector(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
    color=Color(255,255,255);
}
Vector::Vector(){
    x=0;y=0,z=0;color=Color(255,255,255);
}

Vector::Vector(double x,double y,double z, const Color& color):x(x),y(y),z(z),color(color){}

double Vector::getX() const{
    return this->x;
}

double Vector::getY() const{
    return this->y;
}

double Vector::getZ() const{
    return this->z;
}
//Calculate squared magnitude of a vector
double Vector::normeSquared() const{
      return (this->x*this->x) + (this->y*this->y) + (this->z*this->z);
}

double Vector::norme() const{
      return sqrt(normeSquared());
}

Vector Vector::UnitVector() const{
       const double norm=norme();
       return Vector(x/norm,y/norm,z/norm);
}

Vector Vector::operator + (const Vector &a) const {
       return Vector(a.x+this->x,a.y+this->y,a.z+this->z);
}

Vector Vector::operator - (const Vector &a) const{
       return Vector(this->x-a.x,this->y-a.y,this->z-a.z);
}

Vector Vector::operator * (double s) const {
       return Vector(s*this->x, s*this->y, s*this->z);
}

Vector Vector::operator / (double s) const {
       return Vector(this->x/s,this->y/s,this->z/s);
}

Vector Vector::operator - () const {
       return Vector(-this->x,-this->y,-this->z);
}

double Vector::dotProduct (const Vector& a) const{
       return (this->x*a.x)+(this->y*a.y)+(this->z*a.z);
}

Vector Vector::crossProduct (const Vector& a) const{
       return Vector(
            (this->y * a.z) - (this->z * a.y), 
            (this->z * a.x) - (this->x * a.z), 
            (this->x * a.y) - (this->y * a.x));
}

double Vector::distanceTo(const Vector& a) const{
       return Vector(this->x-a.x,this->y-a.y,this->z-a.z).norme();
}

bool Vector::isNull() const{
    return x==0 && y==0 && z==0;
}

std::ostream& operator<< (std::ostream& out, const Vector& vec){
    out<<"("<<vec.getX()<<","<<vec.getY()<<","<<vec.getZ()<<")"<<vec.getColor();
    return out;
}

void Vector::setColor(const Color &color) {
    this->color = color;
}

const Color& Vector::getColor() const {return color; }

void Vector::setR(const unsigned short r) {color.setRed(r); }
void Vector::setG(const unsigned short g) {color.setGreen(g); }
void Vector::setB(const unsigned short b) {color.setBlue(b); }

