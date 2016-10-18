//
// Created by bysong on 14/05/15.
//
#include <mpi.h>
#include <stdexcept>
#include <limits>
#include "Tracing.h"


const double ks = 0.5;
const double kd = 0.5;
const double ka = 0.5;
const double alpha = 30;
const double infinity = std::numeric_limits<double>::infinity();
const Color sky = Color(255,255,255);

Color lighting(Vector &position, Sphere &sphere, std::vector<Light> &light, Vector &eye){
    Color Ip = light[0].getIa() * ka;
    for(int i = 0; i < light.size(); i++){
        Vector Lm(light[i].getPosition().getX()-position.getX(), light[i].getPosition().getY()-position.getY(),light[i].getPosition().getZ()-position.getZ() );
        Lm = Lm/(Lm.norme());
        Vector N(position.getX() - sphere.getCenter().getX(), position.getY() - sphere.getCenter().getY(), position.getZ() - sphere.getCenter().getZ());
        N = N/(N.norme());
        if(Lm.dotProduct(N) >= 0) {
            Vector Rm = N*(2*(Lm.dotProduct(N)))-Lm;
            Rm = Rm/(Rm.norme());
            Vector V( eye.getX()- position.getX(), eye.getY()-position.getY() , eye.getZ()-position.getZ());
            V = V/(V.norme());
            Ip = Ip + light[i].getId()*(kd*(Lm.dotProduct(N)));
            if(Rm.dotProduct(V) >= 0)
                Ip = Ip+(light[i].getIs()*(ks * pow(Rm.dotProduct(V), alpha)));
        }
    }
    return Ip+position.getColor();
}

void ray_trace_no_shadow(Camera &camera, Scene &scene, std::vector<Light>& light){
    for(int i = 0; i < camera.getNbr_v(); i++){
        for(int j = 0; j < camera.getNbr_h(); j++){
            camera.setTarget(camera.getScreen()[i][j]);
            Ray direction = fromTo(camera.getEye(), camera.getTarget());
            Vector intersection;
            Sphere nearest_sphere;
            int numSphere;
            if(nearestIntersection(direction, scene, camera.getEye(), -1,intersection, nearest_sphere, numSphere)){
                Color color = lighting(intersection, nearest_sphere, light, camera.getEye());
                camera.getScreen()[i][j].setColor(color);
            }
        }
    }
}



Color lighting(const Vector &position, const Sphere &sphere, int numSphere, const Scene &scene, const std::vector<Light> &light, const Vector &eye){
    Color Ip = light[0].getIa()*ka + position.getColor();
    for(int i = 0; i < light.size(); i++){
        if(isInShadow(position, numSphere, scene, light[i])) {
            Ip = Ip*0.75;
        }
        else {
            Vector Lm(light[i].getPosition().getX() - position.getX(), light[i].getPosition().getY() - position.getY(),
                      light[i].getPosition().getZ() - position.getZ());
            Lm = Lm / (Lm.norme());
            Vector N(position.getX() - sphere.getCenter().getX(), position.getY() - sphere.getCenter().getY(),
                     position.getZ() - sphere.getCenter().getZ());
            N = N / (N.norme());

            if (Lm.dotProduct(N) >= 0) {
                Vector Rm = N * (2 * (Lm.dotProduct(N))) - Lm;
                Rm = Rm / (Rm.norme());
                Vector V(eye.getX() - position.getX(), eye.getY() - position.getY(),
                         eye.getZ() - position.getZ());
                V = V / (V.norme());
                Ip = Ip + light[i].getId() * (kd * (Lm.dotProduct(N)));
                if (Rm.dotProduct(V) >= 0)
                    Ip = Ip + (light[i].getIs() * (ks * pow(Rm.dotProduct(V), alpha)));
            }
        }
    }
    return Ip;
}


bool isInShadow(const Vector &point, int numSphere, const Scene &scene, const Light &light){
    Vector intersection3, intersection4;
    double shadow_distance=point.distanceTo(light.getPosition());
    double dist=infinity;
    bool isInShadow = false;//if there should be shadows, m=1;
    Ray directionLight = fromTo(light.getPosition(),point);
    for (int m=0; m< scene.numberSpheres(); m++) {
        if (isIntersect(directionLight, scene.getScene()[m], intersection3, intersection4)) {
            dist = intersection3.distanceTo(light.getPosition());
            if ((numSphere != m) && (dist < shadow_distance)) {
                isInShadow = true;
                break;
            }
        }
    }
    return isInShadow;
}



