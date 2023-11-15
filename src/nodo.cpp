#include "nodo.h"

void Nodo::draw(){
    glPushMatrix();
    for (auto &hijo : this->hijos){
        hijo->draw();
    }
    glPopMatrix();
}

void Nodo::addHijo(Objeto3D *objeto)
{
    Objeto3D::addHijo(objeto);
}

void Nodo::clear(){
    Objeto3D::clear();
}