/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: Isaac Brao Aissaoni

	Programa principal
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
modulo visual.c
    Inicialización de ventana X
    Transformación de visualización
    Transformación de proyección
 
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include "visual.h"

void Camara::inicializa(const Punto3D &posicion, const Punto3D &focus, bool tipo, bool activa){
  GestorCamaras::getInstancia()->addCamara(this);
  setCamara(posicion, focus);
  this->tipo = tipo;
  
  if (activa)
    GestorCamaras::getInstancia()->setCamaraActiva(this);
}

Camara::Camara(const Punto3D &posicion, const Punto3D &focus, bool tipo, bool activa){
  inicializa(posicion, focus, tipo, activa);
}

Camara::Camara(){
  inicializa(Punto3D(0, 0, 10), Punto3D(0, 0, 0), PERSPECTIVA, false);
}

Camara::~Camara(){
  GestorCamaras::getInstancia()->borrarCamara(this);
}

void Camara::setCamara(const Punto3D &new_posicion, const Punto3D &new_focus){
  posicion = new_posicion;
  focus = new_focus;
}

void Camara::cambiarCoordenadasCamara(const Punto3D &new_posicion){
  posicion = new_posicion;
}

void Camara::cambiarFocus(const Punto3D &new_focus){
  focus = new_focus;
}

void Camara::moverFocus(const Punto3D &new_focus){
  moverFocus(Vector3D(new_focus) - Vector3D(focus));
}

void Camara::moverFocus(const Vector3D &direccion){
  posicion.x += direccion.x;
  posicion.y += direccion.y;
  posicion.z += direccion.z;

  focus.x += direccion.x;
  focus.y += direccion.y;
  focus.z += direccion.z;
}

void Camara::cambiarTipo(bool tipo){
  this->tipo = tipo;
}

void Camara::activar(){
  activa = true;
}

void Camara::desactivar(){
  if(activa){
    activa = false;
  }
}

Punto3D Camara::getFocus() const{
  return focus;
}

Punto3D Camara::getPosicion() const{
  return posicion;
}

bool Camara::isActiva() const{
  return activa;
}

void Camara::draw(){
  if (!activa){
    //printf("No se puede dibujar una camara que no esta activa\n");
    return;
  }

  //printf("Dibujando camara\n");

  //glMatrixMode(GL_MODELVIEW);
  //glLoadIdentity();
  if(tipo == ORTOGONAL)
    glOrtho(20, 20, 20, 20, 1, 100);
  
    //gluPerspective(60.0, 1.0, 1.0, 1000.0);
  gluLookAt(posicion.x, posicion.y, posicion.z, focus.x, focus.y, focus.z, 0.0f, 1.0f, 0.0f);
  //glTranslatef(x, y, z);
}

void Camara::alejar(float d){
  Vector3D v(Vector3D(posicion) - Vector3D(focus));
  float modulo = v.mod();

  v = v * (d / modulo);

  posicion.x += v.x;
  posicion.y += v.y;
  posicion.z += v.z;
}

void Camara::acercar(float d){
  Vector3D v(Vector3D(posicion) - Vector3D(focus));
  float modulo = v.mod();

  v = v * (d / modulo);

  posicion.x -= v.x;
  posicion.y -= v.y;
  posicion.z -= v.z;
}

void Camara::avanzar(float d){
  Vector3D v(Vector3D(focus) - Vector3D(posicion));
  v.normalizar();
  
  v = v * d;

  posicion.x += v.x;
  posicion.y += v.y;
  posicion.z += v.z;

  focus.x += v.x;
  focus.y += v.y;
  focus.z += v.z;
}

void Camara::retroceder(float d){
  avanzar(-d);
}

void Camara::izquierda(float d){
  derecha(-d);
}

