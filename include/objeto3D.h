#ifndef OBJETO3D_H
#define OBJETO3D_H

#include <vector>
#include "trigonometria.h"

class Objeto3D {
protected:
    std::vector<Objeto3D *> hijos;
public:
    virtual void draw();
    virtual void addHijo(Objeto3D *objeto);
    virtual void clear();
};

#endif