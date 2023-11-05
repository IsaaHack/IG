#ifndef MALLA_H
#define MALLA_H

#include "modelo.h"
#include "file_ply_stl.h"
#include "GL/glut.h"
#include <vector>

using namespace std;
using namespace ply;


/**
 * @brief Clase que representa una malla
 * @details Una malla se representa mediante un vector de vértices, un vector de caras y un vector de normales
 * @details Hereda de Objeto3D
 * @see Objeto3D
*/
class Malla : public Objeto3D
{
protected:
    vector<float> vertices; // Vector de vértices
    vector<int> caras; // Vector de caras
    vector<float> normales; // Vector de normales de vertices
    int modo_sombreado; // Modo de sombreado

    /**
     * @brief Obtiene el vértice i-ésimo
     * @param i Índice del vértice
     * @return Vértice i-ésimo
     * @pre i >= 0 && i < vertices.size() / 3
     * @post El objeto no es modificado
    */
    Punto3D getVertice(int i) const;

    /**
     * @brief Obtiene la cara i-ésima
     * @param i Índice de la cara
     * @return Cara i-ésima
     * @pre i >= 0 && i < caras.size() / 3
     * @post El objeto no es modificado
    */
    Triangulo3D getCara(int i) const;

    /**
     * @brief Obtiene la normal del vértice i-ésimo
     * @param i Índice del vértice
     * @return Normal del vértice i-ésimo
     * @pre i >= 0 && i < normales.size() / 3
     * @post El objeto no es modificado
    */
    Vector3D getNormal(int i) const;

    /**
     * @brief Establece la normal del vértice i-ésimo
     * @param i Índice del vértice
     * @param normal Normal del vértice i-ésimo
     * @pre i >= 0 && i < normales.size() / 3
     * @post La normal del vértice i-ésimo es modificada
    */
    void setNormal(int i, const Vector3D &normal);

    /**
     * @brief Suma una normal a la normal del vértice i-ésimo
     * @param i Índice del vértice
     * @param normal Normal a sumar
     * @pre i >= 0 && i < normales.size() / 3
     * @post La normal del vértice i-ésimo es modificada
    */
    void addNormal(int i, const Vector3D &normal);

    /**
     * @brief Calcula las normales de los vértices
     * @post Las normales de los vértices son calculadas
     * @post El objeto es modificado
    */
    void calcularNormalesVertices();

    /**
     * @brief Normaliza las normales de los vértices
     * @post Las normales de los vértices son normalizadas
     * @post El objeto es modificado
    */
    void normalizarNormales();

    /**
     * @brief Dibuja las normales de los vértices
     * @post El objeto no es modificado
    */
    void drawNormalesVertices() const;

    /**
     * @brief Dibuja las normales de las caras
     * @post El objeto no es modificado
    */
    void drawNormalesCaras() const;

    /**
     * @brief Borra los datos de la malla
    */
    void clear();
public:

    /**
     * @brief Carga un objeto a partir de un archivo PLY
    */
    virtual void cargar(const char *nombre_archivo_ply) = 0;

    /**
     * @brief Modifica el modo de sombreado
     * @param modo Modo de sombreado
     * @pre modo == GL_FLAT || modo == GL_SMOOTH
     * @post El modo de sombreado es modificado
    */
    virtual void setModoSombreado(int modo);

    /**
     * @brief Dibuja el objeto con el modo de dibujado actual
    */
    virtual void draw();

    /**
     * @brief Dibuja el objeto con el modo de dibujado actual con opción de dibujar las normales. draw() == draw(false)
     * @param draw_normales Si se deben dibujar las normales
     * @post El objeto no es modificado
    */
    virtual void draw(bool draw_normales);

    /**
     * @brief Dibuja el objeto con el modo de sombreado GL_SMOOTH con opción de dibujar las normales.
     * @param draw_normales Si se deben dibujar las normales
     * @post El objeto no es modificado
    */
    virtual void drawSmooth(bool draw_normales = false);

    /**
     * @brief Dibuja el objeto con el modo de sombreado GL_FLAT con opción de dibujar las normales.
     * @param draw_normales Si se deben dibujar las normales
     * @post El objeto no es modificado
    */
    virtual void drawFlat(bool draw_normales = false);
};


#endif