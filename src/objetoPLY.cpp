#include "objetoPLY.h"
#include <iostream>

void ObjetoPLY::cargar(const char *nombre_archivo_ply)
{
    read(nombre_archivo_ply, vertices, caras);
    normales.resize(vertices.size(), 0);

    
    for(int i = 0; i < caras.size(); i += 3){
        Vector3D normal = obtenerNormalSinNormalizar(getVertice(caras[i]), getVertice(caras[i + 1]), getVertice(caras[i + 2]));

        addNormal(caras[i], normal);
        addNormal(caras[i + 1], normal);
        addNormal(caras[i + 2], normal);
    }
    
    normalizarNormales();
}

void ObjetoPLY::draw()
{
    if(modo_sombreado == GL_FLAT)
        glShadeModel(GL_FLAT);
    else
        glShadeModel(GL_SMOOTH);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    if(modo_sombreado == GL_SMOOTH)
        glNormalPointer(GL_FLOAT, 0, &normales[0]);
    else{
        vector<float> normales_caras;
        normales_caras.resize(caras.size(), 0);
        for(int i = 0; i < caras.size(); i += 3){
            Vector3D normal = obtenerNormal(getVertice(caras[i]), getVertice(caras[i + 1]), getVertice(caras[i + 2]));
            normales_caras[i] = normal.x;
            normales_caras[i + 1] = normal.y;
            normales_caras[i + 2] = normal.z;

            printf("P1: %f %f %f\n", getVertice(caras[i]).x, getVertice(caras[i]).y, getVertice(caras[i]).z);
            printf("P2 %f %f %f\n", getVertice(caras[i + 1]).x, getVertice(caras[i + 1]).y, getVertice(caras[i + 1]).z);
            printf("P3 %f %f %f\n", getVertice(caras[i + 2]).x, getVertice(caras[i + 2]).y, getVertice(caras[i + 2]).z);
            printf("Normal: %f %f %f\n", normal.x, normal.y, normal.z);
        }
        glNormalPointer(GL_FLOAT, 0, &normales_caras[0]);
    }
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);

    glDrawElements(GL_TRIANGLES, caras.size(), GL_UNSIGNED_INT, &caras[0]);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glShadeModel(GL_FLAT);
}