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
#include "cubo.h"
#include "luz.h"
#include "gestorIdGeometria.h"

int modo, modo_ejecucion;
bool iluminacion, normales;
int camara = 0;

Ejes ejesCoordenadas;
Objeto3D root_scene;

ObjetoPLY objeto_load;
ObjetoRevolucion objeto_spin;

Helicoptero helicoptero;
ControladorHelicoptero* controlador = helicoptero.getControlador();
//Aspas aspas(100.0,360.0*10.0);
//Suelo suelo;

Cubo dado;
//Cubo cubo1, cubo2, cubo3;
ObjetoRevolucion lata, peon, peon1, peon2, peon3;

Traslacion t1(Vector3D(1.5, 0, 0)), t2(Vector3D(0, 0, 3)), t3(Vector3D(-3.5, 0, 0)), t4(Vector3D(2, 0, 0));

Luz luz0(GL_LIGHT0), luz1(GL_LIGHT1);

GLfloat pos_luz0[4] = {5.0, 5.0, 10.0, 0.0}; // Posicion de la fuente de luz 0
GLfloat color_luz0_ambiental[4] = {0.1, 0.1, 0.4, 1.0}; // Color especular de la fuente de luz 1 (azul)
GLfloat color_luz0_especular[4] = {0.1, 0.1, 1.0, 1.0}; // Color especular de la fuente de luz 1 (azul)
GLfloat color_luz0_difusa[4] = {0.6, 0.2, 1.0, 1.0}; // Color difuso de la fuente de luz 1 (azul)

GLfloat pos_luz1[4] = {-5.0, -5.0, 0.0, 0.0}; // Posicion de la fuente de luz 1
GLfloat color_luz1_especular[4] = {0.1, 1.0, 0.3, 1.0}; // Color especular de la fuente de luz 1 (verde)
GLfloat color_luz1_difusa[4] = {0.4, 1.0, 0.2, 1.0}; // Color difuso de la fuente de luz 1 (verde)

Material material_dado, material_lata, material_tapas, m_cubo1, m_cubo2, m_cubo3;

