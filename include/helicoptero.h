#ifndef HELICOPTERO_H
#define HELICOPTERO_H

#include <objeto3D.h>
#include <transformaciones.h>
#include <objetoPLY.h>
#include <nodo.h>
#include <aspas.h>

//const Vector3D ejex(1, 0, 0);
//const Vector3D ejey(0, 1, 0);
//const Vector3D ejez(0, 0, 1);

class Helicoptero : public Malla{
private:
        ObjetoPLY cuerpo, helice;
        
        Nodo heli, cab, col, rot, asp;

        Rotacion ry, rx;
        
        Rotacion r1_;

        float velodidad_helice;
        float giro_x_actual, giro_y_actual;
        float *giro_x, *giro_y;

        void actualizar();
    public:
        Helicoptero();
        Helicoptero(float velodidad_helice);
        void cargar(const char *ply);
        void cargar(const char *ply_cuerpo, const char *ply_helice);

        virtual void draw();
};

#endif