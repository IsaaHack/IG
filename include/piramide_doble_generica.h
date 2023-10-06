#ifndef PIRAMIDEDOBLEGENERICA_H
#define PIRAMIDEDOBLEGENERICA_H

#include "modelo.h"

class Piramide_doble_generica :public Objeto3D{
  private:
    float radio, alto;
    int num_lados;
    Vector3D puntos[52];
  public:
    Piramide_doble_generica(float radio, float alto, int num_lados);
    void draw();
};

#endif