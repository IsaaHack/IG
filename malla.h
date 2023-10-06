#ifndef MALLA_H
#define MALLA_H

#include "modelo.h"
#include "file_ply_stl.h"
#include <vector>

using namespace std;

class Malla : public Objeto3D
{
private:
    vector<float> vertices;
    vector<int> caras;
    vector<float> normales;

    void cargar(const char *nombre_archivo_ply);
public:
    Malla(const char *nombre_archivo_ply);
    void draw();
};


#endif