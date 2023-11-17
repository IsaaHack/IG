#ifndef HELICOPTERO_H
#define HELICOPTERO_H

#include <objeto3D.h>
#include <transformaciones.h>
#include <objetoPLY.h>

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

//IMPORTANTE: Las animaciones estan atadas a los FPS, por lo que si se cambian los FPS, se cambia la velocidad de las animaciones

class Helicoptero : public Objeto3D{
private:
        ObjetoPLY cuerpo, helice;
        
        Objeto3D helicoptero, col, asp;

        ControladorHelicoptero controlador;

        Rotacion ry, r_helice, r_cabeceo, r_alabeo, r_giro;
        Traslacion posicion;
        
        Rotacion r1;
        Traslacion t1, t2;

        float heli_x, heli_y, heli_z;
        float giro_helice, velocidad_helice;
        float giro_cabeceo, giro_alabeo, giro_giro;
        float velocidad_cabeceo, velocidad_alabeo, velocidad_giro;
        float velocidad_vertical;

        float calcularVelocidadAscenso();
        float calcularVelocidadDescenso();
    public:
        Helicoptero();
        void cargar(const char *ply);
        void cargar(const char *ply_cuerpo, const char *ply_helice);

        ControladorHelicoptero* getControlador(){return &controlador;}
        Punto3D getPosicion() const {return Punto3D(heli_x, heli_y, heli_z);}
        float getGiroHelicoptero() const {return giro_giro;}
        void actualizar();

        virtual void draw();
};

#endif