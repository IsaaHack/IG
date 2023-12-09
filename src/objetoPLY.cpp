#include "objetoPLY.h"
#include <iostream>


void ObjetoPLY::cargar(const char *nombre_archivo_ply)
{
    Geometria::clear();
    
    read(nombre_archivo_ply, malla.vertices, malla.caras);
    
    malla.calcularNormalesVertices();
}

void ObjetoPLY::draw() {
    this->Geometria::draw();
}
