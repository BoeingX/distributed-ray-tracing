#include <mpi.h>
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
//Il ne faut pas mettre mpi.h à la fin des include, sinon une erreur
// /usr/include/openmpi/ompi/mpi/cxx/mpicxx.h:188:9: erreur: expected identifier before ‘int’ class Status;
//se produit

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

//testMPI
void testMPI(int argc, char *argv[]){
    MPI_Init(&argc, &argv);
    int p;
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    Scene scene(Vector(0,0,0), width, height, distance_to_screen);

    std::vector<Light> light;
    light.push_back(Light(Vector(10,0,10)));
    //light.push_back(Light(Vector(5,0,5),Color(255,0,0),Color(255,0,0)));
    //light.push_back(Light(Vector(0,0,8)));

    int n;
    bool saveImg;

    if(rank == 0){
        std::cout<<"Do you want to save image(0/1)?"<<std::endl;
        std::cin>>saveImg;
        std::cout<<"How many balls do you want?"<<std::endl;
        std::cin>>n;
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    double* x = new double[n]; double* y = new double[n]; double* z = new double[n];
    unsigned short* r = new unsigned short[n]; unsigned short* g = new unsigned short[n]; unsigned short* b = new unsigned short[n];
    double* radius = new double[n];

    if(rank==0){
        scene.addSphereOnGround(n, eye, width, height);
        for(int i = 0; i < n; i++){
            x[i] = scene.getScene()[i].getCenter().getX();
            y[i] = scene.getScene()[i].getCenter().getY();
            z[i] = scene.getScene()[i].getCenter().getZ();
            r[i] = scene.getScene()[i].getRed();
            g[i] = scene.getScene()[i].getGreen();
            b[i] = scene.getScene()[i].getBlue();
            radius[i] = scene.getScene()[i].getRadius();
        }
    }

    MPI_Bcast(x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(y, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(z, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(r, n, MPI_UNSIGNED_SHORT, 0, MPI_COMM_WORLD);
    MPI_Bcast(g, n, MPI_UNSIGNED_SHORT, 0, MPI_COMM_WORLD);
    MPI_Bcast(b, n, MPI_UNSIGNED_SHORT, 0, MPI_COMM_WORLD);
    MPI_Bcast(radius,n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if(rank != 0) {
        for (int i = 0; i < n; i++) {
            Sphere toAdd(Vector(x[i], y[i], z[i]), radius[i], Color(r[i], g[i], b[i]));
            scene.addSphere(toAdd);
        }
    }

    ray_trace_mpi(camera, scene, light);

    if(rank == 0)
        camera.toImg(resolution_h, resolution_v, depth, saveImg, "Ray_tracing_mpi");

    delete[] r,g,b,x,y,z,radius;

    MPI_Finalize();
}

int main(int argc, char *argv[]){
    if(argc != 2)
        testMPI(argc, argv);
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
