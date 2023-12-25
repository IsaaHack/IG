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
	modulo mouse.c
	Gestion de eventos de raton

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"

/**	 void clickRaton( int boton, int estado, int x, int y )

Procedimiento para gestionar los eventos de pulsacion de los botones del raton.

Argumentos:

boton: Codigo glut del boton que ha manipulado el usuario.

estado: Estado en el que esta el boton que se ha pulsado.

x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

**/

#define COEFICIENTE_GIRO 0.1
#define COEFICIENTE_MOVERSE 0.01

bool botonIzquierdo = false;
bool botonDerecho = false;
bool botonCentral = false;

int ratonX = 0;
int ratonY = 0;

void clickRaton (int boton, int estado, int x, int y)
{
	switch (boton)
	{
		case GLUT_LEFT_BUTTON:
			if (estado == GLUT_DOWN)
			{
				botonIzquierdo = true;
			}
			else
			{
				botonIzquierdo = false;
			}
			break;
		case GLUT_RIGHT_BUTTON:
			if (estado == GLUT_DOWN)
			{
				botonDerecho = true;
			}
			else
			{
				botonDerecho = false;
			}
			break;
		case GLUT_MIDDLE_BUTTON:
			if (estado == GLUT_DOWN)
			{
				botonCentral = true;
			}
			else
			{
				botonCentral = false;
			}
			break;
		default:
			break;
	}

	if(estado == GLUT_DOWN){
		ratonX = x;
		ratonY = y;
	}
}


/**	void RatonMovido( int x, int y )

Procedimiento para gestionar los eventos de movimiento del raton.

Argumentos:

x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

**/

void RatonMovido (int x, int y)
{
	int dx = x - ratonX;
	int dy = y - ratonY;

	if (botonIzquierdo)
	{
		
	}
	else if (botonDerecho)
	{
		GestorCamaras::getInstancia()->getCamaraActiva()->moversePerpendicularAdelante(dy*COEFICIENTE_MOVERSE);
		GestorCamaras::getInstancia()->getCamaraActiva()->derecha(-dx*COEFICIENTE_MOVERSE);
	}
	else if (botonCentral)
	{
		GestorCamaras::getInstancia()->getCamaraActiva()->rotarX(dy*COEFICIENTE_GIRO);
		GestorCamaras::getInstancia()->getCamaraActiva()->rotarY(dx*COEFICIENTE_GIRO);
	}

	ratonX = x;
	ratonY = y;
}
