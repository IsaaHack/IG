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
#include "objetoPLY.h"
#include "objetoRevolucion.h"
#include "helicoptero.h"
#include "aspas.h"
#include "suelo.h"

int modo, modo_ejecucion;
bool iluminacion, normales;
Ejes ejesCoordenadas;
ObjetoPLY objeto_load;
ObjetoRevolucion objeto_spin;
Helicoptero helicoptero;
ControladorHelicoptero* controlador = helicoptero.getControlador();
Aspas aspas(100.0,360.0*10.0);
Suelo suelo;
int camara = 0;
Cubo dado;
Material material_dado, material_lata, material_tapas;
ObjetoRevolucion lata;
Objeto3D root_scene;
Traslacion t1(Vector3D(3, 0, 0));


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

  material_dado.setColorAmbiental(1, 1, 1, 1);
  material_dado.setColorDifuso(1, 1, 1, 1);
  material_dado.setColorEspecular(0, 0, 0, 1);
  material_dado.setExponenteBrillo(0);

  material_lata.setColorAmbiental(1, 1, 1, 1);
  material_lata.setColorDifuso(1, 1, 1, 1);
  material_lata.setColorEspecular(0.3, 0.3, 0.3, 1);
  material_lata.setExponenteBrillo(10);

  material_tapas.setColorAmbiental(1, 1, 1, 1);
  material_tapas.setColorDifuso(0.6, 0.6, 0.6, 1);
  material_tapas.setColorEspecular(1, 1, 1, 1);
  material_tapas.setExponenteBrillo(100);

  if(modo_ejecucion == LOAD){// Cargo el objeto que entra por parámetro
    root_scene.addHijo(&objeto_load);
    objeto_load.cargar(ruta_ply);
  }else if(modo_ejecucion == SPIN){// Cargo el objeto de revolución que entra por parámetro
    root_scene.addHijo(&objeto_spin);
    objeto_spin.cargar(ruta_ply);
  }else{// Inicializamos los objetos de la escena
    root_scene.addHijo(&lata);
    root_scene.addHijo(&t1);
    root_scene.addHijo(&dado);

    //helicoptero.cargar("./plys/heli.ply", "./plys/helices.ply");
    lata.cargar("./plys/lata-pcue.ply", 100, false, false);
    lata.setMaterial(material_lata);
    lata.cargarTapaInferior("./plys/lata-pinf.ply");
    lata.cargarTapaSuperior("./plys/lata-psup.ply");
    lata.cargarTexturaTapas("./textures/tapas.jpg");
    lata.escalarVertices(5, 5, 5);
    lata.setMaterialTapas(material_tapas);
    lata.cargarTextura("./textures/coke.jpg");

    dado.setModoSombreado(GL_FLAT);
    dado.setMaterial(material_dado);
    dado.cargarTextura("./textures/dado.jpg");
  }

  camara = 0;
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

ControladorHelicoptero* getControlador(){
  return controlador;
}

void cambiarCamara(){
  if(camara == 0){
    camara = 1;
  }else{
    camara = 0;
  }
  glutPostRedisplay();
}

int getCamara(){
  return camara;
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

  //aspas.actualizar();
  //helicoptero.actualizar();

  if(camara == 0){
    transformacionVisualizacion(); // Carga transformacion de visualizacion
  }else{
    Punto3D pos = helicoptero.getPosicion();
    cambiarCoordenadasCamara2(pos.x, pos.y, pos.z);
    transformaciónVisualizacion2(-helicoptero.getGiroHelicoptero());
  }
  

  glLightfv(GL_LIGHT0, GL_POSITION, pos); // Declaracion de luz. Colocada aqui esta fija en la escena

  ejesCoordenadas.draw(); // Dibuja los ejes

  if(iluminacion)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);

  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)

  root_scene.draw();

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
