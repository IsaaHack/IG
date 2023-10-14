#ifndef MALLA_H
#define MALLA_H

#include "modelo.h"
#include "file_ply_stl.h"
#include "GL/glut.h"
#include <vector>

using namespace std;
using namespace ply;

class Malla : public Objeto3D
{
protected:
    vector<float> vertices;
    vector<int> caras;
    vector<float> normales;
    int modo_sombreado;

    Punto3D getVertice(int i);
    void setNormal(int i, const Vector3D &normal);
    void addNormal(int i, const Vector3D &normal);
    void normalizarNormales();
public:
    virtual void cargar(const char *nombre_archivo_ply) = 0;
    virtual void setModoSombreado(int modo);
    virtual void draw() = 0;
};


#endif