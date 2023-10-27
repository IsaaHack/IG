#include "barridoLineal.h"
#include "iostream"

Vector3D BarridoLineal::obtenerNormalObjeto(const vector<float> &objeto) const
{
    Punto3D p1(objeto[0], objeto[1], objeto[2]);
    Punto3D p2(objeto[3], objeto[4], objeto[5]);
    Punto3D p3(objeto[6], objeto[7], objeto[8]);

    return obtenerNormal(p1, p2, p3);
}

Punto3D BarridoLineal::calcularCentro(const vector<float> &objeto) const
{
    Punto3D centro;

    for(int i = 0; i < objeto.size(); i += 3){
        centro.x += objeto[i];
        centro.y += objeto[i + 1];
        centro.z += objeto[i + 2];
    }

    centro.x /= objeto.size() / 3;
    centro.y /= objeto.size() / 3;
    centro.z /= objeto.size() / 3;

    return centro;
}

vector<Vector3D> BarridoLineal::calcularVectoresTrayectoria(const vector<Punto3D> &trayectoria) const
{
    vector<Vector3D> vectores_trayectoria;

    for(int i = 0; i < trayectoria.size() - 1; i++){
        Vector3D v(trayectoria[i], trayectoria[i + 1]);
        v.normalizar();
        vectores_trayectoria.push_back(v);
    }

    return vectores_trayectoria;
}

vector<Vector3D> BarridoLineal::calcularVectoresTrayectoriaSinNormalizar(const vector<Punto3D> &trayectoria) const
{
    vector<Vector3D> vectores_trayectoria;

    for(int i = 0; i < trayectoria.size() - 1; i++){
        Vector3D v(trayectoria[i], trayectoria[i + 1]);
        vectores_trayectoria.push_back(v);
    }

    return vectores_trayectoria;
}

void BarridoLineal::calcularTrayectoria(const Vector3D &vector_trayectoria, const Punto3D &centro, int num_instancias)
{
    Punto3D p;

    for(int i = 0; i < num_instancias; i++){
        p.x = vector_trayectoria.x*i + centro.x;
        p.y = vector_trayectoria.y*i + centro.y;
        p.z = vector_trayectoria.z*i + centro.z;
        trayectoria.push_back(p);
    }
}

void BarridoLineal::calcularTrayectoria(const vector<Vector3D> &trayectoria, const Punto3D &centro)
{
    Punto3D p = centro;
    for(int i = 0; i < trayectoria.size(); i++){
        calcularTrayectoria(trayectoria[i], p, 1);
        p.x += trayectoria[i].x;
        p.y += trayectoria[i].y;
        p.z += trayectoria[i].z;
    }

    for(int i = 1; i < this->trayectoria.size(); i++){
        MatrizRotacion m(trayectoria[i-1], trayectoria[i]);
        this->trayectoria[i] = m * this->trayectoria[i];
    }
}

void BarridoLineal::calcularVertices(const vector<float> &objeto, const Vector3D &normal_objeto)
{
    vector<Vector3D> vectores_trayectoria = calcularVectoresTrayectoria(trayectoria);

    Vector3D normal = normal_objeto;

    MatrizRotacion m(normal, vectores_trayectoria[0]);
    for(int i = 0; i < objeto.size(); i += 3){
        Punto3D p = Punto3D(objeto[i], objeto[i + 1], objeto[i + 2]);
        p = m * p;
        vertices.push_back(p.x);
        vertices.push_back(p.y);
        vertices.push_back(p.z);
    }

    normal = vectores_trayectoria[0];

    Vector3D v(trayectoria[0], trayectoria[1]);
    //v.normalizar();
    for(int i = 1; i < vectores_trayectoria.size(); i++){
        Vector3D dir = vectores_trayectoria[i-1];
        MatrizRotacion m(normal, dir);

        for(int j = 0; j < objeto.size(); j += 3){
            Punto3D p = Punto3D(getVertice(num_vertices_objeto*(i-1) + j/3));
            p = m * p;
            p.x += v.x;
            p.y += v.y;
            p.z += v.z;
            
            vertices.push_back(p.x);
            vertices.push_back(p.y);
            vertices.push_back(p.z);

            printf("Vertice %d: (%f, %f, %f)\n", num_vertices_objeto*(i) + j/3, p.x, p.y, p.z);
        }

        v = Vector3D(trayectoria[i], trayectoria[i + 1]);

        normal = dir;
    }

    for(int i = 0; i < objeto.size(); i += 3){
        Punto3D p = Punto3D(getVertice(num_vertices_objeto*(num_vertices_trayectoria-2) + i/3));
        p.x += v.x;
        p.y += v.y;
        p.z += v.z;
        vertices.push_back(p.x);
        vertices.push_back(p.y);
        vertices.push_back(p.z);
    }

    

    vertices.push_back(trayectoria[0].x);
    vertices.push_back(trayectoria[0].y);
    vertices.push_back(trayectoria[0].z);
    vertices.push_back(trayectoria[num_vertices_trayectoria - 1].x);
    vertices.push_back(trayectoria[num_vertices_trayectoria - 1].y);
    vertices.push_back(trayectoria[num_vertices_trayectoria - 1].z);

}

