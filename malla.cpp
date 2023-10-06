#include "malla.h"

void Malla::cargar(const char *nombre_archivo_ply){
    ply::read(nombre_archivo_ply, vertices, caras);

    for(int i = 0; i < caras.size(); i += 3){
        Vector3D p1(vertices[caras[i] * 3], vertices[caras[i] * 3 + 1], vertices[caras[i] * 3 + 2]);
        Vector3D p2(vertices[caras[i + 1] * 3], vertices[caras[i + 1] * 3 + 1], vertices[caras[i + 1] * 3 + 2]);
        Vector3D p3(vertices[caras[i + 2] * 3], vertices[caras[i + 2] * 3 + 1], vertices[caras[i + 2] * 3 + 2]);
        Vector3D normal = obtenerNormal(p1, p2, p3);
    }
}

Malla::Malla(const char *nombre_archivo_ply){
    cargar(nombre_archivo_ply);
}