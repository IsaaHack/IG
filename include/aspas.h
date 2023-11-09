#ifndef ASPAS_H
#define ASPAS_H

#include <modelo.h>
#include <cubo.h>
#include <nodo.h>

class Aspas : public Objeto3D{
private:
    Cubo cubo;
    Nodo a, b, c, d;
    Nodo cabeza, b_, aspas, aspa;
    Nodo raiz;
    float *giro_x, *giro_y;

    void arbolTransformaciones();
public:
    Aspas();
    Aspas(float *giro_x, float *giro_y);
    void draw();
};

#endif
