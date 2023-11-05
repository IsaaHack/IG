#include "objetoPLY.h"
#include <iostream>


void ObjetoPLY::cargar(const char *nombre_archivo_ply)
{
    clear();
    
    read(nombre_archivo_ply, vertices, caras);
    
    calcularNormalesVertices();
}

void ObjetoPLY::draw() {
    this->Malla::draw();
}
