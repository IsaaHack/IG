#include "nodo.h"

Nodo::~Nodo()
{
    for(auto &objeto : nodos_hijos){
        if(dynamic_cast<Transformacion*>(objeto) != nullptr)
            delete dynamic_cast<Transformacion*>(objeto);
    }
}

void Nodo::aplicar()
{
    glPushMatrix();
    for(auto &objeto : nodos_hijos){
        if(dynamic_cast<Transformacion*>(objeto) != nullptr){
            dynamic_cast<Transformacion*>(objeto)->aplicar();
        }else{
            objeto->draw();
        }
    }
    glPopMatrix();
}

void Nodo::addObjeto(Objeto3D *objeto)
{
    nodos_hijos.push_back(objeto);
}

void Nodo::addTransformacion(Transformacion *transformacion)
{
    nodos_hijos.push_back(transformacion);
}

void Nodo::addTransladacion(const Vector3D &vector_traslacion)
{
    nodos_hijos.push_back(new Traslacion(vector_traslacion));
}

void Nodo::addRotacion(const Vector3D &eje, float angulo)
{
    nodos_hijos.push_back(new Rotacion(eje, angulo));
}

void Nodo::addEscalado(const Vector3D &vector_escalado)
{
    nodos_hijos.push_back(new Escalado(vector_escalado));
}

void Nodo::addNodo(Nodo *nodo)
{
    nodos_hijos.push_back(nodo);
}
