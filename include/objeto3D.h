#ifndef OBJETO3D_H
#define OBJETO3D_H

#include <vector>
#include "geometria3D.h"

class Objeto3D {
protected:
    std::vector<Objeto3D *> hijos;
public:
    ~Objeto3D();
    virtual void draw() = 0;
    virtual void addHijo(Objeto3D *objeto);
    void recorrerArbol();
    void clear();
};

#endif