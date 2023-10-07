#ifndef PIRAMIDE_H
#define PIRAMIDE_H

#include "modelo.h"

class Piramide : public Objeto3D{
  private:
    float lado, alto;
    Punto3D puntos[5];
  public:
    Piramide(float lado, float alto);
    void draw();
};

#endif