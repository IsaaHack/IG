#ifndef EJES_H
#define EJES_H

#include "GL/glut.h"
#include "modelo.h"

class Ejes : public Objeto3D{
public:
  float longitud = 30;

  void draw();
};

#endif