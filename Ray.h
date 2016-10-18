//
// Created by bysong on 26/04/15.
//
#include <utility>
#include "Vector.h"
#include "Sphere.h"
#include "Scene.h"
#include "Camera.h"
#include "Plane.h"

#ifndef PROJET_RAY_H
#define PROJET_RAY_H


class Ray {
private:
    Vector point;
    Vector direction;
public:
    Ray(const Vector &point, const Vector &direction);
    const Vector& getPoint() const;
    const Vector& getDirection() const;
};

//determine if the ray intersects with the sphere
bool isIntersect(const Ray &ray, const Sphere &sphere, Vector &intersect1, Vector &intersect2);

//determine if the ray hits a plane
bool isIntersect(const Ray &ray, const Plane& plane, Vector &intersect);


//determine if the ray intersects with the sphere, and get the first sphere it hits if it does
//the first method is for the ray directly from the light source, because we do not treat light source as a sphere of 0 radius
bool nearestIntersection(const Ray &ray, const Scene &scene, const Vector &start, int mynum, Vector &intersection, Sphere& nearest_sphere, int &numSphere);
//general method
bool nearestIntersection(const Ray &ray, const Scene &scene, const Vector &start, const Sphere &sphere, int mynum, Vector &intersection, Sphere& nearest_sphere, int &numSphere);

Ray fromTo(const Vector& start, const Vector& end);


#endif //PROJET_RAY_H
