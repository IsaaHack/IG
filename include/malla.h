#ifndef MALLA_H
#define MALLA_H

#include "modelo.h"
#include "file_ply_stl.h"
#include <vector>

using namespace std;
using namespace ply;

class Malla : public Objeto3D
{
private:
    vector<float> vertices;
    vector<int> caras;
    vector<float> normales;
public:
    Malla() = default;
    void cargar(const char *nombre_archivo_ply);
    void draw();
};


#endif