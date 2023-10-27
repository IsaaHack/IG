#ifndef BARRIDO_LINEAL_H
#define BARRIDO_LINEAL_H

#include <malla.h>

class BarridoLineal : public Malla{
    protected:
        vector<Punto3D> trayectoria;

        int num_vertices_objeto;
        int num_vertices_trayectoria;

        Vector3D obtenerNormalObjeto(const vector<float> &objeto) const;
        Punto3D calcularCentro(const vector<float> &objeto) const;
        vector<Vector3D> calcularVectoresTrayectoria(const vector<Punto3D> &trayectoria) const;
        vector<Vector3D> calcularVectoresTrayectoriaSinNormalizar(const vector<Punto3D> &trayectoria) const;
        void calcularTrayectoria(const Vector3D &vector_trayectoria, const Punto3D &centro, int num_instancias);
        void calcularTrayectoria(const vector<Vector3D> &trayectoria, const Punto3D &centro);
        void calcularVertices(const vector<float> &objeto, const Vector3D &normal_objeto);
        void calcularTriangulos();

    public:
        BarridoLineal();

        void cargar(const char *nombre_archivo_ply);

        void cargar(const char *nombre_archivo_ply, const vector<Punto3D> &trayectoria);

        void cargarProbar(const char *nombre_archivo_ply, const vector<Punto3D> &trayectoria);

        void cargar(const char *nombre_archivo_ply, const Vector3D &vector_trayectoria, int num_instancias);

        void cargar(const char *nombre_archivo_ply, const char *nombre_archivo_trayectoria);

        void draw();
};



#endif