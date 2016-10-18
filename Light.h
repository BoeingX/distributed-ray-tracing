//
// Created by bysong on 26/04/15.
//

#ifndef PROJET_LIGHT_H
#define PROJET_LIGHT_H


#include "Vector.h"
#include "Color.h"

class Light {
private:
    Vector position;
    Color is;
    Color id;

    //ia is the ambient light, but to simplify the syntax, we consider it as a composant of light.
    Color ia;
public:
    Light(const Vector &position);
    Light(const Vector &position, const Color &is, const Color &id);
    const Color& getIs() const;
    const Color& getId() const;
    const Color& getIa() const;
    const Vector& getPosition() const;
};


#endif //PROJET_LIGHT_H
