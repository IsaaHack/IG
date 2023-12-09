#include "geometria.h"

void Geometria::cargarTextura(const char *nombre_archivo_jpg){
    unsigned width, height;
    width = height = 0;

    unsigned char *data = LeerArchivoJPEG(nombre_archivo_jpg, width, height);

    if(data != NULL){
        malla.asignarTextura(data, width, height);
    }
}

void Geometria::draw(){
    material.draw();
    malla.draw();
}

void Geometria::drawFlat(bool draw_normales){
    material.draw();
    malla.drawFlat(draw_normales);
}

void Geometria::drawSmooth(bool draw_normales){
    material.draw();
    malla.drawSmooth(draw_normales);
}

void Geometria::draw(bool draw_normales){
    material.draw();
    malla.draw(draw_normales);
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