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

            malla.vertices.push_back(x);
            malla.vertices.push_back(y);
            malla.vertices.push_back(z);
        }
    }
}

void ObjetoRevolucion::calcularTriangulos(bool tapa_superior, bool tapa_inferior)
{
    for(int i = 0; i < num_vertices_perfil - 1; i++){
        int primer_punto_capa_actual = i * precision;
        int primer_punto_capa_siguiente = primer_punto_capa_actual + precision;

        for(int j = 0; j < precision - 1; j++){
            int p1 = primer_punto_capa_actual + j;
            int p2 = primer_punto_capa_actual + j + 1;
            int p3 = primer_punto_capa_siguiente + j + 1;
            int p4 = primer_punto_capa_siguiente + j;

            malla.caras.push_back(p1);
            malla.caras.push_back(p2);
            malla.caras.push_back(p3);

            malla.caras.push_back(p1);
            malla.caras.push_back(p3);
            malla.caras.push_back(p4);
        }

        int p1 = primer_punto_capa_actual + precision - 1;
        int p2 = primer_punto_capa_actual;
        int p3 = primer_punto_capa_siguiente;
        int p4 = primer_punto_capa_siguiente + precision - 1;

        malla.caras.push_back(p1);
        malla.caras.push_back(p2);
        malla.caras.push_back(p3);

        malla.caras.push_back(p1);
        malla.caras.push_back(p3);
        malla.caras.push_back(p4);
    }

    if(tapa_superior && Punto3D(0, malla.getVertice(0).y, 0) != malla.getVertice(0)){
        float y = malla.getVertice(0).y;
        malla.vertices.push_back(0);
        malla.vertices.push_back(y);
        malla.vertices.push_back(0);

        for(int i = 0; i < precision; i++){
            malla.caras.push_back(i);
            malla.caras.push_back(malla.vertices.size() / 3 - 1);
            malla.caras.push_back(((i + 1) % precision));
        }
    }

    int primer_punto_ultima_capa = (num_vertices_perfil - 1) * precision;
    if(tapa_inferior && Punto3D(0, malla.getVertice(primer_punto_ultima_capa).y, 0) != malla.getVertice(primer_punto_ultima_capa)){
        float y = malla.getVertice(primer_punto_ultima_capa).y;
        malla.vertices.push_back(0);
        malla.vertices.push_back(y);
        malla.vertices.push_back(0);
        
        for(int i = 0; i < precision; i++){
            malla.caras.push_back(primer_punto_ultima_capa + ((i + 1) % precision));
            malla.caras.push_back(malla.vertices.size() / 3 - 1);
            malla.caras.push_back(primer_punto_ultima_capa + i);
        }
    }
}

void ObjetoRevolucion::verificarPerfil(vector<float> &perfil) const
{
    Vector3D dir_perfil;
    bool inicializado = false;
    for(int i = 0; i < perfil.size(); i += 3){
        Vector3D v(perfil[i], 0, perfil[i + 2]);

        if(!inicializado){
            if(v != Vector3D()){
                dir_perfil = v.obtenerNormalizado();
                inicializado = true;
            }
        }else if(dir_perfil != v.obtenerNormalizado()){
            v = dir_perfil * v.mod();
            perfil[i] = v.x;
            perfil[i + 2] = v.z;
        }
            
    }
}

ObjetoRevolucion::ObjetoRevolucion()
{
    setModoSombreado(GL_SMOOTH);
    precision = 3;
}

void ObjetoRevolucion::cargar(const char *nombre_archivo_ply){
    cargar(nombre_archivo_ply, 100, true, true);
}

void ObjetoRevolucion::cargar(const char *nombre_archivo_ply, int precision, bool tapa_superior, bool tapa_inferior){
    Geometria::clear();
    vector<float> perfil;
    ply::read_vertices(nombre_archivo_ply, perfil);

    num_vertices_perfil = perfil.size() / 3;

    if(precision >= 3 && precision < 100)
        this->precision = precision;
    else if(precision >= 100)
        this->precision = 100;


    verificarPerfil(perfil);
    calcularVertices(perfil);
    calcularTriangulos(tapa_superior, tapa_inferior);
    malla.calcularNormalesVertices();
}

void ObjetoRevolucion::draw()
{
    this->Geometria::draw();
}

void ObjetoRevolucion::draw(bool draw_normales)
{
    this->Geometria::draw(draw_normales);
}
