#ifndef GEOMETRIA_H
#define GEOMETRIA_H

#include <objeto3D.h>
#include <malla.h>
#include <material.h>
#include <lector-jpg.h>

class Geometria : public Objeto3D
{
protected:
    Malla malla;
    Material material;
    Punto3D punto_pivote; // Punto pivote
public:
    virtual void cargar(const char *nombre_archivo_ply) = 0;

    virtual void cargarTextura(const char *nombre_archivo_jpg);

    virtual void draw();

    virtual void draw(bool draw_normales);

    virtual void drawFlat(bool draw_normales);

    virtual void drawSmooth(bool draw_normales);

    virtual void clear();

    void setModoSombreado(int modo);

    void setMaterial(const Material &material);

    void setPuntoPivote(const Punto3D &punto_pivote);

    void calcularPuntoPivote();

    Punto3D getPuntoPivote() const;
};


#endif