void Camara::derecha(float d){
  Vector3D v(Vector3D(focus) - Vector3D(posicion));
  v.normalizar();

  Vector3D ejeGiro = v ^ ejey;
  ejeGiro.normalizar();

  ejeGiro = ejeGiro * d;

  posicion.x += ejeGiro.x;
  posicion.y += ejeGiro.y;
  posicion.z += ejeGiro.z;

  focus.x += ejeGiro.x;
  focus.y += ejeGiro.y;
  focus.z += ejeGiro.z;
}

void Camara::moversePerpendicularAdelante(float d){
  Vector3D v(focus.x - posicion.x, 0, focus.z - posicion.z);
  v.normalizar();

  v = v * d;

  posicion.x += v.x;
  posicion.z += v.z;

  focus.x += v.x;
  focus.z += v.z;
}

void Camara::moversePerpendicularAtras(float d){
  moversePerpendicularAdelante(-d);
}

void Camara::rotarX(float angulo){
  angulo *= M_PI / 180.0;

  Vector3D v(Vector3D(posicion) - Vector3D(focus));

  v.normalizar();

  Vector3D ejeGiro = v ^ ejey;
  ejeGiro.normalizar();

  MatrizRotacion m(angulo, ejeGiro);

  posicion.x -= focus.x;
  posicion.y -= focus.y;
  posicion.z -= focus.z;

  Punto3D p(posicion);

  p = m * p;
  
  if(posicion.z <= 0 && p.z <= 0 || posicion.z >= 0 && p.z >= 0){
    posicion.x = p.x;
    posicion.z = p.z;
    posicion.y = p.y;
  }

  posicion.x += focus.x;
  posicion.y += focus.y;
  posicion.z += focus.z;
}

void Camara::rotarY(float angulo){
  angulo *= M_PI / 180.0;

  MatrizRotacion m(angulo, ejey);

  posicion.x -= focus.x;
  posicion.y -= focus.y;
  posicion.z -= focus.z;

  Punto3D p(posicion);

  p = m * p;

  posicion.x = p.x;
  posicion.z = p.z;
  //posicion.y = p.y;

  posicion.x += focus.x;
  posicion.y += focus.y;
  posicion.z += focus.z;
}

GestorCamaras* GestorCamaras::instancia = nullptr;

GestorCamaras::GestorCamaras(){
  if(instancia != nullptr)
    throw std::invalid_argument("Ya existe una instancia de GestorCamaras");
  
  instancia = this;

  camaraActiva = nullptr;
  idCamaraActiva = -1;
}

GestorCamaras::~GestorCamaras(){
  if(instancia != nullptr)
    delete instancia;
}

void GestorCamaras::addCamara(Camara* camara){
  camaras.push_back(camara);
}

void GestorCamaras::setCamaraActiva(Camara* camara){
  if(camara == nullptr){
    camaraActiva = nullptr;
    idCamaraActiva = -1;
    return;
  }

  if(camara->isActiva())
    return;

  for(int i = 0; i < camaras.size(); i++){
    if(camaras[i] == camara){
      idCamaraActiva = i;
      break;
    }
  }

  if(camaraActiva != nullptr)
    camaraActiva->desactivar();

  camaraActiva = camara;  

  camaraActiva->activar();
}

void GestorCamaras::setCamaraActiva(int id){
  if(id < 0 || id >= camaras.size())
    return;

  printf("Nueva camara activa %d\n", id);


  if(camaraActiva != nullptr)
    camaraActiva->desactivar();

  camaraActiva = camaras[id];

  idCamaraActiva = id;

  camaraActiva->activar();
}

int GestorCamaras::getIdCamaraActiva() const{
  return idCamaraActiva;
}

int GestorCamaras::getNumCamaras() const{
  return camaras.size();
}

void GestorCamaras::borrarCamara(Camara* camara){
  if (camara == nullptr)
    return;

  if(camara == camaraActiva){
    camaras.erase(camaras.begin() + idCamaraActiva);
    setCamaraActiva(nullptr);
    return;
  }

  for(int i = 0; i < camaras.size(); i++){
    if(camaras[i] == camara){
      camaras.erase(camaras.begin() + i);
      break;
    }
  }
}

