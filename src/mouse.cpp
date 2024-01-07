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

#define ROJO 0
#define VERDE 1
#define AZUL 2
#define ESCALA_DE_GRISES 3

#define AMBIENTAL 0
#define DIFUSION 1
#define AMBIENTAL_Y_DIFUSION 2
#define ESPECULAR 3
#define EMISION 4
#define APLICAR 5

bool botonIzquierdo = false;
bool botonDerecho = false;
bool botonCentral = false;

int ratonX = 0;
int ratonY = 0;

int menuId = -1;
int menuOption = 0;
int submenu1Id = -1;
int submenu1Option = 0;
int submenu2Id = -1;
int submenu2Option = 0;

float intensidad = 0.0;
int color = ROJO;
int tipo_material = AMBIENTAL;

bool menu_attached = false;

Geometria* seleccionado = nullptr;
Material material_seleccionado;

void clickRaton (int boton, int estado, int x, int y)
{
	switch (boton)
	{
		case GLUT_LEFT_BUTTON:
			if (estado == GLUT_DOWN)
			{
				botonIzquierdo = true;

				Geometria* old = seleccionado;

				if(seleccionado != nullptr){
					seleccionado->setMaterial(material_seleccionado);
					seleccionado = nullptr;
				}

				seleccionado = pick(x, y);

				if(seleccionado != nullptr && old != seleccionado){
					Material material = seleccionado->getMaterial();

					material.setColorEmision(0.4, 0.4, 0.4, 1.0);

					material_seleccionado = seleccionado->getMaterial();
					seleccionado->setMaterial(material);

					glutAttachMenu(GLUT_LEFT_BUTTON);
					menu_attached = true;
				}else if(seleccionado == old && seleccionado != nullptr){
					seleccionado->setMaterial(material_seleccionado);
					seleccionado = nullptr;
				}
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

				if(seleccionado != nullptr){
					seleccionado->setMaterial(material_seleccionado);
					seleccionado = nullptr;
					glutDetachMenu(GLUT_LEFT_BUTTON);
					menu_attached = false;
					modificarMenu();
				}
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

void menuOptions() {
    switch (menuOption) {
        case AMBIENTAL://Ambiental
			tipo_material = AMBIENTAL;
            break;
        case DIFUSION://Difusión
			tipo_material = DIFUSION;
            break;
		case AMBIENTAL_Y_DIFUSION://Ambiental y difusión
			tipo_material = AMBIENTAL_Y_DIFUSION;
			break;
		case ESPECULAR://Especular
			tipo_material = ESPECULAR;
			break;
		case EMISION://Emisión
			tipo_material = EMISION;
			break;
        case APLICAR://Aplicar
			aplicarMaterial();
			break;
		default:
			break;
		
    }

	menu_attached = false;
}

void submenu1Options() {
	switch (submenu1Option) {
		case ROJO://Rojo
			color = ROJO;
			break;
		case VERDE://Verde
			color = VERDE;
			break;
		case AZUL://Azul
			color = AZUL;
			break;
		case ESCALA_DE_GRISES://Escala de grises
			color = ESCALA_DE_GRISES;
			break;
		default:
			break;
	}

	menu_attached = false;
	
}

void submenu2Options() {
	switch (submenu2Option) {
		case 0:
			intensidad = 0.0;
			break;
		case 1://25%
			intensidad = 0.25;
			break;
		case 2://50%
			intensidad = 0.5;
			break;
		case 3://75%
			intensidad = 0.75;
			break;
		case 4://100%
			intensidad = 1.0;
			break;

		default:
			break;
	}
}

void menu(int option) {
    menuOption = option;
	menu_attached = false;

	menuOptions();
}

void submenu1(int option) {
	submenu1Option = option;
	menu_attached = false;

	submenu1Options();
}

void submenu2(int option) {
	submenu2Option = option;
	menu_attached = false;

	submenu2Options();
}

void createMenu() {
	submenu2Id = glutCreateMenu(submenu2);
	glutAddMenuEntry("0% *", 0);
	glutAddMenuEntry("25%", 1);
	glutAddMenuEntry("50%", 2);
	glutAddMenuEntry("75%", 3);
	glutAddMenuEntry("100%", 4);
	// Crea el menú y especifica la función de callback
	submenu1Id = glutCreateMenu(submenu1);
	glutAddMenuEntry("Rojo *", ROJO);
	glutAddMenuEntry("Verde", VERDE);
	glutAddMenuEntry("Azul", AZUL);
	glutAddMenuEntry("Escala de grises", ESCALA_DE_GRISES);
	glutAddSubMenu("Intensidad", submenu2Id);
    // Crea el menú y especifica la función de callback
    menuId = glutCreateMenu(menu);
    glutAddMenuEntry("Cambiar ambiental *", AMBIENTAL);
    glutAddMenuEntry("Cambiar difusion", DIFUSION);
	glutAddMenuEntry("Cambiar ambiental y difusion", AMBIENTAL_Y_DIFUSION);
	glutAddMenuEntry("Cambiar especular", ESPECULAR);
	glutAddMenuEntry("Cambiar emision", EMISION);
	glutAddSubMenu("Cambiar color", submenu1Id);
	glutAddMenuEntry("Aplicar", APLICAR);
    // Agrega más entradas al menú según sea necesario
}

void modificarMenu(){
	if(menu_attached){
		return;
	}
	glutSetMenu(submenu2Id);

	switch (submenu2Option) {
		case 0:
			glutChangeToMenuEntry(1, "0% *", 0);
			glutChangeToMenuEntry(2, "25%", 1);
			glutChangeToMenuEntry(3, "50%", 2);
			glutChangeToMenuEntry(4, "75%", 3);
			glutChangeToMenuEntry(5, "100%", 4);
			break;
		case 1://25%
			glutChangeToMenuEntry(1, "0%", 0);
			glutChangeToMenuEntry(2, "25% *", 1);
			glutChangeToMenuEntry(3, "50%", 2);
			glutChangeToMenuEntry(4, "75%", 3);
			glutChangeToMenuEntry(5, "100%", 4);
			break;
		case 2://50%
			glutChangeToMenuEntry(1, "0%", 0);
			glutChangeToMenuEntry(2, "25%", 1);
			glutChangeToMenuEntry(3, "50% *", 2);
			glutChangeToMenuEntry(4, "75%", 3);
			glutChangeToMenuEntry(5, "100%", 4);
			break;
		case 3://75%
			glutChangeToMenuEntry(1, "0%", 0);
			glutChangeToMenuEntry(2, "25%", 1);
			glutChangeToMenuEntry(3, "50%", 2);
			glutChangeToMenuEntry(4, "75% *", 3);
			glutChangeToMenuEntry(5, "100%", 4);
			break;
		case 4://100%
			glutChangeToMenuEntry(1, "0%", 0);
			glutChangeToMenuEntry(2, "25%", 1);
			glutChangeToMenuEntry(3, "50%", 2);
			glutChangeToMenuEntry(4, "75%", 3);
			glutChangeToMenuEntry(5, "100% *", 4);
			break;

		default:
			break;
	}

	glutSetMenu(submenu1Id);

	switch (submenu1Option) {
		case ROJO://Rojo
			glutChangeToMenuEntry(1, "Rojo *", ROJO);
			glutChangeToMenuEntry(2, "Verde", VERDE);
			glutChangeToMenuEntry(3, "Azul", AZUL);
			glutChangeToMenuEntry(4, "Escala de grises", ESCALA_DE_GRISES);
			break;
		case VERDE://Verde
			glutChangeToMenuEntry(1, "Rojo", ROJO);
			glutChangeToMenuEntry(2, "Verde *", VERDE);
			glutChangeToMenuEntry(3, "Azul", AZUL);
			glutChangeToMenuEntry(4, "Escala de grises", ESCALA_DE_GRISES);
			break;
		case AZUL://Azul
			glutChangeToMenuEntry(1, "Rojo", ROJO);
			glutChangeToMenuEntry(2, "Verde", VERDE);
			glutChangeToMenuEntry(3, "Azul *", AZUL);
			glutChangeToMenuEntry(4, "Escala de grises", ESCALA_DE_GRISES);
			break;
		case ESCALA_DE_GRISES://Escala de grises
			glutChangeToMenuEntry(1, "Rojo", ROJO);
			glutChangeToMenuEntry(2, "Verde", VERDE);
			glutChangeToMenuEntry(3, "Azul", AZUL);
			glutChangeToMenuEntry(4, "Escala de grises *", ESCALA_DE_GRISES);
			break;
		default:
			break;
	}

	glutSetMenu(menuId);

	switch (menuOption) {
		case AMBIENTAL://Ambiental
			glutChangeToMenuEntry(1, "Cambiar ambiental *", AMBIENTAL);
			glutChangeToMenuEntry(2, "Cambiar difusion", DIFUSION);
			glutChangeToMenuEntry(3, "Cambiar ambiental y difusion", AMBIENTAL_Y_DIFUSION);
			glutChangeToMenuEntry(4, "Cambiar especular", ESPECULAR);
			glutChangeToMenuEntry(5, "Cambiar emision", EMISION);
			break;
		case DIFUSION://Difusión
			glutChangeToMenuEntry(1, "Cambiar ambiental", AMBIENTAL);
			glutChangeToMenuEntry(2, "Cambiar difusion *", DIFUSION);
			glutChangeToMenuEntry(3, "Cambiar ambiental y difusion", AMBIENTAL_Y_DIFUSION);
			glutChangeToMenuEntry(4, "Cambiar especular", ESPECULAR);
			glutChangeToMenuEntry(5, "Cambiar emision", EMISION);
			break;
		case AMBIENTAL_Y_DIFUSION://Ambiental y difusión
			glutChangeToMenuEntry(1, "Cambiar ambiental", AMBIENTAL);
			glutChangeToMenuEntry(2, "Cambiar difusion", DIFUSION);
			glutChangeToMenuEntry(3, "Cambiar ambiental y difusion *", AMBIENTAL_Y_DIFUSION);
			glutChangeToMenuEntry(4, "Cambiar especular", ESPECULAR);
			glutChangeToMenuEntry(5, "Cambiar emision", EMISION);
			break;
		case ESPECULAR://Especular
			glutChangeToMenuEntry(1, "Cambiar ambiental", AMBIENTAL);
			glutChangeToMenuEntry(2, "Cambiar difusion", DIFUSION);
			glutChangeToMenuEntry(3, "Cambiar ambiental y difusion", AMBIENTAL_Y_DIFUSION);
			glutChangeToMenuEntry(4, "Cambiar especular *", ESPECULAR);
			glutChangeToMenuEntry(5, "Cambiar emision", EMISION);
			break;
		case EMISION://Emisión
			glutChangeToMenuEntry(1, "Cambiar ambiental", AMBIENTAL);
			glutChangeToMenuEntry(2, "Cambiar difusion", DIFUSION);
			glutChangeToMenuEntry(3, "Cambiar ambiental y difusion", AMBIENTAL_Y_DIFUSION);
			glutChangeToMenuEntry(4, "Cambiar especular", ESPECULAR);
			glutChangeToMenuEntry(5, "Cambiar emision *", EMISION);
			break;
		default:
			break;
	}

	menu_attached = true;
}

void aplicarMaterial(){
	GLfloat *color_seleccionado = nullptr;
	Material material;

	if(seleccionado != nullptr){
		switch (tipo_material){
			case AMBIENTAL:
				color_seleccionado = material_seleccionado.getColorAmbiental();
				break;
			case DIFUSION:
				color_seleccionado = material_seleccionado.getColorDifuso();
				break;
			case AMBIENTAL_Y_DIFUSION:
				color_seleccionado = material_seleccionado.getColorDifuso();
				break;
			case ESPECULAR:
				color_seleccionado = material_seleccionado.getColorEspecular();
				break;
			case EMISION:
				color_seleccionado = material_seleccionado.getColorEmision();
				break;
			default:
				break;
		}

		if(color_seleccionado != nullptr){
			switch (color){
				case ROJO:
					color_seleccionado[0] = intensidad;
					color_seleccionado[1] = 0.0;
					color_seleccionado[2] = 0.0;
					break;
				case VERDE:
					color_seleccionado[0] = 0.0;
					color_seleccionado[1] = intensidad;
					color_seleccionado[2] = 0.0;
					break;
				case AZUL:
					color_seleccionado[0] = 0.0;
					color_seleccionado[1] = 0.0;
					color_seleccionado[2] = intensidad;
					break;
				case ESCALA_DE_GRISES:
					color_seleccionado[0] = intensidad;
					color_seleccionado[1] = intensidad;
					color_seleccionado[2] = intensidad;
					break;
				default:
					break;
			}
		}

		if(tipo_material == AMBIENTAL_Y_DIFUSION){
			material_seleccionado.setColorAmbiental(color_seleccionado[0], color_seleccionado[1], color_seleccionado[2], 1.0);
			//material_seleccionado.setColorDifuso(color_seleccionado[0], color_seleccionado[1], color_seleccionado[2], 1.0);
		}

		material = material_seleccionado;

		material.setColorEmision(0.4, 0.4, 0.4, 1.0);

		seleccionado->setMaterial(material);
	}
}
