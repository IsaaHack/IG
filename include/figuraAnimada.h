#ifndef FIGURAANIMADA_H
#define FIGURAANIMADA_H

#include "objeto3D.h"
#include "time.h"
#include "material.h"

class FiguraAnimada : public Objeto3D {
private:
    clock_t tiempo_anterior;
    clock_t tiempo_actual;
public:
    FiguraAnimada();
    virtual void actualizar();
    virtual void draw() = 0;
    double getTiempoTranscurrido();
};


#endif