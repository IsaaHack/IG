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

=======================================================

	 modelo.h
*/

#ifndef MODELO_H
#define MODELO_H

/**
	Funcion de redibujado. Se ejecuta con los eventos postRedisplay
**/
void Dibuja (void);

/**
	Funcion de fondo
**/
void idle (int v);

/**
	Funcion de inicializacion del modelo y de las variables globales
**/
void initModel ();

/**
	Funcion de inicializacion del modo de visualizacion
**/
void setModo(int M);

/** Interruptor de la iluminación*/
void switchIluminacion();

class Objeto3D 
{ 
public: 

virtual void draw( ) = 0; // Dibuja el objeto
} ; 


class Punto3D{
public:
  Punto3D(GLfloat x, GLfloat y, GLfloat z){
	this->x = x;
	this->y = y;
	this->z = z;
  }
  Punto3D(){
	x = 0;
	y = 0;
	z = 0;
  }
  
  void dibuja() const;
  void normalizar();

  GLfloat x, y, z;
};

void hacerNormal(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3);

void dibujaTriangulo(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3);

void dibujaCuadrado(const Punto3D &p1, const Punto3D &p2, const Punto3D &p3, const Punto3D &p4);

void dibujaCuadrado(const Punto3D &normal, Punto3D &p1, const Punto3D &p2, const Punto3D &p3, const Punto3D &p4);

#endif