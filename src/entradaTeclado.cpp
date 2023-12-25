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
modulo entradaTeclado.c
  Gestion de eventos de teclado
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h> // Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include "helicoptero.h"
#include "visual.h"

/**

Imprime en la consola las instrucciones del programa

**/
void printHelp()
{

  printf("\n\n     Prácticas de Informática Gráfica	Curso 2022-2023");
  printf("\n\n Dpto. Lenguajes y Sistemas Informaticos");
  printf("\n E.T.S.I. Informatica		Univ. de Granada ");
  printf("\n");
  printf("\n Opciones: \n\n");
  printf("h, H: Imprime informacion de ayuda \n");
  printf("PgUp, PgDn: avanza y retrocede la cámara \n\n");
  printf("+,-: avanza y retrocede la cámara \n\n");
  printf("Teclas de movimiento de cursor: giran la camara\n\n");
  // Anyade la informacion de las opciones que introduzcas aqui !!
  printf("p, P: Modo de visualización en puntos\n");
  printf("l, L: Modo de visualización en lineas\n");
  printf("f, F: Modo de visualización en relleno\n");
  printf("i, I: Activa/desactiva iluminación\n");
  printf("n, N: Activa/desactiva normales\n");
  // Opcion de la camara
  printf("v, V: Cambia la cámara\n");
  // Opciones del helicoptero
  printf("w, W: Avanza el helicóptero\n");
  printf("s, S: Retrocede el helicóptero\n");
  printf("a, A: Alabeo a la izquierda\n");
  printf("d, D: Alabeo a la derecha\n");
  printf("q, Q: Giro a la izquierda\n");
  printf("e, E: Giro a la derecha\n");
  printf("espacio: Subir el helicóptero\n");
  printf("c, C: Bajar el helicóptero\n");
  // Opciones de las luces
  printf("1: Activa/desactiva la luz 1\n");
  printf("2: Activa/desactiva la luz 2\n");
  //Final
  printf("\n Escape: Salir");
  printf("\n\n\n");
}

/* @teclado ---------------------------------------------------------------- */

/** 		void letra (unsigned char k, int x, int y)

Este procedimiento es llamado por el sistema cuando se pulsa una tecla normal
El codigo k es el ascii de la letra

Para anyadir nuevas ordenes de teclado coloca el correspondiente case.

Parametros de entrada:

k: codigo del caracter pulsado

x:

y:

**/

float rotxCamara = 30, rotyCamara = 45;
float rotxCamara2 = 45, rotyCamara2 = -90;
float dCamara = 10;

void letra(unsigned char k, int x, int y)
{

  switch (k)
  {
  case 'w':
  case 'W':
    if(GestorCamaras::getInstancia()->getIdCamaraActiva() == 1)
      getControlador()->irAlante();
    else GestorCamaras::getInstancia()->getCamaraActiva()->avanzar(1.0);
    break;
  case 's':
  case 'S':
    if(GestorCamaras::getInstancia()->getIdCamaraActiva() == 1)
      getControlador()->irAtras();
    else GestorCamaras::getInstancia()->getCamaraActiva()->retroceder(1.0);
    break;
  case 'a':
  case 'A':
    if(GestorCamaras::getInstancia()->getIdCamaraActiva() == 1)
      getControlador()->alabeoIzquierda();
    else GestorCamaras::getInstancia()->getCamaraActiva()->izquierda(1.0);
    break;
  case 'd':
  case 'D':
    if(GestorCamaras::getInstancia()->getIdCamaraActiva() == 1)
      getControlador()->alabeoDerecha();
    else GestorCamaras::getInstancia()->getCamaraActiva()->derecha(1.0);
    break;
  case 'r':
  case 'R':
    if(GestorCamaras::getInstancia()->getIdCamaraActiva() == 0){
      GestorCamaras::getInstancia()->getCamaraActiva()->setCamara(Punto3D(0, 0, 10), Punto3D(0, 0, 0));
      GestorCamaras::getInstancia()->getCamaraActiva()->rotarX(45);
      GestorCamaras::getInstancia()->getCamaraActiva()->rotarY(30);
    }
    break;
  case 'q':
  case 'Q':
    if(GestorCamaras::getInstancia()->getIdCamaraActiva() == 1)
      getControlador()->giroIzquierda();
    break;
  case 'e':
  case 'E':
    if(GestorCamaras::getInstancia()->getIdCamaraActiva() == 1)
      getControlador()->giroDerecha();
    break;
  case ' ':
    if(GestorCamaras::getInstancia()->getIdCamaraActiva() == 1)
      getControlador()->subirHelicoptero();
    break;
  case 'c':
  case 'C':
    if(GestorCamaras::getInstancia()->getIdCamaraActiva() == 1)
      getControlador()->bajarHelicoptero();
    break;
  case 'p':
  case 'P':
    setModo(GL_POINT);
    break;
  case 'l':
  case 'L':
    setModo(GL_LINE);
    break;
  case 'f':
  case 'F':
    setModo(GL_FILL);
    break;
  case 'i':
  case 'I':
    switchIluminacion();
    break;
  case 'n':
  case 'N':
    switchNormales();
    break;
  case 'v':
  case 'V':
    cambiarCamara();
    GestorCamaras::getInstancia()->setCamaraActiva((1 + GestorCamaras::getInstancia()->getIdCamaraActiva()) % GestorCamaras::getInstancia()->getNumCamaras());
    break;
  case 'h':
  case 'H':
    printHelp(); // H y h imprimen ayuda
    break;
  case '+': // acerca la cámara
    dCamara -= 5.0;
    GestorCamaras::getInstancia()->getCamaraActiva()->alejar(-5.0);
    break;
  case '-': // aleja la cámara
    dCamara += 5.0;
    GestorCamaras::getInstancia()->getCamaraActiva()->alejar(5.0);
    break;
  case '1':
    switchLuz(0);
    break;
  case '2':
    switchLuz(1);
    break;
  case 27: // Escape  Terminar
    exit(0);
  default:
    return;
  }
  if(getCamara() == 0)
    setCamara(rotxCamara, rotyCamara, dCamara);
  else setCamara2(rotxCamara2, rotyCamara2, dCamara);
  //quito el redisplays porque no hace falta actualizar la imagen
  //glutPostRedisplay(); // Algunas de las opciones cambian paramentros
} // de la camara. Es necesario actualziar la imagen