void BarridoLineal::calcularTriangulos()
{
    for(int i = 0; i < num_vertices_trayectoria - 1; i++){
        int primer_punto_capa_actual = i * num_vertices_objeto;
        int primer_punto_capa_siguiente = primer_punto_capa_actual + num_vertices_objeto;

        for(int j = 0; j < num_vertices_objeto - 1; j++){
            int p1 = primer_punto_capa_actual + j;
            int p2 = primer_punto_capa_actual + j + 1;
            int p3 = primer_punto_capa_siguiente + j + 1;
            int p4 = primer_punto_capa_siguiente + j;

            caras.push_back(p1);
            caras.push_back(p2);
            caras.push_back(p3);

            caras.push_back(p1);
            caras.push_back(p3);
            caras.push_back(p4);
        }

        int p1 = primer_punto_capa_actual + num_vertices_objeto - 1;
        int p2 = primer_punto_capa_actual;
        int p3 = primer_punto_capa_siguiente;
        int p4 = primer_punto_capa_siguiente + num_vertices_objeto - 1;

        caras.push_back(p1);
        caras.push_back(p2);
        caras.push_back(p3);

        caras.push_back(p1);
        caras.push_back(p3);
        caras.push_back(p4);
    }

    int punto_centro_inf = vertices.size() / 3 - 2;
    int punto_centro_sup = vertices.size() / 3 - 1;

    if(getVertice(punto_centro_inf) != getVertice(punto_centro_sup)){
        for(int i = 0; i < num_vertices_objeto; i++){
            int p1 = i;
            int p2 = punto_centro_inf;
            int p3 = (i + 1)%num_vertices_objeto;
            

            caras.push_back(p1);
            caras.push_back(p2);
            caras.push_back(p3);
        }


        for(int i = 0; i < num_vertices_objeto; i++){
            int p1 = i+(num_vertices_trayectoria-1)*num_vertices_objeto;
            int p2 = (i+1)%num_vertices_objeto+(num_vertices_trayectoria-1)*num_vertices_objeto;
            int p3 = punto_centro_sup;

            caras.push_back(p1);
            caras.push_back(p2);
            caras.push_back(p3);
        }
    }
    

}

BarridoLineal::BarridoLineal()
{
    this->num_vertices_objeto = 0;
    this->num_vertices_trayectoria = 0;
}

void BarridoLineal::cargar(const char *nombre_archivo_ply)
{
    cargar(nombre_archivo_ply, Vector3D(0.0,1.0,0.0), 2);
}

void BarridoLineal::cargar(const char *nombre_archivo_ply, const vector<Punto3D> &trayectoria)
{
    vector<float> objeto;
    read_vertices(nombre_archivo_ply, objeto); 
    this->num_vertices_objeto = objeto.size() / 3;

    Punto3D centro = calcularCentro(objeto);
    Vector3D normal = obtenerNormalObjeto(objeto);

    Vector3D v(trayectoria[0], trayectoria[1]);
    v.normalizar();
    MatrizRotacion m(normal, v);

    centro = m * centro;

    calcularTrayectoria(calcularVectoresTrayectoria(trayectoria), centro);
    //this->trayectoria = trayectoria;
    this->num_vertices_trayectoria = trayectoria.size();

    calcularVertices(objeto, normal);
    calcularTriangulos();
    calcularNormalesVertices();
}

