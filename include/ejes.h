#ifndef EJES_H
#define EJES_H

#include "GL/glut.h"
#include "objeto3D.h"

class Ejes : public Objeto3D{
public:
  float longitud = 30;

  void draw();
};

#endif