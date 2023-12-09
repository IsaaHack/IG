#ifndef OBJETO_PLY_H
#define OBJETO_PLY_H

#include "geometria.h"

class ObjetoPLY : public Geometria{
public:
    /**
     * @brief Constructor por defecto
     * @post Crea un objeto vacío con modo de sombreado GL_SMOOTH
    */
    ObjetoPLY(){
        setModoSombreado(GL_SMOOTH);
    };

    /**
     * @brief Carga un objeto a partir de un archivo PLY
     * @param nombre_archivo_ply Nombre del archivo PLY
     * @post El objeto es cargado
    */
    void cargar(const char *nombre_archivo_ply);

    /**
     * @brief Dibuja el objeto con el modo de sombreado establecido
     * @post El objeto no es modificado
    */
    virtual void draw();
};

#endif