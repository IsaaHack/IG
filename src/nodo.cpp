#include "nodo.h"

Nodo::~Nodo() = default;
/**
{
    
    for(auto nuevo : nuevos){
        if(dynamic_cast<Rotacion*>(nuevo) != nullptr){
            delete dynamic_cast<Rotacion*>(nuevo);
        }else if(dynamic_cast<Traslacion*>(nuevo) != nullptr){
            delete dynamic_cast<Traslacion*>(nuevo);
        }else if(dynamic_cast<Escalado*>(nuevo) != nullptr){
            delete dynamic_cast<Escalado*>(nuevo);
        }
    }
    

}
*/

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
    Traslacion *traslacion = new Traslacion(vector_traslacion);
    nuevos.push_back(traslacion);
    nodos_hijos.push_back(nuevos.back());
}

void Nodo::addRotacion(const Vector3D &eje, float angulo)
{
    Rotacion *rotacion = new Rotacion(eje, angulo);
    nuevos.push_back(rotacion);
    nodos_hijos.push_back(nuevos.back());
}

void Nodo::addEscalado(const Vector3D &vector_escalado)
{
    Escalado *escalado = new Escalado(vector_escalado);
    nuevos.push_back(escalado);
    nodos_hijos.push_back(nuevos.back());
}

void Nodo::addNodo(Nodo *nodo)
{
    nodos_hijos.push_back(nodo);
}

void Nodo::clear()
{
    nodos_hijos.clear();
}
