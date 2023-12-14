#ifndef MATERIAL_H
#define MATERIAL_H

#include "GL/glut.h"

/**
 * @brief Clase que representa un material
 * @details Un material se representa mediante un color ambiental, difuso y especular, un exponente de brillo y un índice de refracción
 */
class Material{
private:
    GLfloat color_ambiental[4]; // Color ambiental
    GLfloat color_difuso[4]; // Color difuso
    GLfloat color_especular[4]; // Color especular
    GLfloat color_emision[4]; // Color emisión
    GLfloat exponente_brillo; // Exponente de brillo
    GLfloat indice_refraccion; // Índice de refracción
public:
    /**
     * @brief Constructor por defecto
     * @post Crea un material con color ambiental, difuso y especular blanco, exponente de brillo 0 e índice de refracción 1
     */
    Material();

    /**
     * @brief Constructor
     * @param color_ambiental Color ambiental
     * @param color_difuso Color difuso
     * @param color_especular Color especular
     * @param exponente_brillo Exponente de brillo
     * @param indice_refraccion Índice de refracción
     * @post Crea un material con los parámetros dados
     */
    Material(const GLfloat color_ambiental[4], const GLfloat color_difuso[4], const GLfloat color_especular[4], GLfloat exponente_brillo, GLfloat indice_refraccion);

    /**
     * @brief Constructor de copia
    */
    Material(const Material &m);

    /**
     * @brief Establece el color ambiental
     * @param r Componente roja
     * @param g Componente verde
     * @param b Componente azul
     * @param a Componente alfa
     */
    void setColorAmbiental(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    /**
     * @brief Establece el color difuso
     * @param r Componente roja
     * @param g Componente verde
     * @param b Componente azul
     * @param a Componente alfa
     */
    void setColorDifuso(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    /**
     * @brief Establece el color especular
     * @param r Componente roja
     * @param g Componente verde
     * @param b Componente azul
     * @param a Componente alfa
     */
    void setColorEspecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    /**
     * @brief Establece el color emisión
     * @param r Componente roja
     * @param g Componente verde
     * @param b Componente azul
     * @param a Componente alfa
     */
    void setColorEmision(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    /**
     * @brief Establece el exponente de brillo
     * @param exponente_brillo Exponente de brillo
     * @post El exponente de brillo es modificado
     */
    void setExponenteBrillo(GLfloat exponente_brillo);

    /**
     * @brief Establece el índice de refracción
     * @param indice_refraccion Índice de refracción
     * @post El índice de refracción es modificado
     */
    void setIndiceRefraccion(GLfloat indice_refraccion);

    void draw();
};

#endif