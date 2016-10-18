//
// Created by bysong on 26/04/15.
//

#ifndef PROJET_COLOR_H
#define PROJET_COLOR_H
#include <iostream>

class Color {
private:
    unsigned short r;
    unsigned short g;
    unsigned short b;
public:
    Color(unsigned short r = 0, unsigned short g = 0, unsigned short b = 0);
    void setColor(unsigned short r, unsigned short g, unsigned short b);
    void setColor(const Color& color);
    void setRed(unsigned short r);
    void setGreen(unsigned short green);
    void setBlue(unsigned short blue);
    unsigned short getRed() const;
    unsigned short getGreen() const;
    unsigned short getBlue() const;
    Color operator + (const Color& color) const;
    Color operator - (const Color& color) const;
    Color operator * (const double gamma) const;
    Color operator / (const double gamma) const;
    friend std::ostream& operator<<(std::ostream& out, const Color& color);
};


#endif //PROJET_COLOR_H
