#ifndef OBJETOREVOLUCION_H
#define OBJETOREVOLUCION_H

#include "malla.h"

/**
 * @brief Clase que representa un objeto de revolución
 * @details Un objeto de revolución se crea a partir de un perfil y una precisión
 * @details Hereda de Malla
 * @see Malla
*/
class ObjetoRevolucion : public Malla{
    protected:
        int precision; // Número de divisiones del perfil
        int num_vertices_perfil; // Número de vértices del perfil

        /**
         * @brief Calcula los vértices de la malla a partir de un perfil
         * @param perfil Vector con los puntos del perfil
         * @pre perfil.size() > 1
         * @post perfil no se modifica
        */
        void calcularVertices(const vector<float> &perfil);

        /**
         * @brief Calcula las caras de la malla a partir de un perfil
         * @param tapa_superior Si se debe añadir la tapa superior
         * @param tapa_inferior Si se debe añadir la tapa inferior
        */
        void calcularTriangulos(bool tapa_superior, bool tapa_inferior);

        /**
         * @brief Verifica los puntos del perfil y los modifica si es necesario.
         * Si un punto no va en la misma dirección que el anterior se cambia su dirección
         * @param perfil Vector con los puntos del perfil
         * @pre perfil.size() > 1
         * @post perfil puede modificarse
         * @post El objeto no es modificado
        */
        void verificarPerfil(vector<float> &perfil) const;
    public:
        /**
         * @brief Constructor por defecto
         * @post Crea un objeto vacío con modo de sombreado GL_SMOOTH y precisión 3
        */
        ObjetoRevolucion();

        /**
         * @brief Carga un objeto a partir de un archivo PLY
         * @param nombre_archivo_ply Nombre del archivo PLY
         * @post El objeto es cargado con una precisión de 100 divisiones y con las tapas superior e inferior
        */
        void cargar(const char *nombre_archivo_ply);

        /**
         * @brief Carga un objeto a partir de un archivo PLY con una precisión y tapas dadas
         * @param nombre_archivo_ply Nombre del archivo PLY
         * @param precision Número de divisiones del perfil
         * @param tapa_superior Si se debe añadir la tapa superior
         * @param tapa_inferior Si se debe añadir la tapa inferior
         * @pre precision >= 3 y precision <= 100
         * @post El objeto es cargado con la precisión y tapas dadas
        */
        void cargar(const char *nombre_archivo_ply, int precision, bool tapa_superior = true, bool tapa_inferior = true);

        /**
         * @brief Dibuja el objeto con el modo de dibujado actual
        */
        virtual void draw();

        /**
         * @brief Dibuja el objeto con el modo de dibujado actual
         * @param draw_normales Si se deben dibujar las normales
        */
        void draw(bool draw_normales);
};

#endif