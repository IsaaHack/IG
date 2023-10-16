#include "objetoPLY.h"
#include <iostream>


void ObjetoPLY::cargar(const char *nombre_archivo_ply)
{
    read(nombre_archivo_ply, vertices, caras);
    normales.resize(vertices.size(), 0);
    
    for(int i = 0; i < caras.size(); i += 3){
        Vector3D normal = getCara(i / 3).getNormal();

        addNormal(caras[i], normal);
        addNormal(caras[i + 1], normal);
        addNormal(caras[i + 2], normal);
    }
    
    normalizarNormales();
}

void ObjetoPLY::draw() {
    this->Malla::draw();
}
