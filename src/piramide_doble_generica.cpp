#include "piramide_doble_generica.h"

Piramide_doble_generica::Piramide_doble_generica(float radio, float alto, int num_lados){
    this->radio = radio;
    this->alto = alto;
    if(num_lados <= 50)
        this->num_lados = num_lados;
    else
        this->num_lados = 50;
    
    for(int i = 0; i < num_lados; i++){
        puntos[i] = Punto3D(radio * (1 + cos(2 * M_PI * i / num_lados)), 0, radio * (1 + sin(2 * M_PI * i / num_lados)));
    }
    puntos[this->num_lados + 1] = Punto3D(radio, alto, radio);
    puntos[this->num_lados + 2] = Punto3D(radio, -alto, radio);
}

void Piramide_doble_generica::draw(){
    for(int i = 0; i < num_lados; i++){
        dibujaTriangulo(puntos[(i + 1) % num_lados], puntos[i] , puntos[num_lados + 1]);
        dibujaTriangulo(puntos[i], puntos[(i + 1) % num_lados], puntos[num_lados + 2]);
    }
    
    dibujaTriangulo(puntos[1], puntos[0], puntos[4]);
    dibujaTriangulo(puntos[2], puntos[1], puntos[4]);
    dibujaTriangulo(puntos[3], puntos[2], puntos[4]);
    dibujaTriangulo(puntos[0], puntos[3], puntos[4]);
    dibujaTriangulo(puntos[0], puntos[1], puntos[5]);
    dibujaTriangulo(puntos[1], puntos[2], puntos[5]);
    dibujaTriangulo(puntos[2], puntos[3], puntos[5]);
    dibujaTriangulo(puntos[3], puntos[0], puntos[5]);
}