#ifndef PIRAMIDEDOBLEGENERICA_H
#define PIRAMIDEDOBLEGENERICA_H

#include "objeto3D.h"

class Piramide_doble_generica :public Objeto3D{
  private:
    float radio, alto;
    int num_lados;
    Punto3D puntos[52];
  public:
    Piramide_doble_generica(float radio, float alto, int num_lados);
    void draw();
};

#endif