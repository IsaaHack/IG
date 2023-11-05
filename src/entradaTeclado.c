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
float dCamara = 10;

void letra(unsigned char k, int x, int y)
{

  switch (k)
  {
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
  case 'h':
  case 'H':
    printHelp(); // H y h imprimen ayuda
    break;
  case '+': // acerca la cámara
    dCamara -= 5.0;
    break;
  case '-': // aleja la cámara
    dCamara += 5.0;
    break;
  case 27: // Escape  Terminar
    exit(0);
  default:
    return;
  }
  setCamara(rotxCamara, rotyCamara, dCamara);
  glutPostRedisplay(); // Algunas de las opciones cambian paramentros
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
    rotxCamara += 5.0; // Cursor arriba + rotacion x
    if (rotxCamara > 360)
      rotxCamara -= 360;
    break;
  case GLUT_KEY_DOWN:
    rotxCamara -= 5.0;
    if (rotxCamara < 0)
      rotxCamara += 360;
    break;
  case GLUT_KEY_LEFT:
    rotyCamara += 5.0;
    if (rotyCamara > 360)
      rotyCamara -= 360;
    break;
  case GLUT_KEY_RIGHT:
    rotyCamara -= 5.0;
    if (rotyCamara < 0)
      rotyCamara += 360;
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
  setCamara(rotxCamara, rotyCamara, dCamara);
  glutPostRedisplay(); // Actualiza la imagen (ver proc. letra)
}
