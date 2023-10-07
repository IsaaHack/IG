#include "malla.h"

Punto3D Malla::getVertice(int i){
    return Punto3D(i * 3, i * 3 + 1, i * 3 + 2);
}

void Malla::addNormal(int i, const Vector3D &normal){
    normales[i * 3] += normal.x;
    normales[i * 3 + 1] += normal.y;
    normales[i * 3 + 2] += normal.z;
}

void Malla::setNormal(int i, const Vector3D &normal){
    normales[i * 3] = normal.x;
    normales[i * 3 + 1] = normal.y;
    normales[i * 3 + 2] = normal.z;
}

void Malla::cargar(const char *nombre_archivo_ply)
{
    read(nombre_archivo_ply, vertices, caras);
    normales.resize(vertices.size(), 0);

    for(int i = 0; i < caras.size(); i += 3){
        Vector3D normal = obtenerNormalSinNormalizar(getVertice(caras[i]), getVertice(caras[i + 1]), getVertice(caras[i + 2]));

        addNormal(caras[i], normal);
        addNormal(caras[i + 1], normal);
        addNormal(caras[i + 2], normal);
    }

    for(int i = 0; i < normales.size(); i += 3){
        Vector3D normal(normales[i], normales[i + 1], normales[i + 2]);
        normal.normalizar();
        setNormal(i, normal);
    }
}

void Malla::draw(){

}
