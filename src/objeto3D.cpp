#include "objeto3D.h"

using namespace std;

Objeto3D::~Objeto3D()
{
    clear();
}

void Objeto3D::addHijo(Objeto3D *objeto)
{
    hijos.push_back(objeto);
}

void Objeto3D::clear()
{
    hijos.clear();
}

void Objeto3D::recorrerArbol()
{

    glPushMatrix();
    draw();
    for (auto hijo : hijos)
    {
        hijo->recorrerArbol();
    }
    
    glPopMatrix();
}
