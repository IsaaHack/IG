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
#include "ejes.h"
#include "cubo.h"
#include "piramide.h"
#include "escalera.h"
#include "piramide_doble_generica.h"
#include "objetoPLY.h"
#include "objetoRevolucion.h"

int modo;
bool iluminacion;
Ejes ejesCoordenadas;
Cubo cubo(4.0);
Piramide piramide(1.0, 1.0);
Escalera escalera(1.0, 1.0);
Piramide_doble_generica piramide_50_lados(2.0, 4.0, 50);
ObjetoPLY beethoven;
ObjetoRevolucion lata;

/**	void initModel()

Inicializa el modelo y de las variables globales


**/
void initModel()
{
  modo = GL_FILL;
  iluminacion = true;
  glPolygonMode(GL_FRONT_AND_BACK, modo);
  beethoven.cargar("./plys/shark.ply");
  //beethoven.setModoSombreado(GL_FLAT);
  lata.cargar("./plys/lata-pcue.ply");
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
  lata.draw();
  /**
  cubo.draw();
 
  glTranslatef(5.0,0.0,0.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
  cubo.draw();

  glTranslatef(-5.0,0.0,5.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
  escalera.draw();

  glTranslatef(5.0,0.0,0.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color4);
  piramide_50_lados.draw();
  */

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
