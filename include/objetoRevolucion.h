#ifndef OBJETOREVOLUCION_H
#define OBJETOREVOLUCION_H

#include "malla.h"

class ObjetoRevolucion : public Malla{
    protected:
        int precision;

        void calcularVertices(const vector<float> &perfil);
        void calcularTriangulos(bool tapa_superior, bool tapa_inferior);
    public:
        ObjetoRevolucion();
        void cargar(const char *nombre_archivo_ply);
        void cargar(const char *nombre_archivo_ply, int precision, bool tapa_superior = true, bool tapa_inferior = true);
        void draw();
};

#endif