/**		void especial(int k, int x, int y)
Este procedimiento es llamado por el sistema cuando se pulsa una tecla
especial. El codigo k esta definido en glut mediante constantes

Parametros de entrada:

k: codigo del caracter pulsado (definido en glut mediante constantes).

x:

y:

**/
void especial(int k, int x, int y)
{

  switch (k)
  {
  case GLUT_KEY_UP:
    GestorCamaras::getInstancia()->getCamaraActiva()->rotarX(5.0);
    if(getCamara() == 0){
      rotxCamara += 5.0; // Cursor arriba + rotacion x
      if (rotxCamara > 360)
        rotxCamara -= 360;
    }else{
      rotxCamara2 += 5.0; // Cursor arriba + rotacion x
      if (rotxCamara2 > 360)
        rotxCamara2 -= 360;
    }
    break;
  case GLUT_KEY_DOWN:
    GestorCamaras::getInstancia()->getCamaraActiva()->rotarX(-5.0);
    if(getCamara() == 0)
      rotxCamara -= 5.0; // Cursor abajo - rotacion x
      if (rotxCamara < 0)
        rotxCamara += 360;
    else{
      rotxCamara2 -= 5.0; // Cursor abajo - rotacion x
      if (rotxCamara2 < 0)
        rotxCamara2 += 360;
    }
    break;
  case GLUT_KEY_LEFT:
  GestorCamaras::getInstancia()->getCamaraActiva()->rotarY(-5.0);
    if(getCamara() == 0){
      rotyCamara += 5.0; // Cursor izquierda + rotacion y
      if (rotyCamara > 360)
        rotyCamara -= 360;
    }else{
      rotyCamara2 += 5.0; // Cursor izquierda + rotacion y
      if (rotyCamara2 > 360)
        rotyCamara2 -= 360;
    }
    break;
  case GLUT_KEY_RIGHT:
    GestorCamaras::getInstancia()->getCamaraActiva()->rotarY(5.0);
    if(getCamara() == 0){
      rotyCamara -= 5.0; // Cursor derecha - rotacion y
      if (rotyCamara < 0)
        rotyCamara += 360;
    }else{
      rotyCamara2 -= 5.0; // Cursor derecha - rotacion y
      if (rotyCamara2 < 0)
        rotyCamara2 += 360;
    }
    break;
  case GLUT_KEY_PAGE_DOWN: // acerca la cámara
    dCamara -= 5.0;
    break;
  case GLUT_KEY_PAGE_UP: // aleja la cámara
    dCamara += 5.0;
    break;
  default:
    return;
  }

  if(rotxCamara2 == 90)
    rotxCamara2 = 85;
  else if(rotxCamara2 == 270)
    rotxCamara2 = 275;

  if(getCamara() == 0)
    setCamara(rotxCamara, rotyCamara, dCamara);
  else setCamara2(rotxCamara2, rotyCamara2, dCamara);
  //glutPostRedisplay(); // Actualiza la imagen (ver proc. letra)
}
