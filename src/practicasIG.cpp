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

=======================================================

  practicasIG.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h> // Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include "iostream"
#include "entradaTeclado.h"
// #include "hiply.h"

/*=================================================*/

/**	int main( int argc, char *argv[] )
  Programa principal.

  Inicializa glut y openGL
  Crea la ventana X
  Inicializa las variables globales
  lanza los gestores de eventos
**/

void printError();

int main(int argc, char *argv[])
{
  // Inicializa glu y openGL

  glutInit(&argc, argv);

  // Comprobación de argumentos

  int modo_ejecucion = -1;
  char *nombre_fichero = NULL;

  if (argc == 2){
    if(std::string(argv[1]) == "--help"){
      printHelp();
      exit(0);
    }else{
      printError();
      exit(-1);
    }
  }else if (argc == 3){
    if (std::string(argv[1]) == "--spin"){
      modo_ejecucion = SPIN;
      nombre_fichero = argv[2];
    }else if (std::string(argv[1]) == "--load"){
      modo_ejecucion = LOAD;
      nombre_fichero = argv[2];
    }else{
      printError();
      exit(-1);
    }
  }else if (argc > 3){
    printError();
    exit(-1);
  }

  // Crea una ventana X para la salida grafica en la posicion 0,0 con tamaño 800x800, con colores RGB-alfa, con doble buffer, y
  // buffer de profundidad

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(800, 800);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("IG. Curso 2022/23. Autor: Isaac Brao Aissaoni");

  // Inicializa las variables del modelo
  initModel(modo_ejecucion, nombre_fichero);

  // Inicializa las funciones de dibujo y cambio de tamanyo de la ventana X
  glutDisplayFunc(Dibuja);
  glutReshapeFunc(inicializaVentana);

  // FUNCIONES DE INTERACCION
  glutKeyboardFunc(letra);
  glutSpecialFunc(especial);

  glutMouseFunc(clickRaton);
  glutMotionFunc(RatonMovido);

  // Funcion de fondo
  glutTimerFunc(30, idle, 0);

  // Inicializa parametros de openGL
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  // Lanza el gestor de eventos de glut
  glutMainLoop();
  return 0;
}

void printError(){
  std::cout << "Error en los argumentos" << std::endl;
  std::cout << "Uso:" << std::endl;
  std::cout << "practicasIG --help" << std::endl;
  std::cout << "practicasIG --spin fichero.ply" << std::endl;
  std::cout << "practicasIG --load fichero.ply" << std::endl;
  std::cout << "  --help: muestra esta ayuda" << std::endl;
  std::cout << "  --spin: carga el modelo y lo hace girar" << std::endl;
  std::cout << "  --load: carga el modelo y permite interaccionar con el" << std::endl;
  std::cout << "  fichero.ply: fichero ply que se carga" << std::endl;
}
