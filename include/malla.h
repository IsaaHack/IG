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
    Triangulo3D getCara(int i);
    Vector3D getNormal(int i);
    void setNormal(int i, const Vector3D &normal);
    void addNormal(int i, const Vector3D &normal);
    void calcularNormalesVertices();
    void normalizarNormales();
    void drawNormalesVertices();
    void drawNormalesCaras();
public:
    virtual void cargar(const char *nombre_archivo_ply) = 0;
    virtual void setModoSombreado(int modo);
    virtual void draw();
    virtual void draw(bool draw_normales);
    virtual void drawSmooth(bool draw_normales = false);
    virtual void drawFlat(bool draw_normales = false);
};


#endif