void BarridoLineal::cargarProbar(const char *nombre_archivo_ply, const vector<Punto3D> &trayectoria)
{
    vector<float> objeto;
    read_vertices(nombre_archivo_ply, objeto); 
    this->num_vertices_objeto = objeto.size() / 3;

    Punto3D centro = calcularCentro(objeto);
    Vector3D normal = obtenerNormalObjeto(objeto);

    vector<Vector3D> vectores_trayectoria = calcularVectoresTrayectoria(trayectoria);

    Vector3D v(0, 0, 0);

    for(int i = 0; i < vectores_trayectoria.size(); i++){
        Vector3D dir = vectores_trayectoria[i];
        MatrizRotacion m(normal, dir);
        centro = m * centro;

        for(int j = 0; j < objeto.size(); j += 3){
            Punto3D p = Punto3D(objeto[j], objeto[j + 1], objeto[j + 2]);
            p = m * p;
            p.x += v.x;
            p.y += v.y;
            p.z += v.z;
            vertices.push_back(p.x);
            vertices.push_back(p.y);
            vertices.push_back(p.z);

            objeto[j] = p.x;
            objeto[j + 1] = p.y;
            objeto[j + 2] = p.z;
        }

        centro = calcularCentro(objeto);
        this->trayectoria.push_back(centro);
        normal = dir;
        v = Vector3D(trayectoria[i], trayectoria[i + 1]);
    }

    num_vertices_trayectoria = this->trayectoria.size();

    vertices.push_back(this->trayectoria[0].x);
    vertices.push_back(this->trayectoria[0].y);
    vertices.push_back(this->trayectoria[0].z);
    vertices.push_back(this->trayectoria[num_vertices_trayectoria - 1].x);
    vertices.push_back(this->trayectoria[num_vertices_trayectoria - 1].y);
    vertices.push_back(this->trayectoria[num_vertices_trayectoria - 1].z);

    calcularTriangulos();
    calcularNormalesVertices();
}

void BarridoLineal::cargar(const char *nombre_archivo_ply, const Vector3D &vector_trayectoria, int num_instancias)
{
    vector<float> objeto;
    read_vertices(nombre_archivo_ply, objeto);
    this->num_vertices_objeto = objeto.size() / 3;

    Punto3D centro = calcularCentro(objeto);
    Vector3D normal = obtenerNormalObjeto(objeto);

    MatrizRotacion m(normal, vector_trayectoria);

    centro = m * centro;

    calcularTrayectoria(vector_trayectoria, centro, num_instancias);

    this->num_vertices_trayectoria = trayectoria.size();

    calcularVertices(objeto, normal);
    calcularTriangulos();
    calcularNormalesVertices();
}

void BarridoLineal::cargar(const char *nombre_archivo_ply, const char *nombre_archivo_trayectoria)
{
    vector<float> trayectoria;
    read_vertices(nombre_archivo_trayectoria, trayectoria);

    vector<Punto3D> trayectoria_vector;
    for(int i = 0; i < trayectoria.size(); i += 3){
        Punto3D v(trayectoria[i], trayectoria[i + 1], trayectoria[i + 2]);
        trayectoria_vector.push_back(v);
    }

    cargar(nombre_archivo_ply, trayectoria_vector);
}

void BarridoLineal::draw(){
    glBegin(GL_POINTS);
    {
        for(int i = 0; i < vertices.size(); i += 3){
            glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
        }
    }
    glEnd();

    glBegin(GL_LINES);
    {
        for(int i = 0; i < trayectoria.size() - 1; i += 1){
            glVertex3f(trayectoria[i].x, trayectoria[i].y, trayectoria[i].z);
            glVertex3f(trayectoria[i + 1].x, trayectoria[i + 1].y, trayectoria[i + 1].z);
        }
    }
    glEnd();
    
    
    Malla::drawFlat(true);
}
