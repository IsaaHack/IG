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

	visual.h
*/

#ifndef VISUAL_H
#define VISUAL_H

#include <objeto3D.h>

//======================== visual.c

#define PERSPECTIVA 1
#define ORTOGONAL 0


class Camara : public Objeto3D{
private:
	Punto3D focus;
	Punto3D posicion;
	bool tipo;
	bool activa;

	void inicializa(const Punto3D &posicion, const Punto3D &focus, bool tipo, bool activa);
public:
	Camara(const Punto3D &posicion, const Punto3D &focus, bool tipo = PERSPECTIVA, bool activa = false);
	Camara();
	~Camara();
	void setCamara(const Punto3D &new_posicion, const Punto3D &new_focus);
	void cambiarCoordenadasCamara(const Punto3D &new_posicion);
	void cambiarFocus(const Punto3D &new_focus);
	void moverFocus(const Punto3D &new_focus);
	void moverFocus(const Vector3D &direccion);
	void cambiarTipo(bool tipo);
	void activar();
	void desactivar();
	Punto3D getFocus() const;
	Punto3D getPosicion() const;
	bool isActiva() const;
	void draw();

	void alejar(float d);
	void acercar(float d);
	void avanzar(float d);
	void retroceder(float d);
	void izquierda(float d);
	void derecha(float d);
	void moversePerpendicularAdelante(float d);
	void moversePerpendicularAtras(float d);

	void rotarX(float angulo);
	void rotarY(float angulo);
};

class GestorCamaras{
private:
	int idCamaraActiva;
	Camara* camaraActiva;
	vector<Camara*> camaras;
	static GestorCamaras* instancia;
	GestorCamaras();
	~GestorCamaras();
public:
	void addCamara(Camara* camara);
	void setCamaraActiva(Camara* camara);
	void setCamaraActiva(int id);
	int getIdCamaraActiva() const;
	int getNumCamaras() const;
	void borrarCamara(Camara* camara);
	Camara* getCamaraActiva();
	static GestorCamaras* getInstancia();
};


/** 	void setCamara()

Cambia los parámetros de la cámara en el modulo visual

**/
void setCamara (float ax, float ay, float d);
void setCamara2 (float ax, float ay, float d);

void cambiarCoordenadasCamara2(float x, float y, float z);


/** 	void transformacionVisualizacion()

Fija la transformacion de visualizacion en funcion de los angulos de rotacion view_rotx,
view_roty y view_rotz y el desplazamiento de la camara d.

**/
void transformacionVisualizacion ();

void transformaciónVisualizacion2(float az);

/**	void fijaProyeccion()

Fija la transformacion de proyeccion en funcion del tamaño de la ventana y del tipo de proyeccion

**/
void fijaProyeccion ();


/**	void inicializaVentana(GLsizei ancho,GLsizei alto)

Inicializa el viewport para que ocupe toda la ventana X, y llama a fijaProyeccion.

**/

void inicializaVentana (GLsizei ancho, GLsizei alto);

#endif
