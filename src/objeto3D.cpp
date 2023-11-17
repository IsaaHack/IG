#include "objeto3D.h"

using namespace std;

void Objeto3D::addHijo(Objeto3D *objeto)
{
    hijos.push_back(objeto);
}

void Objeto3D::clear()
{
    hijos.clear();
}

void Objeto3D::draw()
{
    glPushMatrix();
    for(auto &hijo : hijos){
        hijo->draw();
    }
    glPopMatrix();
}
