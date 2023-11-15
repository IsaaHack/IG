#ifndef ASPAS_H
#define ASPAS_H

#include <objeto3D.h>
#include <transformaciones.h>
#include <cubo.h>
#include <nodo.h>

const Vector3D ejex(1, 0, 0);
const Vector3D ejey(0, 1, 0);
const Vector3D ejez(0, 0, 1);

class Aspas : public Objeto3D{
private:
        Cubo cubo;
        
        Nodo a, b, c;
        Nodo molino, cabeza, b_, aspas, aspa;

        Rotacion ry, rx;

        static Rotacion r1, r2, r3, r4;
        static Traslacion t1, t2, t3, t4, t5;
        static Escalado s_a, s_b, s_c;

        float *giro_x, *giro_y;

        void actualizar();
    public:
        Aspas();
        Aspas(float *giro_x, float *giro_y);
        virtual void draw();
};

#endif
