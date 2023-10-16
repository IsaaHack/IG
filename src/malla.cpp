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

Triangulo3D Malla::getCara(int i)
{
    if(i < 0 || i >= caras.size() / 3) return Triangulo3D();
    return Triangulo3D(getVertice(caras[i * 3]), getVertice(caras[i * 3 + 1]), getVertice(caras[i * 3 + 2]));
}

void Malla::setModoSombreado(int modo){
    if(modo == GL_FLAT || modo == GL_SMOOTH)
            modo_sombreado = modo;
}

void Malla::draw() {
    if(modo_sombreado == GL_FLAT)
        glShadeModel(GL_FLAT);
    else
        glShadeModel(GL_SMOOTH);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    glNormalPointer(GL_FLOAT, 0, &normales[0]);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);

    glDrawElements(GL_TRIANGLES, caras.size(), GL_UNSIGNED_INT, &caras[0]);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glShadeModel(GL_FLAT);
}
