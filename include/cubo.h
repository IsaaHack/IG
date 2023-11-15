#ifndef CUBO_H
#define CUBO_H

#include <GL/glut.h>
#include "objeto3D.h"

class Cubo : public Objeto3D{
private:
  int lado;

public:
  Cubo(){
    lado = 1;
  }
  Cubo(float lado){
    this->lado = lado;
  }

  void draw();
};

#endif