void ray_trace(Camera &camera, Scene &scene, std::vector<Light> &light) {
    for (int i = 0; i < camera.getNbr_v(); i++) {
        for (int j = 0; j < camera.getNbr_h(); j++) {
            camera.setTarget(camera.getScreen()[i][j]);
            Ray direction = fromTo(camera.getEye(), camera.getTarget());
            Vector intersection;
            Sphere nearest_sphere;
            int numSphere;
            if(nearestIntersection(direction, scene, camera.getEye(),-1, intersection, nearest_sphere, numSphere)){
                Color color = lighting(intersection, nearest_sphere, numSphere, scene, light, camera.getEye());
                camera.getScreen()[i][j].setColor(color);
            }
        }
    }
}

void ray_trace_rec(Camera &camera, Scene &scene, std::vector<Light> &light){
    for (int i = 0; i < camera.getNbr_v(); i++) {
        for (int j = 0; j < camera.getNbr_h(); j++) {
            camera.setTarget(camera.getScreen()[i][j]);
            Ray direction = fromTo(camera.getEye(), camera.getTarget());
            Vector intersection;
            Sphere nearest_sphere;
            int numSphere;
            if(nearestIntersection(direction, scene, camera.getEye(), -1, intersection, nearest_sphere, numSphere)){
                Color color = lighting_rec(intersection, nearest_sphere, numSphere, scene, light, camera.getEye());
                camera.getScreen()[i][j].setColor(color);
            }
        }
    }
}



Color lighting_rec(const Vector &position,const Sphere &sphere, int numSphere, const Scene &scene, const std::vector<Light> &light, const Vector &eye) {
    Color cs = lighting(position, sphere, numSphere, scene, light, eye);
    Vector toEye = eye - position;
    Vector N = position - sphere.getCenter();
    toEye = toEye / (toEye.norme());
    N = N / (N.norme());
    Vector reflection_eye = N * (2 * (toEye.dotProduct(N))) - toEye;
    Ray out(position, reflection_eye);
    Vector intersection;
    Sphere nearest_sphere;
    int num;
    if (!nearestIntersection(out, scene, position, sphere, numSphere, intersection, nearest_sphere, num)){
        return cs*(1 - sphere.getR())+ sky*sphere.getR();
    }
    else {
        return cs * (1 - sphere.getR()) + lighting_rec(intersection, nearest_sphere, num, scene, light, position) * (sphere.getR());

    }
}




Color lighting_ground(const Vector &position,const Sphere &sphere, int numSphere, const Scene &scene, const std::vector<Light> &light, const Vector &eye, const Plane &ground){
    Color cs = lighting(position, sphere, numSphere, scene, light, eye);
    Vector toEye = eye - position;
    Vector N = position - sphere.getCenter();
    toEye = toEye / (toEye.norme());
    N = N / (N.norme());
    Vector reflection_eye = N * (2 * (toEye.dotProduct(N))) - toEye;
    Ray out(position, reflection_eye);
    Vector intersection;
    Sphere nearest_sphere;
    int num;
    if (!nearestIntersection(out, scene, position, sphere, numSphere, intersection, nearest_sphere, num)){
        if(isIntersect(out, ground, intersection))
            return cs*(1-sphere.getR()) + intersection.getColor()*sphere.getR();
        return cs*(1 - sphere.getR())+ sky*sphere.getR();
    }
    else {
        return cs * (1 - sphere.getR()) + lighting_ground(intersection, nearest_sphere, num, scene, light, position, scene.getGround()) * (sphere.getR());
    }
}

