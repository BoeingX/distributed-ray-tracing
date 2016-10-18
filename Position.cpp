//
// Created by bysong on 27/04/15.
//

#include "Position.h"
#include <cmath>
Position::Position(){
    x=0;y=0,z=0;color=Color(255,255,255);
}
Position::Position(double x,double y,double z){
    this->x = x;
    this->y = y;
    this->z = z;
    color = Color(255,255,255);
}
Position::Position(double x,double y,double z, const Color& color):x(x),y(y),z(z),color(color){}

double Position::getX() const{
    return x;
}

double Position::getY() const{
    return y;
}

double Position::getZ() const{
    return z;
}

double Position::distanceTo(const Position &position) const {
    return sqrt((x-position.getX())*(x-position.getX()) +
                        (y-position.getY())*(y-position.getY())+
                        (z-position.getZ())*(z-position.getZ()));
}

std::ostream& operator<< (std::ostream& out, const Position& vec){
    out<<"("<<vec.getX()<<","<<vec.getY()<<","<<vec.getZ()<<")";
    return out;
}

void Position::setColor(const Color &color) {
    this->color = color;
}

const Color& Position::getColor() const {return color; }