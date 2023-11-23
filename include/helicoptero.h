#ifndef HELICOPTERO_H
#define HELICOPTERO_H

#include <figuraAnimada.h>
#include <transformaciones.h>
#include <objetoPLY.h>

// Valores predefinidos (ficticios) para el cálculo de la velocidad de ascenso
#define densidadAire 1.225f  // Densidad del aire en kg/m^3
#define areaRotor 25.0f    // Área del rotor en m^2
#define longitudPala 5.0f  // Longitud de la pala del rotor en metros
#define coeficienteSustentacion 0.8f  // Coeficiente de sustentación (ficticio)
#define pesoHelicoptero 5000.0f      // Peso del helicóptero en Newtons (ficticio)
#define coeficienteArrastre 0.02f  // Coeficiente de arrastre (valor ficticio, debería ser obtenido de datos reales)

/**
 * Clase que controla el helicoptero
*/
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

/**
 * Clase que representa un helicoptero
*/
class Helicoptero : public FiguraAnimada{
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
        float tiempo_cayendo;

        float calcularVelocidadAscenso();
        float calcularVelocidadDescenso(double tiempoTranscurrido);
    public:
        Helicoptero();
        void cargar();
        void cargar(const char *ply_cuerpo, const char *ply_helice);

        ControladorHelicoptero* getControlador(){return &controlador;}
        Punto3D getPosicion() const {return Punto3D(heli_x, heli_y, heli_z);}
        float getGiroHelicoptero() const {return giro_giro;}
        void actualizar();

        virtual void draw();
};

#endif