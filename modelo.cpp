/*	Prácticas de Informática Gráfica

  Grupo C					Curso 2022-23

  Codigo base para la realización de las practicas de IG

  Estudiante: Isaac Brao Aissaoni

=======================================================
  G. Arroyo, J.C. Torres
  Dpto. Lenguajes y Sistemas Informticos
  (Univ. de Granada)

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details
 http://www.gnu.org/copyleft/gpl.html

=======================================================/
modulo modelo.c
    Representación del modelo
    Funciones de dibujo
    Función Idle

*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h> // Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include "modelo.h"

void Punto3D::dibuja() const{
    glVertex3f(x, y, z);
}

void Punto3D::normalizar(){
  GLfloat modulo = sqrt(x * x + y * y + z * z);
  x /= modulo;
  y /= modulo;
  z /= modulo;
}

void hacerNormal(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3){
  Punto3D v1, v2, normal;
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
  glNormal3f(normal.x, normal.y, normal.z);
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

void dibujaCuadrado(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3, const Punto3D &p4){
  dibujaTriangulo(p1, p2, p3);
  dibujaTriangulo(p1, p3, p4);
}

void dibujaCuadrado(const Punto3D &normal, Punto3D &p1, const Punto3D &p2, const Punto3D &p3, const Punto3D &p4){
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

class Ejes : public Objeto3D{
public:
  float longitud = 30;
  // Dibuja el objeto
  void draw()
  {
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    {
      glColor3f(0, 1, 0);
      glVertex3f(0, 0, 0);
      glVertex3f(0, longitud, 0);

      glColor3f(1, 0, 0);
      glVertex3f(0, 0, 0);
      glVertex3f(longitud, 0, 0);

      glColor3f(0, 0, 1);
      glVertex3f(0, 0, 0);
      glVertex3f(0, 0, longitud);
    }
    glEnd();
    glEnable(GL_LIGHTING);
  }
};

class Cubo : public Objeto3D{
private:
  int lado;

public:
  Cubo(float lado)
  {
    this->lado = lado;
  }

  void draw()
  {
    float x, y, z;
    x = y = z = lado;
    //float color[4] = {0.8, 0.0, 1, 1};
    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glBegin(GL_QUAD_STRIP);
    {                            /* Caras transversales */
      glNormal3f(0.0, 0.0, 1.0); /*Vertical delantera */
      glVertex3f(x, y, z);
      glVertex3f(0, y, z);
      glVertex3f(x, 0, z);
      glVertex3f(0, 0, z);
      glNormal3f(0.0, -1.0, 0.0); /*Inferior */
      glVertex3f(x, 0, 0);
      glVertex3f(0, 0, 0);
      glNormal3f(0.0, 0.0, -1.0); /* Vertical hacia atras */
      glVertex3f(x, y, 0);
      glVertex3f(0, y, 0);
      glNormal3f(0.0, 1.0, 0.0); /* Superior, horizontal */
      glVertex3f(x, y, z);
      glVertex3f(0, y, z);
    }
    glEnd();
    glBegin(GL_QUADS);
    { /* Costados */
      glNormal3f(1.0, 0.0, 0.0);
      glVertex3f(x, 0, 0);
      glVertex3f(x, y, 0);
      glVertex3f(x, y, z);
      glVertex3f(x, 0, z);
      glNormal3f(-1.0, 0.0, 0.0);
      glVertex3f(0, 0, 0);
      glVertex3f(0, 0, z);
      glVertex3f(0, y, z);
      glVertex3f(0, y, 0);
    }
    glEnd();
  }
};

class Piramide : public Objeto3D{
  private:
    float lado, alto;
    
    Punto3D puntos[5];
  public:
    Piramide(float lado, float alto){
      this->lado = lado;
      this->alto = alto;
      puntos[0] = Punto3D(lado/2, alto, lado/2);
      puntos[1] = Punto3D(0, 0, 0);
      puntos[2] = Punto3D(lado, 0, lado);
      puntos[3] = Punto3D(lado, 0, 0);
      puntos[4] = Punto3D(0, 0, lado);
    }

    void draw(){
      dibujaCuadrado(puntos[1], puntos[3], puntos[2], puntos[4]);
      dibujaTriangulo(puntos[0], puntos[2], puntos[3]);
      dibujaTriangulo(puntos[0], puntos[4], puntos[2]);
      dibujaTriangulo(puntos[0], puntos[1], puntos[4]);
      dibujaTriangulo(puntos[0], puntos[3], puntos[1]);
    }
};

class Escalera : public Objeto3D{
  private:
    float lado, alto;
    Punto3D puntos[12];
  public:
    Escalera(float lado, float alto){
      this->lado = lado;
      this->alto = alto;
      puntos[0] = Punto3D(0, 0, 0);
      puntos[1] = Punto3D(lado, 0, 0);
      puntos[2] = Punto3D(lado, 0, lado);
      puntos[3] = Punto3D(0, 0, lado);
      puntos[4] = Punto3D(lado, alto/2, 0);
      puntos[5] = Punto3D(lado, alto/2, lado);
      puntos[6] = Punto3D(lado/2, alto/2, lado);
      puntos[7] = Punto3D(lado/2, alto/2, 0);
      puntos[8] = Punto3D(lado/2, alto, 0);
      puntos[9] = Punto3D(lado/2, alto, lado);
      puntos[10] = Punto3D(0, alto, lado);
      puntos[11] = Punto3D(0, alto, 0);
    }

