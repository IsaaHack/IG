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

}

void BarridoLineal::calcularVertices(const vector<float> &objeto, const Vector3D &normal_objeto)
{
    vector<Vector3D> vectores_trayectoria = calcularVectoresTrayectoria(trayectoria);

    Vector3D normal = normal_objeto;

    MatrizRotacion m(normal, vectores_trayectoria[0]);
    for(int i = 0; i < objeto.size(); i += 3){
        Punto3D p = Punto3D(objeto[i], objeto[i + 1], objeto[i + 2]);
        p = m * p;
        malla.vertices.push_back(p.x);
        malla.vertices.push_back(p.y);
        malla.vertices.push_back(p.z);
    }

    normal = vectores_trayectoria[0];
    Vector3D v(trayectoria[0], trayectoria[1]);

    for(int i = 1; i < vectores_trayectoria.size(); i++){
        Vector3D dir = vectores_trayectoria[i];
        m.set(normal, dir);

        for(int j = 0; j < objeto.size(); j += 3){
            Punto3D p = Punto3D(malla.getVertice(num_vertices_objeto*(i-1) + j/3));
            
            p.x += v.x;
            p.y += v.y;
            p.z += v.z;

            p = m * p;
            
            malla.vertices.push_back(p.x);
            malla.vertices.push_back(p.y);
            malla.vertices.push_back(p.z);
        }

        v = Vector3D(trayectoria[i-1], trayectoria[i]);

        normal = dir;
    }

    for(int i = 0; i < objeto.size(); i += 3){
        Punto3D p = Punto3D(malla.getVertice(num_vertices_objeto*(num_vertices_trayectoria-2) + i/3));
        p.x += v.x;
        p.y += v.y;
        p.z += v.z;
        malla.vertices.push_back(p.x);
        malla.vertices.push_back(p.y);
        malla.vertices.push_back(p.z);
    }

    malla.vertices.push_back(trayectoria[0].x);
    malla.vertices.push_back(trayectoria[0].y);
    malla.vertices.push_back(trayectoria[0].z);
    malla.vertices.push_back(trayectoria[num_vertices_trayectoria - 1].x);
    malla.vertices.push_back(trayectoria[num_vertices_trayectoria - 1].y);
    malla.vertices.push_back(trayectoria[num_vertices_trayectoria - 1].z);

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

            malla.caras.push_back(p1);
            malla.caras.push_back(p2);
            malla.caras.push_back(p3);

            malla.caras.push_back(p1);
            malla.caras.push_back(p3);
            malla.caras.push_back(p4);
        }

        int p1 = primer_punto_capa_actual + num_vertices_objeto - 1;
        int p2 = primer_punto_capa_actual;
        int p3 = primer_punto_capa_siguiente;
        int p4 = primer_punto_capa_siguiente + num_vertices_objeto - 1;

        malla.caras.push_back(p1);
        malla.caras.push_back(p2);
        malla.caras.push_back(p3);

        malla.caras.push_back(p1);
        malla.caras.push_back(p3);
        malla.caras.push_back(p4);
    }

    int punto_centro_inf = malla.vertices.size() / 3 - 2;
    int punto_centro_sup = malla.vertices.size() / 3 - 1;

    if(malla.getVertice(punto_centro_inf) != malla.getVertice(punto_centro_sup)){
        for(int i = 0; i < num_vertices_objeto; i++){
            int p1 = i;
            int p2 = punto_centro_inf;
            int p3 = (i + 1)%num_vertices_objeto;
            

            malla.caras.push_back(p1);
            malla.caras.push_back(p2);
            malla.caras.push_back(p3);
        }


        for(int i = 0; i < num_vertices_objeto; i++){
            int p1 = i+(num_vertices_trayectoria-1)*num_vertices_objeto;
            int p2 = (i+1)%num_vertices_objeto+(num_vertices_trayectoria-1)*num_vertices_objeto;
            int p3 = punto_centro_sup;

            malla.caras.push_back(p1);
            malla.caras.push_back(p2);
            malla.caras.push_back(p3);
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
    this->num_vertices_trayectoria = this->trayectoria.size();

    calcularVertices(objeto, normal);
    calcularTriangulos();
    malla.calcularNormalesVertices();
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
            
            p.x += v.x;
            p.y += v.y;
            p.z += v.z;

            p = m * p;
            
            malla.vertices.push_back(p.x);
            malla.vertices.push_back(p.y);
            malla.vertices.push_back(p.z);

            objeto[j] = p.x;
            objeto[j + 1] = p.y;
            objeto[j + 2] = p.z;
        }

        centro = calcularCentro(objeto);
        this->trayectoria.push_back(centro);
        normal = obtenerNormalObjeto(objeto);
        normal = dir;
        v = Vector3D(trayectoria[i], trayectoria[i + 1]);
    }

    num_vertices_trayectoria = this->trayectoria.size();

    malla.vertices.push_back(this->trayectoria[0].x);
    malla.vertices.push_back(this->trayectoria[0].y);
    malla.vertices.push_back(this->trayectoria[0].z);
    malla.vertices.push_back(this->trayectoria[num_vertices_trayectoria - 1].x);
    malla.vertices.push_back(this->trayectoria[num_vertices_trayectoria - 1].y);
    malla.vertices.push_back(this->trayectoria[num_vertices_trayectoria - 1].z);

    calcularTriangulos();
    malla.calcularNormalesVertices();
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
    malla.calcularNormalesVertices();
}

void BarridoLineal::cargar(const vector<Punto3D> objeto, const Vector3D &vector_trayectoria, int num_instancias)
{
    this->num_vertices_objeto = objeto.size();

    vector<float> objeto_floats;
    for(int i = 0; i < objeto.size(); i++){
        objeto_floats.push_back(objeto[i].x);
        objeto_floats.push_back(objeto[i].y);
        objeto_floats.push_back(objeto[i].z);
    }

    Punto3D centro = calcularCentro(objeto_floats);
    Vector3D normal = obtenerNormal(objeto[0], objeto[1], objeto[2]);

    MatrizRotacion m(normal, vector_trayectoria);

    centro = m * centro;

    calcularTrayectoria(vector_trayectoria, centro, num_instancias);

    this->num_vertices_trayectoria = trayectoria.size();

    calcularVertices(objeto_floats, normal);
    calcularTriangulos();
    malla.calcularNormalesVertices();
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
        for(int i = 0; i < malla.vertices.size(); i += 3){
            glVertex3f(malla.vertices[i], malla.vertices[i + 1], malla.vertices[i + 2]);
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
    
    
    malla.drawFlat(true);
}
