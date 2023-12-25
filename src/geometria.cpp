#include "geometria.h"
#include "gestorIdGeometria.h"

Geometria::Geometria(){
    GestorIdGeometria::getInstancia()->addGeometria(this);
    material = Material();
    punto_pivote = Punto3D();

    unsigned unsigned_id = GestorIdGeometria::getInstancia()->getID(this);

    printf("ID: %d\n", unsigned_id);
}

Geometria::~Geometria(){
    GestorIdGeometria::getInstancia()->borraGeometria(this);
}

void Geometria::cargarTextura(const char *nombre_archivo_jpg){
    unsigned width, height;
    width = height = 0;

    unsigned char *data = LeerArchivoJPEG(nombre_archivo_jpg, width, height);

    if(data != NULL){
        malla.asignarTextura(data, width, height);
    }
}

void Geometria::draw(){
    GLuint id_textura = malla.id_textura;

    if(GestorIdGeometria::getInstancia()->getModo() == MODO_NORMAL)
        material.draw();
    else{
        unsigned unsigned_id = GestorIdGeometria::getInstancia()->getID(this);

        unsigned char id1 = (unsigned char)unsigned_id;
        unsigned char id2 = (unsigned char)(unsigned_id >> 8);
        unsigned char id3 = (unsigned char)(unsigned_id >> 16);

        glColor3b(id1, id2, id3);

        malla.id_textura = 0;
    }
    
    malla.draw();

    malla.id_textura = id_textura;
}

void Geometria::drawFlat(bool draw_normales){
    GLuint id_textura = malla.id_textura;

    if(GestorIdGeometria::getInstancia()->getModo() == MODO_NORMAL)
        material.draw();
    else{
        unsigned unsigned_id = GestorIdGeometria::getInstancia()->getID(this);

        glColor3bv((GLbyte*)&unsigned_id);

        malla.id_textura = 0;
    }

    malla.drawFlat(draw_normales);

    malla.id_textura = id_textura;
}

void Geometria::drawSmooth(bool draw_normales){
    GLuint id_textura = malla.id_textura;

    if(GestorIdGeometria::getInstancia()->getModo() == MODO_NORMAL)
        material.draw();
    else{
        unsigned unsigned_id = GestorIdGeometria::getInstancia()->getID(this);

        glColor3bv((GLbyte*)&unsigned_id);

        malla.id_textura = 0;
    }

    malla.drawSmooth(draw_normales);

    malla.id_textura = id_textura;
}

void Geometria::draw(bool draw_normales){
    GLuint id_textura = malla.id_textura;

    if(GestorIdGeometria::getInstancia()->getModo() == MODO_NORMAL)
        material.draw();
    else{
        unsigned unsigned_id = GestorIdGeometria::getInstancia()->getID(this);

        glColor3bv((GLbyte*)&unsigned_id);

        malla.id_textura = 0;
    }

    malla.draw(draw_normales);

    malla.id_textura = id_textura;
}

void Geometria::clear(){
    malla.clear();
}

void Geometria::setModoSombreado(int modo){
    malla.setModoSombreado(modo);
}

void Geometria::setMaterial(const Material &material){
    this->material = material;
}

Material Geometria::getMaterial() const{
    return material;
}

void Geometria::setPuntoPivote(const Punto3D &punto_pivote)
{
    this->punto_pivote = punto_pivote;
}

Punto3D Geometria::getPuntoPivote() const
{
    return punto_pivote;
}

void Geometria::calcularPuntoPivote(){
    Punto3D min, max;
    min.x = min.y = min.z = 1000000;
    max.x = max.y = max.z = -1000000;

    for(int i = 0; i < malla.vertices.size(); i += 3){
        if(malla.vertices[i] < min.x) min.x = malla.vertices[i];
        if(malla.vertices[i] > max.x) max.x = malla.vertices[i];
        if(malla.vertices[i + 1] < min.y) min.y = malla.vertices[i + 1];
        if(malla.vertices[i + 1] > max.y) max.y = malla.vertices[i + 1];
        if(malla.vertices[i + 2] < min.z) min.z = malla.vertices[i + 2];
        if(malla.vertices[i + 2] > max.z) max.z = malla.vertices[i + 2];
    }

    punto_pivote.x = (min.x + max.x) / 2;
    punto_pivote.y = (min.y + max.y) / 2;
    punto_pivote.z = (min.z + max.z) / 2;
}

void Geometria::escalarVertices(float factor_x, float factor_y, float factor_z){
    malla.escalarVertices(factor_x, factor_y, factor_z);
    punto_pivote.x *= factor_x;
    punto_pivote.y *= factor_y;
    punto_pivote.z *= factor_z;
}