    void draw(){
      dibujaCuadrado(puntos[0], puntos[1], puntos[2], puntos[3]);//Base
      dibujaCuadrado(puntos[4], puntos[7], puntos[6], puntos[5]);//Primer escalon
      dibujaCuadrado(puntos[8], puntos[11], puntos[10], puntos[9]);//Segundo escalon
      dibujaCuadrado(puntos[0], puntos[3], puntos[10], puntos[11]);//Atras
      dibujaCuadrado(puntos[1], puntos[4], puntos[5], puntos[2]);//Frente primer escalon
      dibujaCuadrado(puntos[7], puntos[8], puntos[9], puntos[6]);//Frente segundo escalon
      dibujaCuadrado(puntos[2], puntos[5], puntos[6], puntos[3]);//Lado derecho primera parte
      dibujaCuadrado(puntos[3], puntos[6], puntos[9], puntos[10]);//Lado derecho segunda parte
      dibujaCuadrado(puntos[0], puntos[7], puntos[4], puntos[1]);//Lado izquierdo primera parte
      dibujaCuadrado(puntos[0], puntos[11], puntos[8], puntos[7]);//Lado izquierdo segunda parte
    }
};

class Piramide_doble_generica :public Objeto3D{
  private:
    float radio, alto;
    int num_lados;
    Punto3D puntos[52];
  public:
    Piramide_doble_generica(float radio, float alto, int num_lados){
      this->radio = radio;
      this->alto = alto;
      if(num_lados <= 50)
        this->num_lados = num_lados;
      else
        this->num_lados = 50;
      
      for(int i = 0; i < num_lados; i++){
        puntos[i] = Punto3D(radio * (1 + cos(2 * M_PI * i / num_lados)), 0, radio * (1 + sin(2 * M_PI * i / num_lados)));
      }
      puntos[num_lados + 1] = Punto3D(radio, alto, radio);
      puntos[num_lados + 2] = Punto3D(radio, -alto, radio);
    }

    void draw(){
      for(int i = 0; i < num_lados; i++){
        dibujaTriangulo(puntos[(i + 1) % num_lados], puntos[i] , puntos[num_lados + 1]);
        dibujaTriangulo(puntos[i], puntos[(i + 1) % num_lados], puntos[num_lados + 2]);
      }
      dibujaTriangulo(puntos[1], puntos[0], puntos[4]);
      dibujaTriangulo(puntos[2], puntos[1], puntos[4]);
      dibujaTriangulo(puntos[3], puntos[2], puntos[4]);
      dibujaTriangulo(puntos[0], puntos[3], puntos[4]);
      dibujaTriangulo(puntos[0], puntos[1], puntos[5]);
      dibujaTriangulo(puntos[1], puntos[2], puntos[5]);
      dibujaTriangulo(puntos[2], puntos[3], puntos[5]);
      dibujaTriangulo(puntos[3], puntos[0], puntos[5]);
    }
};

int modo;
bool iluminacion;
Ejes ejesCoordenadas;
Cubo cubo(4.0);
Piramide piramide(4.0, 4.0);
Escalera escalera(4.0, 4.0);
Piramide_doble_generica piramide_50_lados(2.0, 4.0, 50);

/**	void initModel()

Inicializa el modelo y de las variables globales


**/
void initModel()
{
  modo = GL_FILL;
  iluminacion = true;
  glPolygonMode(GL_FRONT_AND_BACK, modo);
}

void setModo(int M){
  modo = M;
  glPolygonMode(GL_FRONT_AND_BACK, modo);
  if(modo != GL_FILL)
    iluminacion = true;
  glutPostRedisplay ();
}

void switchIluminacion(){
  if(modo == GL_FILL){
    if(iluminacion){
      iluminacion = false;
    }else{
      iluminacion = true;
    }
    glutPostRedisplay();
  }
}

/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/
void Dibuja(void)
{
  static GLfloat pos[4] = {5.0, 5.0, 10.0, 0.0}; // Posicion de la fuente de luz

  float color[4] = {0.8, 0.0, 1, 1};
  float color2[4] = {1, 0.1, 0.3, 1};
  float color3[4] = {0.1, 0.4, 0.8, 1};
  float color4[4] = {0.1, 0.8, 0.2, 1};

  glPushMatrix(); // Apila la transformacion geometrica actual

  glClearColor(0.0, 0.0, 0.0, 1.0); // Fija el color de fondo a negro

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Inicializa el buffer de color y el Z-Buffer

  transformacionVisualizacion(); // Carga transformacion de visualizacion

  glLightfv(GL_LIGHT0, GL_POSITION, pos); // Declaracion de luz. Colocada aqui esta fija en la escena

  ejesCoordenadas.draw(); // Dibuja los ejes

  if(iluminacion)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);

  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
  cubo.draw();

  glTranslatef(5.0,0.0,0.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
  piramide.draw();

  glTranslatef(-5.0,0.0,5.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
  escalera.draw();

  glTranslatef(5.0,0.0,0.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color4);
  piramide_50_lados.draw();

  glPopMatrix(); // Desapila la transformacion geometrica

  glutSwapBuffers(); // Intercambia el buffer de dibujo y visualizacion
}

/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/
void idle(int v)
{
  glutPostRedisplay();        // Redibuja
  glutTimerFunc(30, idle, 0); // Vuelve a activarse dentro de 30 ms
}
