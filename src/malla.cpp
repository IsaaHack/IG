#include "malla.h"

Punto3D Malla::getVertice(int i){
    return Punto3D(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]);
}

void Malla::addNormal(int i, const Vector3D &normal){
    if(i >= 0 && i < normales.size() / 3){
        normales[i * 3] += normal.x;
        normales[i * 3 + 1] += normal.y;
        normales[i * 3 + 2] += normal.z;
    }
}

void Malla::normalizarNormales(){
    for(int i = 0; i < normales.size(); i += 3){
        Vector3D normal(normales[i], normales[i + 1], normales[i + 2]);
        normal.normalizar();
        setNormal(i / 3, normal);
    }
}

void Malla::setNormal(int i, const Vector3D &normal){
    if(i >= 0 && i < normales.size() / 3){
        normales[i * 3] = normal.x;
        normales[i * 3 + 1] = normal.y;
        normales[i * 3 + 2] = normal.z;
    }
}

void Malla::setModoSombreado(int modo){
    if(modo == GL_FLAT || modo == GL_SMOOTH)
            modo_sombreado = modo;
}