Camara camara1(Punto3D(0,0,10), Punto3D(), PERSPECTIVA, true);
Camara camara2;


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

  camara1.rotarX(45);
  camara1.rotarY(30);

  
  camara2.setCamara(Punto3D(-10,0,0), Punto3D());
  camara2.rotarX(45);

  luz0.setPosicion(pos_luz0[0], pos_luz0[1], pos_luz0[2]);
  //luz0.setColorAmbiental(color_luz0_ambiental[0], color_luz0_ambiental[1], color_luz0_ambiental[2]);
  //luz0.setColorEspecular(color_luz0_especular[0], color_luz0_especular[1], color_luz0_especular[2]);
  //luz0.setColorDifuso(color_luz0_difusa[0], color_luz0_difusa[1], color_luz0_difusa[2]);

  luz1.setPosicion(pos_luz1[0], pos_luz1[1], pos_luz1[2]);
  //luz1.setColorEspecular(color_luz1_especular[0], color_luz1_especular[1], color_luz1_especular[2]);
  //luz1.setColorDifuso(color_luz1_difusa[0], color_luz1_difusa[1], color_luz1_difusa[2]);

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

  m_cubo1.setColorAmbiental(0.0, 0.2, 0.0, 1);
  m_cubo1.setColorDifuso(0.0, 0.2, 0.0, 1);
  //m_cubo1.setColorEspecular(0.7, 0.9, 0.0, 1);
  //m_cubo1.setExponenteBrillo(48);

  m_cubo2.setColorAmbiental(0.1, 0.1, 0.2, 1);
  m_cubo2.setColorDifuso(0.1, 0.1, 0.2, 1);
  m_cubo2.setColorEspecular(1, 1, 1, 1);
  m_cubo2.setExponenteBrillo(16);

  m_cubo3.setColorAmbiental(0.2, 0.0, 0.0, 1);
  m_cubo3.setColorDifuso(0.2, 0.0, 0.0, 1);
  //m_cubo3.setColorEspecular(0.0, 0.9, 0.6, 1);
  m_cubo3.setColorEmision(1.0, 0.0, 0.0, 1);
  m_cubo3.setExponenteBrillo(64);

  luz0.activar();
  luz1.desactivar();

  root_scene.addHijo(&camara1);
  root_scene.addHijo(&camara2);
  root_scene.addHijo(&luz0);
  root_scene.addHijo(&luz1);

  if(modo_ejecucion == LOAD){// Cargo el objeto que entra por parámetro
    root_scene.addHijo(&objeto_load);
    objeto_load.cargar(ruta_ply);
  }else if(modo_ejecucion == SPIN){// Cargo el objeto de revolución que entra por parámetro
    root_scene.addHijo(&objeto_spin);
    objeto_spin.cargar(ruta_ply);
  }else{// Inicializamos los objetos de la escena
    root_scene.addHijo(&ejesCoordenadas);
    root_scene.addHijo(&helicoptero);
    root_scene.addHijo(&t2);
    root_scene.addHijo(&peon);
    root_scene.addHijo(&t1);
    root_scene.addHijo(&dado);
    root_scene.addHijo(&t2);
    root_scene.addHijo(&t3);
    root_scene.addHijo(&peon1);
    root_scene.addHijo(&t4);
    root_scene.addHijo(&peon2);
    root_scene.addHijo(&t4);
    root_scene.addHijo(&peon3);

    helicoptero.cargar("./plys/heli.ply", "./plys/helices.ply");

    lata.cargar("./plys/lata-pcue.ply", 50, false, false);
    lata.setMaterial(material_lata);
    lata.cargarTapaInferior("./plys/lata-pinf.ply");
    lata.cargarTapaSuperior("./plys/lata-psup.ply");
    lata.cargarTexturaTapas("./textures/tapas.jpg");
    lata.escalarVertices(5, 5, 5);
    lata.setMaterialTapas(material_tapas);
    lata.cargarTextura("./textures/coke.jpg");

    peon.cargar("./plys/perfil.ply", 50, false, false);
    peon.setMaterial(material_lata);
    peon.cargarTextura("./textures/s_textura_test.jpg");

    dado.setModoSombreado(GL_FLAT);
    dado.setMaterial(material_dado);
    dado.cargarTextura("./textures/dado.jpg");

    peon1.cargar("./plys/perfil.ply", 50, true, true);
    peon1.setMaterial(m_cubo1);

    peon2.cargar("./plys/perfil.ply", 50, true, true);
    peon2.setMaterial(m_cubo2);

    peon3.cargar("./plys/perfil.ply", 50, true, true);
    peon3.setMaterial(m_cubo3);
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
    iluminacion = !iluminacion;

    if(iluminacion)
      glEnable(GL_LIGHTING);
    else
      glDisable(GL_LIGHTING);

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

void switchLuz(int luz){
  if(luz == 0){
    if(luz0.getActivada()){
      luz0.desactivar();
    }else{
      luz0.activar();
    }
  }else if(luz == 1){
    if(luz1.getActivada()){
      luz1.desactivar();
    }else{
      luz1.activar();
    }
  }
  glutPostRedisplay();
}

Geometria* pick(int x, int y){
  GLint viewport[4];
  unsigned char color[4];
  bool iluminacion = glIsEnabled(GL_LIGHTING);

  glClearColor(0.0, 0.0, 0.0, 1.0); // Fija el color de fondo a negro

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glGetIntegerv(GL_VIEWPORT, viewport);
  glDisable(GL_DITHER);
  glDisable(GL_LIGHTING);

  GestorIdGeometria::getInstancia()->setModo(MODO_SELECCION);
  root_scene.draw();
  glReadPixels(x, viewport[3] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);

  GestorIdGeometria::getInstancia()->setModo(MODO_NORMAL);

  glEnable(GL_DITHER);
  if(iluminacion)
    glEnable(GL_LIGHTING);

  unsigned int id = (color[0]-1) + (color[1]-1) * 256 + (color[2]-1) * 256 * 256;
  id /= 2;
  
  if(id == 0)
    return nullptr;
  
  return GestorIdGeometria::getInstancia()->getGeometria(id);
}

/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/
void Dibuja(void)
{

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
  helicoptero.actualizar();
  if(GestorCamaras::getInstancia()->getIdCamaraActiva() == 1){
    Punto3D pos = helicoptero.getPosicion();

    GestorCamaras::getInstancia()->getCamaraActiva()->moverFocus(pos);
  }

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
  modificarMenu();
  glutPostRedisplay();        // Redibuja
  glutTimerFunc(30, idle, 0); // Vuelve a activarse dentro de 30 ms
}
