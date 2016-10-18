//
// Created by bysong on 26/04/15.
//
#include <cmath>
#include <stdexcept>
#include "Color.h"

Color::Color(unsigned short r, unsigned short g, unsigned short b){
    this->r = r;
    this->g = g;
    this->b = b;
}

void Color::setColor(const Color &color){
    Color::setColor(color.getRed(),color.getGreen(),color.getBlue());
}
void Color::setColor(unsigned short r, unsigned short g, unsigned short b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

void Color::setRed(unsigned short r) {
    this->r = r;
}

void Color::setGreen(unsigned short g) {
    this->g = g;
}

void Color::setBlue(unsigned short b) {
    this->b = b;
}

unsigned short Color::getRed() const {
    return r;
}

unsigned short Color::getGreen() const {
    return g;
}

unsigned short Color::getBlue() const {
    return b;
}


Color Color::operator + (const Color& color) const{
    unsigned short red = this->getRed() + color.getRed() > 255 ? 255 : this->getRed() + color.getRed();
    unsigned short blue = this->getBlue() + color.getBlue() > 255 ? 255 : this->getBlue() + color.getBlue();
    unsigned short green = this->getGreen() + color.getGreen() > 255 ? 255 : this->getGreen() + color.getGreen();
    return Color(red,green,blue);
}

Color Color::operator -(const Color& color) const{
    unsigned short red = this->getRed() - color.getRed() < 0 ? 0 : this->getRed() - color.getRed();
    unsigned short blue = this->getBlue() - color.getBlue() < 0 ? 0 : this->getBlue() - color.getBlue();
    unsigned short green = this->getGreen() - color.getGreen() <0 ? 0 : this->getGreen() - color.getGreen();
    return Color(red,green,blue);
}

Color Color::operator * (const double gamma) const{
    unsigned short red = gamma*this->getRed() > 255 ? 255 : gamma*this->getRed();
    unsigned short blue = gamma*this->getBlue() > 255 ? 255 : gamma*this->getBlue();
    unsigned short green = gamma*this->getGreen() > 255 ? 255 : gamma*this->getGreen();
    return Color(red,green,blue);
}

Color Color::operator / (const double gamma) const{
    unsigned short red = this->getRed()/gamma > 255 ? 255 : this->getRed()/gamma;
    unsigned short blue = this->getBlue()/gamma > 255 ? 255 : this->getBlue()/gamma;
    unsigned short green = this->getGreen()/gamma > 255 ? 255 : this->getGreen()/gamma;
    return Color(red,green,blue);
}

std::ostream& operator<< (std::ostream& out, const Color& color){
    out<<"("<<color.getRed()<<","<<color.getGreen()<<","<<color.getBlue()<<")";
    return out;
}
