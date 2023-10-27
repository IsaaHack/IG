#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <cstdio>

#define ERROR 0.00001

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

  bool operator==(const Punto3D &p) const{
    return fabs(x - p.x) < ERROR && fabs(y - p.y) < ERROR && fabs(z - p.z) < ERROR;
  }

  bool operator!=(const Punto3D &p) const{
    return !(*this == p);
  }

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
  Vector3D(const Punto3D &p){
    x = p.x;
    y = p.y;
    z = p.z;
  }

  Vector3D(const Punto3D &inicio, const Punto3D &final){
    x = final.x - inicio.x;
    y = final.y - inicio.y;
    z = final.z - inicio.z;
  }

  void dibuja(const Punto3D &p, float factor=1.0) const;

  void normalizar();

  Vector3D obtenerNormalizado() const{
    Vector3D normalizado(*this);
    normalizado.normalizar();
    return normalizado;
  }

  GLfloat angulo_rad(const Vector3D &v) const{
    if(*this == v)
      return 0;
    return acos((*this * v) / (mod() * v.mod()));
  }

  GLfloat angulo_grados(const Vector3D &v) const{
    return angulo_rad(v) * 180 / M_PI;
  }

  GLfloat mod() const{
    return sqrt(x * x + y * y + z * z);
  }

  bool operator==(const Vector3D &v) const{
    return fabs(x - v.x) < ERROR && fabs(y - v.y) < ERROR && fabs(z - v.z) < ERROR;
  }

  bool operator!=(const Vector3D &v) const{
    return !(*this == v);
  }

  Vector3D operator+(const Vector3D &v) const{
    return Vector3D(x + v.x, y + v.y, z + v.z);
  }

  Vector3D operator-(const Vector3D &v) const{
    return Vector3D(x - v.x, y - v.y, z - v.z);
  }

  Vector3D operator*(GLfloat k) const{
    return Vector3D(x * k, y * k, z * k);
  }

  Vector3D operator/(GLfloat k) const{
    return Vector3D(x / k, y / k, z / k);
  }

  Vector3D operator-() const{
    return Vector3D(-x, -y, -z);
  }

  Vector3D operator+=(const Vector3D &v){
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  Vector3D operator-=(const Vector3D &v){
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  Vector3D operator*=(GLfloat k){
    x *= k;
    y *= k;
    z *= k;
    return *this;
  }

  Vector3D operator/=(GLfloat k){
    x /= k;
    y /= k;
    z /= k;
    return *this;
  }

  Vector3D operator^(const Vector3D &v) const{
    return Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
  }

  Vector3D operator^=(const Vector3D &v){
    GLfloat x = y * v.z - z * v.y;
    GLfloat y = z * v.x - x * v.z;
    GLfloat z = x * v.y - y * v.x;
    this->x = x;
    this->y = y;
    this->z = z;
    return *this;
  }

  GLfloat operator*(const Vector3D &v) const{
    return x * v.x + y * v.y + z * v.z;
  }

  GLfloat x, y, z;
};

class MatrizRotacion{
  private:
    GLfloat matriz[3][3];
  public:
    MatrizRotacion(){
      matriz[0][0] = 1;
      matriz[0][1] = 0;
      matriz[0][2] = 0;
      matriz[1][0] = 0;
      matriz[1][1] = 1;
      matriz[1][2] = 0;
      matriz[2][0] = 0;
      matriz[2][1] = 0;
      matriz[2][2] = 1;
    }

    MatrizRotacion(GLfloat angulo, const Vector3D &v){
      set(angulo, v);
    }

    MatrizRotacion(const Vector3D &v1, const Vector3D &v2){
      set(v1, v2);
    }

    void set(GLfloat angulo, const Vector3D &v);

    void set(const Vector3D &v1, const Vector3D &v2);
    
    GLfloat operator[](int i) const{
      if(i < 0 || i > 8)
        return matriz[0][0];
      return matriz[i / 3][i % 3];
    }
    GLfloat &operator[](int i){
      if(i < 0 || i > 8)
        return matriz[0][0];
      return matriz[i / 3][i % 3];
    }

    Punto3D operator*(const Punto3D &p) const{
      return Punto3D(matriz[0][0] * p.x + matriz[0][1] * p.y + matriz[0][2] * p.z,
                     matriz[1][0] * p.x + matriz[1][1] * p.y + matriz[1][2] * p.z,
                     matriz[2][0] * p.x + matriz[2][1] * p.y + matriz[2][2] * p.z);
    }
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

  Punto3D getP1() const{
    return p1;
  }

  Punto3D getP2() const{
    return p2;
  }

  Punto3D getP3() const{
    return p3;
  }

  Vector3D getNormal() const{
    return normal;
  }

  Punto3D getCentro() const{
    return Punto3D((p1.x + p2.x + p3.x) / 3, (p1.y + p2.y + p3.y) / 3, (p1.z + p2.z + p3.z) / 3);
  }

  void normalizarNormal(){
    normal.normalizar();
  }

  void dibuja() const;

private:
  Punto3D p1, p2, p3;
  Vector3D normal;
};

class Circulo3D{
public:
  Circulo3D(const Punto3D &centro, const Vector3D &normal, GLfloat radio, int num_puntos){
    this->centro = centro;
    this->normal = normal;
    this->radio = radio;
    this->num_puntos = num_puntos;
  }

  Circulo3D(){
    centro = Punto3D();
    normal = Vector3D();
    radio = 0;
    num_puntos = 0;
  }

  Punto3D getCentro() const{
    return centro;
  }

  Vector3D getNormal() const{
    return normal;
  }

  GLfloat getRadio() const{
    return radio;
  }

  int getNumPuntos() const{
    return num_puntos;
  }

  std::vector<Punto3D> getPuntos() const;

  private:
    Punto3D centro;
    Vector3D normal;
    GLfloat radio;
    int num_puntos;
};

void hacerNormal(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3);

Vector3D obtenerNormal(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3);

Vector3D obtenerNormalSinNormalizar(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3);

void dibujaTriangulo(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3);

void dibujaTriangulo(const Vector3D &normal, const Punto3D &p1, const Punto3D &p2, const Punto3D &p3);

void dibujaCuadrado(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3, const Punto3D &p4);

void dibujaCuadrado(const Vector3D &normal, const Punto3D &p1, const Punto3D &p2, const Punto3D &p3, const Punto3D &p4);


#endif