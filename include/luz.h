#ifndef LUZ_H
#define LUZ_H

#include "objeto3D.h"
#include "stdio.h"
#include <stdexcept>

#define MAX_LUCES 8

/**
 * @brief Clase que representa una fuente de luz
 * @details Esta clase hereda de la clase Objeto3D
 * @see Objeto3D
 */
class Luz : public Objeto3D{
private:
    GLenum id; /**< Identificador de la fuente de luz */
    GLfloat pos[4]; /**< Posición de la fuente de luz */
    GLfloat color_ambiental[4]; /**< Color de la fuente de luz ambiental */
    GLfloat color_difuso[4]; /**< Color de la fuente de luz difuso*/
    GLfloat color_especular[4]; /**< Color de la fuente de luz especular */
    GLfloat dir[4]; /**< Dirección de la fuente de luz */
    GLfloat cutoff; /**< Ángulo de apertura de la fuente de luz */
    GLfloat exponent; /**< Exponente de la fuente de luz */
    bool activada; /**< Indica si la fuente de luz está activada */

    static bool luces[MAX_LUCES]; /**< Indica si las fuentes de luz están usandose */
public:
    /**
     * @brief Constructor por defecto
     * @post Crea una fuente de luz con id = GL_LIGHT0
     */
    Luz();

    /**
     * @brief Constructor
     * @param id Identificador de la fuente de luz
     * @post Crea una fuente de luz con el identificador id
     */
    Luz(GLenum id);

    /**
     * @brief Destructor
     * @post Destruye la fuente de luz
     */
    ~Luz();

    /**
     * @brief Establece la posición de la fuente de luz
     * @param x Coordenada x de la posición
     * @param y Coordenada y de la posición
     * @param z Coordenada z de la posición
     * @post La posición de la fuente de luz es (x, y, z)
     */
    void setPosicion(GLfloat x, GLfloat y, GLfloat z);

    /**
     * @brief Establece la dirección de la fuente de luz
     * @param x Coordenada x de la dirección
     * @param y Coordenada y de la dirección
     * @param z Coordenada z de la dirección
     * @post La dirección de la fuente de luz es (x, y, z)
     */
    void setDireccion(GLfloat x, GLfloat y, GLfloat z);

    /**
     * @brief Establece el color de la fuente de luz
     * @param r Componente roja del color
     * @param g Componente verde del color
     * @param b Componente azul del color
     * @post El color de la fuente de luz es (r, g, b)
     */
    void setColorAmbiental(GLfloat r, GLfloat g, GLfloat b);

    /**
     * @brief Establece el color difuso de la fuente de luz
     * @param r Componente roja del color
     * @param g Componente verde del color
     * @param b Componente azul del color
     * @post El color difuso de la fuente de luz es (r, g, b)
     */
    void setColorDifuso(GLfloat r, GLfloat g, GLfloat b);

    /**
     * @brief Establece el color especular de la fuente de luz
     * @param r Componente roja del color
     * @param g Componente verde del color
     * @param b Componente azul del color
     * @post El color especular de la fuente de luz es (r, g, b)
     */
    void setColorEspecular(GLfloat r, GLfloat g, GLfloat b);

    /**
     * @brief Establece el ángulo de apertura de la fuente de luz
     * @param cutoff Ángulo de apertura
     * @post El ángulo de apertura de la fuente de luz es cutoff
     */
    void setCutoff(GLfloat cutoff);

    /**
     * @brief Establece el exponente de la fuente de luz
     * @param exponent Exponente
     * @post El exponente de la fuente de luz es exponent
     */
    void setExponent(GLfloat exponent);

    /**
     * @brief Activa la fuente de luz
     * @post La fuente de luz es activada
     */
    void activar();

    /**
     * @brief Desactiva la fuente de luz
     * @post La fuente de luz es desactivada
     */
    void desactivar();

    /**
     * @brief Obtiene el identificador de la fuente de luz
     * @return Identificador de la fuente de luz
     */
    GLenum getId();

    /**
     * @brief Dibuja la fuente de luz
     * @post La fuente de luz es dibujada
     */
    virtual void draw();

    /**
     * @brief Establece la fuente de luz por defecto
     * @post La fuente de luz es establecida por defecto
     */
    void porDefecto();

    /**
     * @brief Obtiene si la fuente de luz está activada
     * @return Si la fuente de luz está activada
     */
    bool getActivada();
};



#endif