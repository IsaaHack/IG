#include "piramide.h"


Piramide::Piramide(float lado, float alto){
    this->lado = lado;
    this->alto = alto;
    puntos[0] = Vector3D(lado/2, alto, lado/2);
    puntos[1] = Vector3D(0, 0, 0);
    puntos[2] = Vector3D(lado, 0, lado);
    puntos[3] = Vector3D(lado, 0, 0);
    puntos[4] = Vector3D(0, 0, lado);
}

void Piramide::draw(){
    dibujaCuadrado(puntos[1], puntos[3], puntos[2], puntos[4]);
    dibujaTriangulo(puntos[0], puntos[2], puntos[3]);
    dibujaTriangulo(puntos[0], puntos[4], puntos[2]);
    dibujaTriangulo(puntos[0], puntos[1], puntos[4]);
    dibujaTriangulo(puntos[0], puntos[3], puntos[1]);
}