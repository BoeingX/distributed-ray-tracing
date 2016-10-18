//
// Created by bysong on 26/04/15.
//

#include "Light.h"
#include "Vector.h"
const Color ia = Color(250,250,210);
Light::Light(const Vector &position):position(position){
    is = Color(255,255,255);
    id = Color(150,150,150);
    this->ia = ia;

}
Light::Light(const Vector &position, const Color &is, const Color &id):position(position),is(is),id(id) {
    this->ia = ia;
}
const Color& Light::getIa() const {return ia;}
const Color& Light::getId() const {return id;}
const Color& Light::getIs() const {return is;}
const Vector& Light::getPosition() const {return position; }