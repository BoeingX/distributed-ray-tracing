#include <iostream>
#include "Vector.h"
#include "Vector.h"
#include "Ray.h"
#include "Scene.h"
#include "Camera.h"
#include "Light.h"
#include "Tracing.h"
#include "CImg.h"
#include <iostream>

using namespace cimg_library;

//some constants
//focus_length is the distance between the screen and the camera
const double focus_length = 5;

//dimension of the screen
const double width = 16;
const double height = 9;

//BMP depth
const int depth = 1;

//distance between the scene and the screen
const double distance_to_screen = 3;

//resolution of screen, on pixel
const int resolution_h = (int)(100*width);
const int resolution_v = (int)(100*height);

//position of camera
const Vector eye(0,-focus_length,0);

//definition of camera
Camera camera(eye, Vector(0,0,1),width,height,resolution_h, resolution_v);

//test1, two spheres without shadow and reflection
void test1(){
    bool saveImg;
    std::cout<<"Do you want to save image(0/1)?"<<std::endl;
    std::cin>>saveImg;
    Sphere sphere(Vector(-2,12,-0.5),4,Color(255,0,0));
    Sphere sphere2(Vector(3.5,7,-1.5), 3, Color(0,0,255));
    Scene scene(Vector(0,0,0),width, height, distance_to_screen);
    scene.addSphere(sphere);
    scene.addSphere(sphere2);
    std::vector<Light> light;
    light.push_back(Light(Vector(5,0,5)));
    ray_trace_no_shadow(camera,scene,light);
    camera.toImg(resolution_h, resolution_v, depth, saveImg, "Ray_tracing_naive");
}

//test2, two spheres with shadow but without reflection
void test2(){
    bool saveImg;
    std::cout<<"Do you want to save image(0/1)?"<<std::endl;
    std::cin>>saveImg;
    Sphere sphere(Vector(-2,12,-0.5),4,Color(255,0,0));
    Sphere sphere2(Vector(3.5,7,-1.5), 3, Color(0,0,255));
    Scene scene(Vector(0,0,0),width, height, distance_to_screen);
    scene.addSphere(sphere);
    scene.addSphere(sphere2);
    std::vector<Light> light;
    light.push_back(Light(Vector(5,0,5)));
    ray_trace(camera,scene,light);
    camera.toImg(resolution_h, resolution_v, depth, saveImg, "Ray_tracing_shadow");
}

//test3, two spheres with shadow and reflection
void test3(){
    bool saveImg;
    std::cout<<"Do you want to save image(0/1)?"<<std::endl;
    std::cin>>saveImg;
    Sphere sphere(Vector(-2,12,-0.5),4,Color(255,0,0));
    Sphere sphere2(Vector(3.5,7,-1.5), 3, Color(0,0,255));
    Scene scene(Vector(0,0,0),width, height, distance_to_screen);
    scene.addSphere(sphere);
    scene.addSphere(sphere2);
    std::vector<Light> light;
    light.push_back(Light(Vector(5,0,5)));
    ray_trace_rec(camera,scene,light);
    camera.toImg(resolution_h, resolution_v, depth, saveImg, "Ray_tracing_reflection");
}

//test4, two spheres with ground to show the depth of image
void test4(){
    bool saveImg;
    std::cout<<"Do you want to save image(0/1)?"<<std::endl;
    std::cin>>saveImg;
    Sphere sphere(Vector(-2,12,-0.5),4,Color(255,0,0));
    Sphere sphere2(Vector(3.5,7,-1.5), 3, Color(0,0,255));
    Scene scene(Vector(0,0,0),width, height, distance_to_screen);
    scene.addSphere(sphere);
    scene.addSphere(sphere2);
    std::vector<Light> light;
    light.push_back(Light(Vector(5,0,5)));
    ray_trace_ground(camera,scene,light);
    camera.toImg(resolution_h, resolution_v, depth, saveImg, "Ray_tracing_ground");
}

//testExtreme, two spheres with zero and total reflection, the sky is white. To change color, please change
//the values in the constructor of Vector and also in the begin of Tracing.cpp
void testExtreme(){
    bool saveImg;
    std::cout<<"Do you want to save image(0/1)?"<<std::endl;
    std::cin>>saveImg;
    Sphere sphere(Vector(-2,12,-0.5),4,Color(255,0,0),1);
    Sphere sphere2(Vector(3.5,7,-1.5), 3, Color(0,0,255), 0);
    Scene scene(Vector(0,0,0),width, height, distance_to_screen);
    scene.addSphere(sphere);
    scene.addSphere(sphere2);
    std::vector<Light> light;
    light.push_back(Light(Vector(5,0,5)));
    ray_trace_ground(camera,scene,light);
    camera.toImg(resolution_h, resolution_v, depth, saveImg, "Ray_tracing_extreme");
}

int main(int argc, char *argv[]){
    if(argc != 2)
        test1();
    else if(strcmp(argv[1],"test1")==0)
        test1();
    else if(strcmp(argv[1],"test2")==0)
        test2();
    else if(strcmp(argv[1],"test3")==0)
        test3();
    else if(strcmp(argv[1],"test4")==0)
        test4();
    else if(strcmp(argv[1],"testExtreme")==0)
        testExtreme();
    return 0;
}
