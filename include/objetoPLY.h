#ifndef OBJETO_PLY_H
#define OBJETO_PLY_H

#include "malla.h"

class ObjetoPLY : public Malla{
public:
    ObjetoPLY(){
        modo_sombreado = GL_SMOOTH;
    };
    void cargar(const char *nombre_archivo_ply);
    void draw();
};

#endif