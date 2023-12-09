#ifndef CUBO_H
#define CUBO_H

#include <GL/glut.h>
#include "geometria.h"

class Cubo : public Geometria{
protected:
  int lado;
  void calcularVertices();
  void calcularCaras();

public:
  Cubo(){
    lado = 1;
    cargar();
  }
  Cubo(float lado){
    this->lado = lado;
    cargar();
  }

  virtual void cargar(const char *nombre_archivo_ply = NULL);

  virtual void cargarTextura(const char *nombre_archivo_jpg);

  virtual void draw();
};

#endif