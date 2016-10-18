//
// Created by bysong on 27/04/15.
//

#ifndef PROJET_POSITION_H
#define PROJET_POSITION_H


#include <iostream>
#include "Color.h"


class Position {
private:
    double x;
    double y;
    double z;
    Color color;
public:
    Position();
    Position(double x,double y, double z);
    Position(double x,double y, double z, const Color &color);
    double getX() const;
    double getY() const;
    double getZ() const;
    double distanceTo(const Position &position) const;
    friend std::ostream& operator<<(std::ostream& out, const Position& vec);
    void setColor(const Color& color);
    const Color& getColor() const;
};


#endif //PROJET_POSITION_H
