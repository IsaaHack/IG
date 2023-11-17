#ifndef SUELO_H
#define SUELO_H

#include <objeto3D.h>

class Suelo : public Objeto3D{
    public:
        Suelo() = default;
        void draw();
};

#endif