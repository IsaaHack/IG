#ifndef ASPAS_H
#define ASPAS_H

#include <figuraAnimada.h>
#include <transformaciones.h>
#include <cubo.h>

#define ANGULO_MAXIMO 45.0

//IMPORTANTE: Las animaciones estan atadas a los FPS, por lo que si se cambian los FPS, se cambia la velocidad de las animaciones

class Aspas : public FiguraAnimada{
private:
        Cubo cubo;
        
        Objeto3D a, b, c;
        Objeto3D molino, cabeza, b_, aspas, aspa;

        Rotacion ry, rx;

        static Rotacion r1, r2, r3, r4;
        static Traslacion t1, t2, t3, t4, t5;
        static Escalado s_a, s_b, s_c;

        float giro_x, giro_y;
        float velocidad_cabeza, velocidad_aspas;
        bool sentido;
    public:
        Aspas();
        Aspas(float velocidad_cabeza, float velocidad_aspas);
        virtual void actualizar();
        virtual void draw();
};

#endif
