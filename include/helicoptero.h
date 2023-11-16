#ifndef HELICOPTERO_H
#define HELICOPTERO_H

#include <objeto3D.h>
#include <transformaciones.h>
#include <objetoPLY.h>
#include <nodo.h>

const float VELOCIDAD_MAXIMA_ASCENSO = 1.0;
const float VELOCIDAD_MAXIMA_DESCENSO = -1.0;
const float VELOCIDAD_MAXIMA_CABECEO = 1.0;
const float VELOCIDAD_MAXIMA_ALABEO = 1.0;
const float VELOCIDAD_MAXIMA_GIRO = 1.0;
const float VELOCIDAD_MAXIMA_HELICE = 3600.0;
const float ANGULO_MAXIMO_ALABEO = 45.0;
const float ANGULO_MAXIMO_CABECEO = 45.0;
const float rozamiento = 0.002;

class ControladorHelicoptero{
    private:
        bool cabeceo_delante, cabeceo_detras;
        bool alabeo_izquierda, alabeo_derecha;
        bool giro_derecha, giro_izquierda;
        bool subir, bajar;
        void estadoPorDefecto();
    public:
        ControladorHelicoptero();
        void irAlante();
        void irAtras();
        void alabeoIzquierda();
        void alabeoDerecha();
        void giroDerecha();
        void giroIzquierda();
        void subirHelicoptero();
        void bajarHelicoptero();
        bool getCabeceoDelante() const {return cabeceo_delante;}
        bool getCabeceoDetras() const {return cabeceo_detras;}
        bool getAlabeoIzquierda() const {return alabeo_izquierda;}
        bool getAlabeoDerecha() const {return alabeo_derecha;}
        bool getGiroDerecha() const {return giro_derecha;}
        bool getGiroIzquierda() const {return giro_izquierda;}
        bool getSubir() const {return subir;}
        bool getBajar() const {return bajar;}
        void actualizar();
};

class Helicoptero : public Malla{
private:
        ObjetoPLY cuerpo, helice;
        
        Nodo helicoptero, cab, col, rot, asp;

        ControladorHelicoptero controlador;

        Rotacion ry, r_helice, r_cabeceo, r_alabeo, r_giro;
        
        Rotacion r1;
        Traslacion t1, t2, posicion;

        

        float heli_x, heli_y, heli_z;
        float giro_helice, velocidad_helice;
        float giro_cabeceo, giro_alabeo, giro_giro;
        float velocidad_cabeceo, velocidad_alabeo, velocidad_giro;
        float velocidad_vertical;

        float calcularVelocidadAscenso();
        float calcularVelocidadDescenso();
        void actualizar();
    public:
        Helicoptero();
        void cargar(const char *ply);
        void cargar(const char *ply_cuerpo, const char *ply_helice);

        ControladorHelicoptero* getControlador(){return &controlador;}

        virtual void draw();
};

#endif