Camara* GestorCamaras::getCamaraActiva(){
  return camaraActiva;
}

GestorCamaras* GestorCamaras::getInstancia(){
  if(instancia == nullptr)
    instancia = new GestorCamaras();

  return instancia;
}


//================================================ VARIABLES  

/**

Angulos de rotacion de la camara.

**/

float view_rotx = 30, view_roty = 45;
float view_rotx2 = 45, view_roty2 = 90;
float x_camara2 = 0, y_camara2 = 0, z_camara2 = 0;


/**

Distancia de la cámara

**/

float D = 10;


/**

Tamaño de la ventana X

**/


float anchoVentana, altoVentana;




/** 	void setCamara()

Cambia los parámetros de la cámara en el modulo visual

**/
void setCamara (float ax, float ay, float d)
{
  view_rotx = ax;
  view_roty = ay;

  D = d;
}

void setCamara2 (float ax, float ay, float d)
{
  view_rotx2 = ax;
  view_roty2 = ay;

  D = d;
}

void cambiarCoordenadasCamara2(float x, float y, float z)
{
  x_camara2 = x;
  y_camara2 = y;
  z_camara2 = z;
}


/** 	void transformacionVisualizacion()

Fija la transformacion de visualizacion en funcion de los angulos de rotacion view_rotx,
view_roty y el desplazamiento de la camara D.

La cámara mira al origen de coordenadas a una distancia D desde la posición angular view_rotx,
view_roty;

**/
void transformacionVisualizacion ()
{
  glTranslatef (0, 0, -D);

  glRotatef (view_rotx, 1.0, 0.0, 0.0);
  glRotatef (view_roty, 0.0, 1.0, 0.0);

  // glTranslatef(-x_camara,-y_camara,-z_camara);
}

void transformaciónVisualizacion2(float az)
{
  float angle_y = (view_roty2 + az) * M_PI / 180.0;  // Ángulo de rotación alrededor del eje y en radianes
  float angle_x = view_rotx2 * M_PI / 180.0;  // Ángulo de rotación alrededor del eje z en radianes

  float camera_x = x_camara2 + D * cos(angle_x) * sin(angle_y);
  float camera_y = y_camara2 + D * sin(angle_x);
  float camera_z = z_camara2 - D * cos(angle_x) * cos(angle_y);

  // Configura la matriz de vista usando gluLookAt
  gluLookAt(camera_x, camera_y, camera_z,  // Posición de la cámara
            x_camara2, y_camara2, z_camara2,  // Punto al que está mirando
            0.0f, 1.0f, 0.0f);  // Vector de orientación
  

  //glTranslatef(x_camara2, y_camara2, z_camara2);
  //glRotatef(az+view_roty2,0.0,1.0,0.0);
  //glRotatef(view_rotx2,0.0,0.0,1.0); // no funca
  //glTranslatef(-x_camara2, -y_camara2, -z_camara2);
  
}

 /**	void fijaProyeccion()

 Fija la transformacion de proyeccion en funcion del tamaño de la ventana y del tipo de proyeccion

 **/
void fijaProyeccion ()
{
  float calto;			// altura de la ventana corregida

  if (anchoVentana > 0)
    calto = altoVentana / anchoVentana;
  else
    calto = 1;

  glFrustum (-1, 1, -calto, calto, 1.5, 1500);

  glMatrixMode (GL_MODELVIEW);
// A partir de este momento las transformaciones son de modelado.       
  glLoadIdentity ();

}


/**	void inicializaVentana(GLsizei ancho,GLsizei alto)

Inicializa el viewport para que ocupe toda la ventana X, y llama a fijaProyeccion.

**/

void inicializaVentana (GLsizei ancho, GLsizei alto)
{
  altoVentana = alto;
  anchoVentana = ancho;

  glViewport (0, 0, ancho, alto);	// Establecemos el Viewport usando la nueva anchura y altura de la ventana X

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  fijaProyeccion ();		// Cargamos la transformacion de proyeccion

}
