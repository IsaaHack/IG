#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <GL/glut.h>
#include <cmath>

#define ERROR 0.0000001

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
  Vector3D(Punto3D &p){
    x = p.x;
    y = p.y;
    z = p.z;
  }

  void normalizar();

  GLfloat x, y, z;
};

class Triangulo3D{
public:
  Triangulo3D(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3);

  Triangulo3D(){
    p1 = Punto3D();
    p2 = Punto3D();
    p3 = Punto3D();
    normal = Vector3D();
  }

  Vector3D getNormal() const{
    return normal;
  }

  void dibuja() const;

private:
  Punto3D p1, p2, p3;
  Vector3D normal;
};

void hacerNormal(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3);

Vector3D obtenerNormal(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3);

Vector3D obtenerNormalSinNormalizar(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3);

void dibujaTriangulo(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3);

void dibujaTriangulo(const Vector3D &normal, const Punto3D &p1, const Punto3D &p2, const Punto3D &p3);

void dibujaCuadrado(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3, const Punto3D &p4);

void dibujaCuadrado(const Vector3D &normal, const Punto3D &p1, const Punto3D &p2, const Punto3D &p3, const Punto3D &p4);


#endif