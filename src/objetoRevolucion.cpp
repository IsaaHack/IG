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

    // Añadir el perfil al final para la costura
    for(int i = 0; i < perfil.size(); i += 3){
        malla.vertices.push_back(perfil[i]);
        malla.vertices.push_back(perfil[i + 1]);
        malla.vertices.push_back(perfil[i + 2]);
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
        int p2_2 = num_vertices_perfil * precision + i;
        int p3 = primer_punto_capa_siguiente;
        int p3_2 = num_vertices_perfil * precision + i + 1;
        int p4 = primer_punto_capa_siguiente + precision - 1;

        //costura
        malla.caras.push_back(p1);
        malla.caras.push_back(p2_2);
        malla.caras.push_back(p3_2);

        malla.caras.push_back(p1);
        malla.caras.push_back(p3_2);
        malla.caras.push_back(p4);

        
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

vector<float> ObjetoRevolucion::obtenerPerfil()
{
    vector<float> perfil;

    for(int i = 0; i < num_vertices_perfil; i ++){
        perfil.push_back(malla.vertices[i*3*precision]);
        perfil.push_back(malla.vertices[i*3*precision + 1]);
        perfil.push_back(malla.vertices[i*3*precision + 2]);
    }

    return perfil;
}

void ObjetoRevolucion::calcularCoordenadasTextura(const vector<float> &perfil)
{
    vector<float> distancias;

    float distancia_total = 0;
    float delta_x = 1.0 / precision;

    Vector3D v1, v2;

    for(int i = 0; i < perfil.size() - 3; i += 3){
        v1 = Vector3D(perfil[i], perfil[i + 1], perfil[i + 2]);
        v2 = Vector3D(perfil[i + 3], perfil[i + 4], perfil[i + 5]);

        float distancia = (v2 - v1).mod();

        distancia_total += distancia;
        distancias.push_back(distancia);
    }

    float x = 0;
    float y = 1;

    int d = 0;

    for(int i = 0; i < num_vertices_perfil*precision*3; i += 3*precision){
        x = 0;

        for(int j = 0; j < precision; j++){
            malla.setCoodenadasTextura(i/3 + j, x, y);
            x += delta_x;
            x = x > 1 ? 1 : x; // Para evitar errores de precisión
        }

        y -= distancias[d] / distancia_total;

        d++;

        y = y < 0 ? 0 : y; // Para evitar errores de precisión
    }

    //costura
    y = 1;
    for(int i = 0; i < num_vertices_perfil; i ++){
        malla.setCoodenadasTextura(num_vertices_perfil*precision + i, 1, y);
        y += distancias[i] / distancia_total;

        y = y < 0 ? 0 : y; // Para evitar errores de precisión
    }

}

void ObjetoRevolucion::calcularCoordenadasTexturaTapas(int modo)
{
    float inicio = 0;

    if(modo == 0) inicio = 0;
    else if(modo == 1) inicio = 0.5;
    else return;

    float radio = 0;

    vector<float> perfil = obtenerPerfil();

    for(int i = 0; i < perfil.size(); i += 3){
        Vector3D v(perfil[i], perfil[i + 1], perfil[i + 2]);
        Vector3D centro(0, v.y, 0);

        radio = max((v - centro).mod(), radio);
    }

    float d_x = 0;
    float d_z = 0;

    for(int i = 0; i < malla.vertices.size()/3; i++){
        Vector3D v(malla.vertices[i*3], malla.vertices[i*3 + 1], malla.vertices[i*3 + 2]);
        Vector3D centro(0, v.y, 0);

        d_x = 0.25*(v.x - centro.x)/radio;
        d_z = 0.5*(v.z - centro.z)/radio;

        d_x += inicio + 0.25;
        d_z += 0.5;

        malla.setCoodenadasTextura(i, d_x, d_z);
    }
}

ObjetoRevolucion::ObjetoRevolucion()
{
    setModoSombreado(GL_SMOOTH);
    precision = MIN_PRECISION;
    num_vertices_perfil = 0;
    tapa_superior = NULL;
    tapa_inferior = NULL;
}

ObjetoRevolucion::~ObjetoRevolucion()
{
    if(tapa_superior != NULL) delete tapa_superior;
    if(tapa_inferior != NULL) delete tapa_inferior;
}

void ObjetoRevolucion::cargar(const char *nombre_archivo_ply){
    cargar(nombre_archivo_ply, 100, true, true);
}

void ObjetoRevolucion::cargar(const char *nombre_archivo_ply, int precision, bool tapa_superior, bool tapa_inferior){
    Geometria::clear();
    vector<float> perfil;
    ply::read_vertices(nombre_archivo_ply, perfil);

    num_vertices_perfil = perfil.size() / 3;

    if(precision >= MIN_PRECISION && precision < MAX_PRECISION)
        this->precision = precision;
    else if(precision >= MAX_PRECISION)
        this->precision = MAX_PRECISION;


    verificarPerfil(perfil);
    calcularVertices(perfil);
    calcularTriangulos(tapa_superior, tapa_inferior);
    malla.calcularNormalesVertices();

    int n = num_vertices_perfil * this->precision;
    //Asignar normales a los puntos de la costura
    for(int i = 0; i < num_vertices_perfil; i++){
        malla.setNormal(n + i, malla.getNormal(i*this->precision));
    }
}

void ObjetoRevolucion::cargarTextura(const char *nombre_archivo_jpg)
{
    Geometria::cargarTextura(nombre_archivo_jpg);
    
    vector<float> perfil = obtenerPerfil();

    calcularCoordenadasTextura(perfil);
}

void ObjetoRevolucion::escalarVertices(float factor_x, float factor_y, float factor_z)
{
    Geometria::escalarVertices(factor_x, factor_y, factor_z);
    if(tapa_superior != NULL) tapa_superior->escalarVertices(factor_x, factor_y, factor_z);
    if(tapa_inferior != NULL) tapa_inferior->escalarVertices(factor_x, factor_y, factor_z);
}

void ObjetoRevolucion::setMaterialTapas(const Material &material)
{
    if(tapa_superior != NULL) tapa_superior->setMaterial(material);
    if(tapa_inferior != NULL) tapa_inferior->setMaterial(material);
}

void ObjetoRevolucion::cargarTapaSuperior(const char *nombre_archivo_ply)
{
    tapa_superior = new ObjetoRevolucion();
    tapa_superior->setMaterial(this->material);
    tapa_superior->cargar(nombre_archivo_ply, precision, false, false);
}

void ObjetoRevolucion::cargarTapaInferior(const char *nombre_archivo_ply)
{
    tapa_inferior = new ObjetoRevolucion();
    tapa_inferior->setMaterial(this->material);
    tapa_inferior->cargar(nombre_archivo_ply, precision, false, false);
}

void ObjetoRevolucion::cargarTexturaTapas(const char *nombre_archivo_jpg)
{
    if(tapa_superior != NULL){
        tapa_superior->Geometria::cargarTextura(nombre_archivo_jpg);
        tapa_superior->calcularCoordenadasTexturaTapas(0);
        if(tapa_inferior != NULL)
            tapa_inferior->malla.id_textura = tapa_superior->malla.id_textura;
            tapa_inferior->malla.coordenadas_textura.resize(tapa_superior->malla.coordenadas_textura.size(), 0);
            tapa_inferior->calcularCoordenadasTexturaTapas(1);
    }else{
        if(tapa_inferior != NULL){
            tapa_inferior->Geometria::cargarTextura(nombre_archivo_jpg);
            tapa_inferior->calcularCoordenadasTexturaTapas(1);
        }
    }
}

void ObjetoRevolucion::draw()
{
    this->Geometria::draw();
    if(tapa_superior != NULL) tapa_superior->draw();
    if(tapa_inferior != NULL) tapa_inferior->draw();
}

void ObjetoRevolucion::draw(bool draw_normales)
{
    this->Geometria::draw(draw_normales);
    if(tapa_superior != NULL) tapa_superior->draw(draw_normales);
    if(tapa_inferior != NULL) tapa_inferior->draw(draw_normales);
}
