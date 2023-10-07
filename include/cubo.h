#ifndef CUBO_H
#define CUBO_H

#include <GL/glut.h>
#include "modelo.h"

class Cubo : public Objeto3D{
private:
  int lado;

public:
  Cubo(float lado){
    this->lado = lado;
  }

  void draw();
};

#endif