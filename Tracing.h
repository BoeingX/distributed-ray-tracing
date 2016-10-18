//
// Created by bysong on 14/05/15.
//

#ifndef PROJET_TRACING_H
#define PROJET_TRACING_H
#include "Vector.h"
#include "Sphere.h"
#include "Light.h"
#include "Camera.h"
#include "Scene.h"
#include "Ray.h"

//trivial method
Color lighting(Vector &position, Sphere &sphere, std::vector<Light>& light, Vector &eye);
void ray_trace_no_shadow(Camera &camera, Scene &scene, std::vector<Light>& light);

//determine if a point is in the shadow with respect to a certain light source
bool isInShadow(const Vector &point, int numSphere, const Scene &scene, const Light &light);

//method with shadow
Color lighting(const Vector &position,const Sphere &sphere, int numSphere, const Scene &scene, const std::vector<Light> &light, const Vector &eye);
void ray_trace(Camera &camera, Scene &scene, std::vector<Light>& light);

//method with reflection
Color lighting_rec(const Vector &position,const Sphere &sphere, int numSphere, const Scene &scene, const std::vector<Light> &light, const Vector &eye);
void ray_trace_rec(Camera &camera, Scene &scene, std::vector<Light> &light);

//method with ground
Color lighting_ground(const Vector &position,const Sphere &sphere, int numSphere, const Scene &scene, const std::vector<Light> &light, const Vector &eye, const Plane &ground);
void ray_trace_ground(Camera &camera, Scene &scene, std::vector<Light> &light);

//method MPI
void ray_trace_mpi(Camera &camera, Scene &scene, std::vector<Light> &light);
#endif //PROJET_TRACING_H
