#ifndef NODO_H
#define NODO_H

#include <GL/glut.h>
#include "transformaciones.h"
#include <vector>
#include <queue>

class Nodo : public Transformacion{
private:
    std::vector<Objeto3D *> nodos_hijos;
    std::vector<Transformacion *> nuevos;
public:
    Nodo() = default;
    ~Nodo();

    void aplicar();
    void addObjeto(Objeto3D *objeto);
    void addTransformacion(Transformacion *transformacion);
    void addTransladacion(const Vector3D &vector_traslacion);
    void addRotacion(const Vector3D &eje, float angulo);
    void addEscalado(const Vector3D &vector_escalado);
    void addNodo(Nodo *nodo);
    void draw(){};
    
    void clear();
};

#endif