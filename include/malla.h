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
private:
    vector<float> vertices;
    vector<int> caras;
    vector<float> normales;

    Punto3D getVertice(int i);
    void setNormal(int i, const Vector3D &normal);
    void addNormal(int i, const Vector3D &normal);
public:
    Malla() = default;
    void cargar(const char *nombre_archivo_ply);
    void draw();
};


#endif