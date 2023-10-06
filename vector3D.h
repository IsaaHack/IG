#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <GL/glut.h>
#include <cmath>

class Vector3D{
public:
  Vector3D(GLfloat x, GLfloat y, GLfloat z){
	this->x = x;
	this->y = y;
	this->z = z;
  }
  Vector3D(){
	x = 0;
	y = 0;
	z = 0;
  }
  
  void dibuja() const;
  void normalizar();

  GLfloat x, y, z;
};

#endif