#ifndef NODO_H
#define NODO_H

#include <objeto3D.h>

class Nodo : public Objeto3D{
    public:
        Nodo() = default;
        virtual void draw();
        virtual void addHijo(Objeto3D *objeto);
        void clear();
};

#endif