void ray_trace_ground(Camera &camera, Scene &scene, std::vector<Light> &light){
    for (int i = 0; i < camera.getNbr_v(); i++) {
        for (int j = 0; j < camera.getNbr_h(); j++) {
            camera.setTarget(camera.getScreen()[i][j]);
            Ray direction = fromTo(camera.getEye(), camera.getTarget());
            Vector intersection;
            Sphere nearest_sphere;
            int numSphere;
            if(nearestIntersection(direction, scene, camera.getEye(), -1, intersection, nearest_sphere, numSphere)){
                Color color = lighting_ground(intersection, nearest_sphere, numSphere, scene, light, camera.getEye(), scene.getGround());
                camera.getScreen()[i][j].setColor(color);
            }
            else{
                if(isIntersect(direction, scene.getGround(),intersection)){
                    Color color = intersection.getColor();
                    for(int l = 0; l < light.size(); l++) {
                        if (isInShadow(intersection, -1, scene, light[l]))
                            color = color * 0.5;
                    }
                    camera.getScreen()[i][j].setColor(color);
                }
            }
        }
    }
}


void ray_trace_mpi(Camera &camera, Scene &scene, std::vector<Light> &light){
    int p;
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Barrier(MPI_COMM_WORLD);
    clock_t t = clock();
    int N = camera.getNbr_v();
    int M = camera.getNbr_h();
    int pas = ceil(N/(double) p);
    int index_min = rank*pas;
    int index_max = (rank+1)*pas <= N ? (rank+1)*pas:N;

    unsigned short** r_local = new unsigned short* [N];
    unsigned short* r_global = new unsigned short [M];
    unsigned short** g_local = new unsigned short* [N];
    unsigned short* g_global = new unsigned short [M];
    unsigned short** b_local = new unsigned short*[N];
    unsigned short* b_global = new unsigned short[M];
    for(int i = 0; i < N; i++){
        r_local[i] = new unsigned short[M];
        g_local[i] = new unsigned short[M];
        b_local[i] = new unsigned short[M];
        std::fill_n(r_local[i], M, 255);
        std::fill_n(g_local[i], M, 255);
        std::fill_n(b_local[i], M, 255);
    }


    for(int i = index_min; i < index_max; i++){
        for (int j = 0; j < camera.getNbr_h(); j++) {
            camera.setTarget(camera.getScreen()[i][j]);
            Ray direction = fromTo(camera.getEye(), camera.getTarget());
            Vector intersection;
            Sphere nearest_sphere;
            int numSphere;
            if(nearestIntersection(direction, scene, camera.getEye(), -1, intersection, nearest_sphere, numSphere)){
                Color color = lighting_ground(intersection, nearest_sphere, numSphere, scene, light, camera.getEye(), scene.getGround());
                r_local[i][j] = color.getRed();
                g_local[i][j] = color.getGreen();
                b_local[i][j] = color.getBlue();
            }
            else if(isIntersect(direction, scene.getGround(),intersection)){
                    Color color = intersection.getColor();
                    for(int l = 0; l < light.size(); l++) {
                        if (isInShadow(intersection, -1, scene, light[l]))
                            color = color * 0.5;
                    }
                    r_local[i][j] = color.getRed();
                    g_local[i][j] = color.getGreen();
                    b_local[i][j] = color.getBlue();
            }
            /*else{//comme r_local, g_local et b_local sont initialises 0, si il n'y a pas ces trois lignes, le ciel est noir.
                r_local[i][j] = 255;
                g_local[i][j] = 255;
                b_local[i][j] = 255;
            }*/

        }
    }

    for(int i = 0; i < N; i++) {
        MPI_Reduce(r_local[i], r_global, M, MPI_UNSIGNED_SHORT, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce(g_local[i], g_global, M, MPI_UNSIGNED_SHORT, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce(b_local[i], b_global, M, MPI_UNSIGNED_SHORT, MPI_SUM, 0, MPI_COMM_WORLD);
        if(rank == 0){
            for(int j = 0; j < M; j++){
                camera.getScreen()[i][j].setR(r_global[j]);
                camera.getScreen()[i][j].setG(g_global[j]);
                camera.getScreen()[i][j].setB(b_global[j]);
            }
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    t = clock() - t;
    if(rank == 0){
    	std::cout <<std::endl
    		      <<"execution time: "
    		      <<(t)/CLOCKS_PER_SEC
    		      <<"s\n\n";
    }
}

