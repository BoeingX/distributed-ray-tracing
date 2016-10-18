//
// Created by bysong on 02/05/15.
//
#include "Vector.h"
#include "Position.h"
#ifndef PROJET_TESTRAY_H
#define PROJET_TESTRAY_H


class TestRay {
private:
    Position center;
    Vector direction;
public:
    TestRay(const Position& center, const Vector& direction);
};


#endif //PROJET_TESTRAY_H
