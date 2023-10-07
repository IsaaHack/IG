#include "geometria3D.h"

void Vector3D::normalizar(){
  GLfloat modulo = sqrt(x * x + y * y + z * z);
  if(modulo < ERROR || modulo > -ERROR) return;
  x /= modulo;
  y /= modulo;
  z /= modulo;
}

void Punto3D::dibuja() const{
    glVertex3f(x, y, z);
}

void hacerNormal(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3){
  Vector3D normal = obtenerNormal(p1, p2, p3);
  glNormal3f(normal.x, normal.y, normal.z);
}

Vector3D obtenerNormal(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3){
  Vector3D v1, v2, normal;
  v1.x = p2.x - p1.x;
  v1.y = p2.y - p1.y;
  v1.z = p2.z - p1.z;
  v2.x = p3.x - p1.x;
  v2.y = p3.y - p1.y;
  v2.z = p3.z - p1.z;
  normal.x = v1.y * v2.z - v1.z * v2.y;
  normal.y = v1.z * v2.x - v1.x * v2.z;
  normal.z = v1.x * v2.y - v1.y * v2.x;
  normal.normalizar();
  return normal;
}

Vector3D obtenerNormalSinNormalizar(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3){
  Vector3D v1, v2, normal;
  v1.x = p2.x - p1.x;
  v1.y = p2.y - p1.y;
  v1.z = p2.z - p1.z;
  v2.x = p3.x - p1.x;
  v2.y = p3.y - p1.y;
  v2.z = p3.z - p1.z;
  normal.x = v1.y * v2.z - v1.z * v2.y;
  normal.y = v1.z * v2.x - v1.x * v2.z;
  normal.z = v1.x * v2.y - v1.y * v2.x;
  return normal;
}

void dibujaTriangulo(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3){
  glBegin(GL_TRIANGLES);
  {
    hacerNormal(p1, p2, p3);
    p1.dibuja();
    p2.dibuja();
    p3.dibuja();
  }
  glEnd();
}

void dibujaTriangulo(const Vector3D &normal, const Punto3D &p1, const Punto3D &p2, const Punto3D &p3){
  glBegin(GL_TRIANGLES);
  {
    glNormal3f(normal.x, normal.y, normal.z);
    p1.dibuja();
    p2.dibuja();
    p3.dibuja();
  }
  glEnd();
}

void dibujaCuadrado(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3, const Punto3D &p4){
  dibujaTriangulo(p1, p2, p3);
  dibujaTriangulo(p1, p3, p4);
}

void dibujaCuadrado(const Vector3D &normal, const Punto3D &p1, const Punto3D &p2, const Punto3D &p3, const Punto3D &p4){
  glNormal3f(normal.x, normal.y, normal.z);
  glBegin(GL_QUADS);
  {
    p1.dibuja();
    p2.dibuja();
    p3.dibuja();
    p4.dibuja();
  }
  glEnd();
}

Triangulo3D::Triangulo3D(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3){
  this->p1 = p1;
  this->p2 = p2;
  this->p3 = p3;
  normal = obtenerNormal(p1, p2, p3);
}

void Triangulo3D::dibuja() const
{
    dibujaTriangulo(normal, p1, p2, p3);
}
