//
// Created by bysong on 26/04/15.
//
#include <stdexcept>
#include "Ray.h"
#include "Camera.h"
#include <cmath>
#include <limits>
#include "Plane.h"
const double epsilon = std::numeric_limits<double>::epsilon();
const double infinity = std::numeric_limits<double>::infinity();

Ray::Ray(const Vector &point, const Vector &direction):point(point),direction(direction) {
    if(direction.isNull())
        throw std::invalid_argument( "Null direction, ray non well-defined !" );
}

const Vector& Ray::getPoint() const{
    return point;
}

const Vector& Ray::getDirection() const{
    return direction;
}
bool isIntersect(const Ray &ray, const Sphere &sphere, Vector &intersect1, Vector &intersect2){
    double A = (ray.getDirection().getX())*(ray.getDirection().getX())+
               (ray.getDirection().getY())*(ray.getDirection().getY())+
               (ray.getDirection().getZ())*(ray.getDirection().getZ());
    double B = 2*((ray.getPoint().getX()-sphere.getCenter().getX())*(ray.getDirection().getX())+
                  (ray.getPoint().getY()-sphere.getCenter().getY())*(ray.getDirection().getY())+
                  (ray.getPoint().getZ()-sphere.getCenter().getZ())*(ray.getDirection().getZ()));
    double C = (ray.getPoint().getX()-sphere.getCenter().getX())*(ray.getPoint().getX()-sphere.getCenter().getX())+
               (ray.getPoint().getY()-sphere.getCenter().getY())*(ray.getPoint().getY()-sphere.getCenter().getY())+
               (ray.getPoint().getZ()-sphere.getCenter().getZ())*(ray.getPoint().getZ()-sphere.getCenter().getZ())-
               (sphere.getRadius())*(sphere.getRadius());
    double delta = B*B-4*A*C;
    if(delta < 0){
        return false;
    }
    double t1 = (-B-sqrt(delta))/(2*A);
    double t2 = -B/A - t1;

    Vector tmp1(ray.getPoint().getX()+t1*(ray.getDirection().getX()),
                          ray.getPoint().getY()+t1*(ray.getDirection().getY()),
                          ray.getPoint().getZ()+t1*(ray.getDirection().getZ()), sphere.getColor());
    Vector tmp2(ray.getPoint().getX()+t2*(ray.getDirection().getX()),
                          ray.getPoint().getY()+t2*(ray.getDirection().getY()),
                          ray.getPoint().getZ()+t2*(ray.getDirection().getZ()),sphere.getColor());
    double dist1 = tmp1.distanceTo(ray.getPoint());
    double dist2 = tmp2.distanceTo(ray.getPoint());
    if(dist1 <= dist2){
        intersect1 = tmp1;
        intersect2 = tmp2;
    }
    else{
        intersect1 = tmp2;
        intersect2 = tmp1;
    }
    return true;
}

Ray fromTo(const Vector &start, const Vector &end){
    return Ray(start, end-start);
}
bool nearestIntersection(const Ray &direction, const Scene &scene, const Vector &start, int mynum, Vector &intersection, Sphere& nearest_sphere, int &numSphere){
    double min_distance = infinity;
    numSphere = 0;
    Vector intersection1, intersection2;
    for (int k = 0; k < scene.numberSpheres(); k++) {
        if(k == mynum)
            continue;
        if (isIntersect(direction, scene.getScene()[k], intersection1, intersection2)) {
            double dist = intersection1.distanceTo(start);
            if (dist < min_distance) {
                min_distance = dist;
                intersection = intersection1;
                nearest_sphere = scene.getScene()[k];
                numSphere = k;
            }
        }
    }

    return min_distance < infinity;
}

bool nearestIntersection(const Ray &ray, const Scene &scene, const Vector &start, const Sphere &sphere, int mynum, Vector &intersection, Sphere& nearest_sphere, int &numSphere){
    double min_distance = infinity;
    numSphere = 0;
    Vector intersection1, intersection2;
    Vector N = start - sphere.getCenter();
    for (int k = 0; k < scene.numberSpheres(); k++) {
        if(k == mynum)
            continue;
        if (isIntersect(ray, scene.getScene()[k], intersection1, intersection2)) {
            double dist = intersection1.distanceTo(start);
            if (dist < min_distance) {
                min_distance = dist;
                intersection = intersection1;
                nearest_sphere = scene.getScene()[k];
                numSphere = k;
            }
        }
    }
    if(min_distance < infinity){
        if((intersection - start).dotProduct(N) < epsilon)
            return false;
        else
            return true;
    }
    return false;
}

bool isIntersect(const Ray &ray, const Plane& plane, Vector &intersect){
    double A = plane.getA();
    double B = plane.getB();
    double C = plane.getC();
    double D = plane.getD();
    double a = ray.getDirection().getX();
    double b = ray.getDirection().getY();
    double c = ray.getDirection().getZ();
    if(ray.getDirection().dotProduct(plane.getNormal())>=0)
        return false;
    double divisor = A*a + B*b + C*c;

    double t = -(A*ray.getPoint().getX() + B*ray.getPoint().getY() + C*ray.getPoint().getZ()+D)/divisor;
    intersect = Vector(t*a+ray.getPoint().getX(), t*b+ray.getPoint().getY(), t*c+ray.getPoint().getZ());
    int x = floor(intersect.getX());
    int y = floor(intersect.getY());
    bool flag1 = x%2;
    bool flag2 = y%2;
    if((flag1&&flag2)||(!flag1&&!flag2))
        intersect.setColor(Color(10,10,10));
    else
        intersect.setColor(Color(250,250,250));
    return true;
}

