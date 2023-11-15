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
#include "barridoLineal.h"
#include "geometria3D.h"
#include "aspas.h"
#include "helicoptero.h"

int modo, modo_ejecucion;
bool iluminacion, normales;
Ejes ejesCoordenadas;
Cubo cubo(4.0);
Piramide piramide(1.0, 1.0);
Escalera escalera(1.0, 1.0);
Piramide_doble_generica piramide_50_lados(2.0, 4.0, 50);
ObjetoPLY beethoven, huesos, objeto_load;
ObjetoRevolucion peon, lata, objeto_spin;
BarridoLineal cilindro, barrido;
float giro_x = 0, giro_y = 0;
Aspas aspas(&giro_x, &giro_y);
bool sentido = true;
Helicoptero helicoptero(30);


/**	void initModel()

Inicializa el modelo y de las variables globales


**/
void initModel(int modo_ejec, char *ruta_ply)
{
  modo = GL_FILL;
  iluminacion = true;
  normales = false;
  glPolygonMode(GL_FRONT_AND_BACK, modo);
  modo_ejecucion = modo_ejec;

  if(modo_ejecucion == LOAD){// Cargo el objeto que entra por parámetro
    objeto_load.cargar(ruta_ply);
  }else if(modo_ejecucion == SPIN){// Cargo el objeto de revolución que entra por parámetro
    objeto_spin.cargar(ruta_ply);
  }else{// Inicializamos los objetos de la escena
    helicoptero.cargar("./plys/heli.ply", "./plys/helices.ply");
    beethoven.cargar("./plys/beethoven.ply");
    huesos.cargar("./plys/footbones.ply");
    lata.cargar("./plys/lata-pcue.ply", 100, true, true);
    peon.cargar("./plys/perfil.ply", 100, true, true);
    Vector3D vector_trayectoria(0, 1, 0);
    Vector3D vector_trayectoria2(1, 0, 0);
    vector_trayectoria.normalizar();
    Circulo3D circulo(Punto3D(), Vector3D(-1,0,0), 0.5, 100);
    cilindro.cargar(circulo.getPuntos(), vector_trayectoria, 2);
    //barrido.cargarProbar("./plys/cuadrado.ply", Circulo3D(Punto3D(), Vector3D(0,0,1), 5, 6).getPuntos());
    barrido.cargar("./plys/cuadrado.ply", vector_trayectoria2, 3);
  }
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

void switchNormales(){
  if(modo == GL_FILL){
    if(normales){
      normales = false;
    }else{
      normales = true;
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

  float color[4] = {0.8, 0.0, 0.1, 1};
  float color2[4] = {1, 0.5, 0.3, 1};
  float color3[4] = {0.1, 0.4, 0.8, 1};
  float color4[4] = {1, 1, 1, 1};
  float color5[4] = {0.1, 0.8, 0.2, 1};
  float color6[4] = {0.8, 0.8, 0.1, 1};

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

  if(modo_ejecucion == SPIN){
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    objeto_spin.drawFlat(normales);
  }else if(modo_ejecucion == LOAD){
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    objeto_load.drawSmooth(normales);
  }else{
    
  }
  if(giro_y > 45){
    sentido = false;
  }else if(giro_y < -45){
    sentido = true;
  }

  if(sentido){
    giro_y += 0.5;
  }else{
    giro_y -= 0.5;
  }
  giro_x += 2;
  helicoptero.draw();

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
