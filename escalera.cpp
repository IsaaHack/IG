#include "escalera.h"

Escalera::Escalera(float lado, float alto){
    this->lado = lado;
    this->alto = alto;
    puntos[0] = Vector3D(0, 0, 0);
    puntos[1] = Vector3D(lado, 0, 0);
    puntos[2] = Vector3D(lado, 0, lado);
    puntos[3] = Vector3D(0, 0, lado);
    puntos[4] = Vector3D(lado, alto/2, 0);
    puntos[5] = Vector3D(lado, alto/2, lado);
    puntos[6] = Vector3D(lado/2, alto/2, lado);
    puntos[7] = Vector3D(lado/2, alto/2, 0);
    puntos[8] = Vector3D(lado/2, alto, 0);
    puntos[9] = Vector3D(lado/2, alto, lado);
    puntos[10] = Vector3D(0, alto, lado);
    puntos[11] = Vector3D(0, alto, 0);
}

void Escalera::draw(){
    dibujaCuadrado(puntos[0], puntos[1], puntos[2], puntos[3]);//Base
    dibujaCuadrado(puntos[4], puntos[7], puntos[6], puntos[5]);//Primer escalon
    dibujaCuadrado(puntos[8], puntos[11], puntos[10], puntos[9]);//Segundo escalon
    dibujaCuadrado(puntos[0], puntos[3], puntos[10], puntos[11]);//Atras
    dibujaCuadrado(puntos[1], puntos[4], puntos[5], puntos[2]);//Frente primer escalon
    dibujaCuadrado(puntos[7], puntos[8], puntos[9], puntos[6]);//Frente segundo escalon
    dibujaCuadrado(puntos[2], puntos[5], puntos[6], puntos[3]);//Lado derecho primera parte
    dibujaCuadrado(puntos[3], puntos[6], puntos[9], puntos[10]);//Lado derecho segunda parte
    dibujaCuadrado(puntos[0], puntos[7], puntos[4], puntos[1]);//Lado izquierdo primera parte
    dibujaCuadrado(puntos[0], puntos[11], puntos[8], puntos[7]);//Lado izquierdo segunda parte
}