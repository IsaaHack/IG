#ifndef ESCALERA_H
#define ESCALERA_H

#include "modelo.h"

class Escalera : public Objeto3D{
  private:
    float lado, alto;
    Punto3D puntos[12];
  public:
    Escalera(float lado, float alto);
    void draw();
};

#endif