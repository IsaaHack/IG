#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <GL/glut.h>
#include <cmath>

#define ERROR 0.0000001

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
  Vector3D(const Punto3D &p){
    x = p.x;
    y = p.y;
    z = p.z;
  }

  void normalizar();

  GLfloat x, y, z;
};

class Punto3D{
public:
  Punto3D(GLfloat x, GLfloat y, GLfloat z){
    this->x = x;
    this->y = y;
    this->z = z;
  }
  Punto3D(){
    x = 0;
    y = 0;
    z = 0;
  }
  
  void dibuja() const;

  GLfloat x, y, z;
};

void hacerNormal(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3);

Vector3D obtenerNormal(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3);

void dibujaTriangulo(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3);

void dibujaTriangulo(const Vector3D &normal, Punto3D &p1, const Punto3D &p2, const Punto3D &p3);

void dibujaCuadrado(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3, const Punto3D &p4);

void dibujaCuadrado(const Vector3D &normal, const Punto3D &p1, const Punto3D &p2, const Punto3D &p3, const Punto3D &p4);


#endif