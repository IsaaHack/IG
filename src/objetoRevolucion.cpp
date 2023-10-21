#include "objetoRevolucion.h"
#include <iostream>

void ObjetoRevolucion::calcularVertices(const vector<float> &perfil){
    float dif_angular = 2 * M_PI / this->precision;
    for(int i = 0; i < perfil.size(); i += 3){
        for(int j = 0; j < this->precision; j++){
            float angulo = j * dif_angular;
            float x = perfil[i] * cos(angulo) + perfil[i + 2] * sin(angulo);
            float y = perfil[i + 1];
            float z = -perfil[i] * sin(angulo) + perfil[i + 2] * cos(angulo);

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }
}

void ObjetoRevolucion::calcularTriangulos(bool tapa_superior, bool tapa_inferior)
{
    for(int punto_inicial_capa = 0; punto_inicial_capa < vertices.size()-(precision*3); punto_inicial_capa += precision*3){//punto_inicial_capa es el primer punto de la capa actual
        for(int punto_capa = 0; punto_capa < precision; punto_capa++){//Indice dentro de una capa del punto
            int p1 = punto_inicial_capa/3 + punto_capa;
            int p2 = punto_inicial_capa/3 + (punto_capa + 1) % precision;
            int p3 = punto_inicial_capa/3 + (punto_capa + 1) % precision + precision;
            int p4 = punto_inicial_capa/3 + punto_capa + precision;

            caras.push_back(p1);
            caras.push_back(p2);
            caras.push_back(p3);

            caras.push_back(p1);
            caras.push_back(p3);
            caras.push_back(p4);
        }
    }

    if(tapa_superior){
        float y = getVertice(0).y;
        for(int i = 0; i < precision; i++){
            vertices.push_back(0);
            vertices.push_back(y);
            vertices.push_back(0);
            caras.push_back(i);
            caras.push_back(vertices.size() / 3 - 1);
            caras.push_back(((i + 1) % precision));
        }
    }

    if(tapa_inferior){
        int primer_punto_ultima_capa = (num_vertices_perfil - 1) * precision;
        float y = getVertice(primer_punto_ultima_capa).y;
        
        for(int i = 0; i < precision; i++){
            vertices.push_back(0);
            vertices.push_back(y);
            vertices.push_back(0);
            caras.push_back(primer_punto_ultima_capa + ((i + 1) % precision));
            caras.push_back(vertices.size() / 3 - 1);
            caras.push_back(primer_punto_ultima_capa + i);
        }
    }
}

ObjetoRevolucion::ObjetoRevolucion()
{
    modo_sombreado = GL_SMOOTH;
    precision = 3;
}

void ObjetoRevolucion::cargar(const char *nombre_archivo_ply){
    cargar(nombre_archivo_ply, 50, true);
}

void ObjetoRevolucion::cargar(const char *nombre_archivo_ply, int precision, bool tapa_superior, bool tapa_inferior){
    vector<float> perfil;
    ply::read_vertices(nombre_archivo_ply, perfil);

    num_vertices_perfil = perfil.size() / 3;

    if(precision >= 3 && precision < 100)
        this->precision = precision;
    else if(precision >= 100)
        this->precision = 100;
    
    calcularVertices(perfil);
    calcularTriangulos(tapa_superior, tapa_inferior);
    Malla::calcularNormalesVertices();
}

void ObjetoRevolucion::draw()
{
    this->Malla::draw();
}

void ObjetoRevolucion::draw(bool draw_normales)
{
    this->Malla::draw(draw_normales);
}
