#include "geometria3D.h"

void Vector3D::dibuja(const Punto3D &p, float factor) const
{
  glBegin(GL_LINES);
  {
      p.dibuja();
      glVertex3f((p.x + x*factor), (p.y + y*factor), (p.z + z*factor));
  }
  glEnd();
}

void Vector3D::normalizar()
{
  GLfloat modulo = mod();
  if (modulo == 0.0)
      return;
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
  Vector3D normal = obtenerNormalSinNormalizar(p1, p2, p3);
  normal.normalizar();
  return normal;
}

Vector3D obtenerNormalSinNormalizar(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3){
  Vector3D v1(p1,p2), v2(p1,p3), normal;
  normal = v1 ^ v2;
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
  normal = obtenerNormalSinNormalizar(p1, p2, p3);
}

void Triangulo3D::dibuja() const
{
    dibujaTriangulo(normal, p1, p2, p3);
}

void MatrizRotacion::set(GLfloat angulo, const Vector3D &eje){
  if(angulo == 0.0){
    matriz[0][0] = 1;
    matriz[0][1] = 0;
    matriz[0][2] = 0;
    matriz[1][0] = 0;
    matriz[1][1] = 1;
    matriz[1][2] = 0;
    matriz[2][0] = 0;
    matriz[2][1] = 0;
    matriz[2][2] = 1;
    return;
  }
  float cose = cos(angulo);
  float icos = 1 - cose;
  float sen = sin(angulo);

  matriz[0][0] = cose + eje.x * eje.x * icos;
  matriz[0][1] = eje.x * eje.y * icos - eje.z * sen;
  matriz[0][2] = eje.x * eje.z * icos + eje.y * sen;
  matriz[1][0] = eje.y * eje.x * icos + eje.z * sen;
  matriz[1][1] = cose + eje.y * eje.y * icos;
  matriz[1][2] = eje.y * eje.z * icos - eje.x * sen;
  matriz[2][0] = eje.z * eje.x * icos - eje.y * sen;
  matriz[2][1] = eje.z * eje.y * icos + eje.x * sen;
  matriz[2][2] = cose + eje.z * eje.z * icos;

}

void MatrizRotacion::set(const Vector3D &normal, const Vector3D &direccion){
  if(normal == direccion){
    set(0, Vector3D(1, 0, 0));
    return;
  }
  Vector3D axis = normal ^ direccion;
  GLfloat angulo = normal.angulo_rad(direccion);
  set(angulo, axis);
}

std::vector<Punto3D> Circulo3D::getPuntos() const
{
  std::vector<Punto3D> puntos;

  MatrizRotacion matriz_rotacion(Vector3D(0, 1, 0), normal);

  for(int i = 0; i < num_puntos; i++){
    Punto3D p(centro.x + radio * cos(2 * M_PI * i / (float)num_puntos), centro.y, centro.z + radio * sin(2 * M_PI * i / (float)num_puntos));
    p = matriz_rotacion * p;
    puntos.push_back(p);
  }
    
  puntos.push_back(puntos[0]);
  
  return puntos;
  
}

