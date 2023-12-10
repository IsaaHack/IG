#ifndef GEOMETRIA_H
#define GEOMETRIA_H

#include <objeto3D.h>
#include <malla.h>
#include <material.h>
#include <lector-jpg.h>

class Geometria : public Objeto3D
{
protected:
    Malla malla; // Malla del objeto
    Material material; // Material del objeto
    Punto3D punto_pivote; // Punto pivote
public:
    /**
     * @brief Carga un objeto PLY
     * @param nombre_archivo_ply Nombre del archivo PLY
     * @pre El archivo PLY debe existir
     * @post El objeto es modificado
    */
    virtual void cargar(const char *nombre_archivo_ply) = 0;

    /**
     * @brief Carga una textura
     * @param nombre_archivo_jpg Nombre del archivo JPG
     * @pre El archivo JPG debe existir
     * @post El objeto es modificado
    */
    virtual void cargarTextura(const char *nombre_archivo_jpg);

    /**
     * @brief Dibuja el objeto
     * @post El objeto no es modificado
    */
    virtual void draw();

    /**
     * @brief Dibuja el objeto con normales o sin normales
     * @param draw_normales Si se deben dibujar las normales
     * @post El objeto no es modificado
    */
    virtual void draw(bool draw_normales);

    /**
     * @brief Dibuja el objeto con el modo de sombreado GL_FLAT con opción de dibujar las normales.
     * @param draw_normales Si se deben dibujar las normales
     * @post El objeto no es modificado
    */
    virtual void drawFlat(bool draw_normales = false);

    /**
     * @brief Dibuja el objeto con el modo de sombreado GL_SMOOTH con opción de dibujar las normales.
     * @param draw_normales Si se deben dibujar las normales
     * @post El objeto no es modificado
    */
    virtual void drawSmooth(bool draw_normales = false);

    /**
     * @brief Borra los datos de la malla
    */
    virtual void clear();

    /**
     * @brief Modifica el modo de sombreado
     * @param modo Modo de sombreado
     * @pre modo == GL_FLAT || modo == GL_SMOOTH
     * @post El modo de sombreado es modificado
    */
    void setModoSombreado(int modo);

    /**
     * @brief Asigna un material al objeto
     * @param material Material
     * @post El objeto es modificado
    */
    void setMaterial(const Material &material);

    /**
     * @brief Asigna un punto pivote al objeto
     * @param punto_pivote Punto pivote
     * @post El objeto es modificado
    */
    void setPuntoPivote(const Punto3D &punto_pivote);

    /**
     * @brief Calcula el punto pivote del objeto
     * @post El objeto es modificado
    */
    void calcularPuntoPivote();

    /**
     * @brief Devuelve el punto pivote del objeto
     * @return Punto pivote
     * @post El objeto no es modificado
    */
    Punto3D getPuntoPivote() const;

    /**
     * @brief Escala los vértices del objeto
     * @param factor_x Factor de escala en el eje x
     * @param factor_y Factor de escala en el eje y
     * @param factor_z Factor de escala en el eje z
     * @post El objeto es modificado
     * @post Los vértices del objeto son escalados
     * @post El punto pivote es modificado
     * @post El punto pivote es escalado
     * @post Las normales de los vértices son recalculadas
    */
    virtual void escalarVertices(float factor_x, float factor_y, float factor_z);
};


#endif