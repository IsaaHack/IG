#include "vector3D.h"

void Vector3D::dibuja() const{
    glVertex3f(x, y, z);
}

void Vector3D::normalizar(){
  GLfloat modulo = sqrt(x * x + y * y + z * z);
  x /= modulo;
  y /= modulo;
  z /= modulo;
}