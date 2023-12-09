#include "material.h"
#include "iostream"

Material::Material(){
    GLfloat colorAmbiente[4] = {1, 0.2, 0.4, 1.0};
    GLfloat colorDifuso[4] = {1, 0.2, 0.4, 1.0};
    GLfloat colorEspecular[4] = {0.0, 0.0, 0.0, 0.0};
    GLfloat exponenteBrillo = 100.0;
    GLfloat indiceRefraccion = 0.0;

    setColorAmbiental(colorAmbiente[0], colorAmbiente[1], colorAmbiente[2], colorAmbiente[3]);
    setColorDifuso(colorDifuso[0], colorDifuso[1], colorDifuso[2], colorDifuso[3]);
    setColorEspecular(colorEspecular[0], colorEspecular[1], colorEspecular[2], colorEspecular[3]);
    setExponenteBrillo(exponenteBrillo);
    setIndiceRefraccion(indiceRefraccion);
}

Material::Material(const GLfloat color_ambiental[4], const GLfloat color_difuso[4], const GLfloat color_especular[4], GLfloat exponente_brillo, GLfloat indice_refraccion){
    setColorAmbiental(color_ambiental[0], color_ambiental[1], color_ambiental[2], color_ambiental[3]);
    setColorDifuso(color_difuso[0], color_difuso[1], color_difuso[2], color_difuso[3]);
    setColorEspecular(color_especular[0], color_especular[1], color_especular[2], color_especular[3]);
    setExponenteBrillo(exponente_brillo);
    setIndiceRefraccion(indice_refraccion);
}

Material::Material(const Material &m){
    setColorAmbiental(m.color_ambiental[0], m.color_ambiental[1], m.color_ambiental[2], m.color_ambiental[3]);
    setColorDifuso(m.color_difuso[0], m.color_difuso[1], m.color_difuso[2], m.color_difuso[3]);
    setColorEspecular(m.color_especular[0], m.color_especular[1], m.color_especular[2], m.color_especular[3]);
    setExponenteBrillo(m.exponente_brillo);
    setIndiceRefraccion(m.indice_refraccion);
}

void Material::setColorAmbiental(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
    color_ambiental[0] = r;
    color_ambiental[1] = g;
    color_ambiental[2] = b;
    color_ambiental[3] = a;
}

void Material::setColorDifuso(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
    color_difuso[0] = r;
    color_difuso[1] = g;
    color_difuso[2] = b;
    color_difuso[3] = a;
}

void Material::setColorEspecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
    color_especular[0] = r;
    color_especular[1] = g;
    color_especular[2] = b;
    color_especular[3] = a;
}

void Material::setExponenteBrillo(GLfloat exponente_brillo){
    this->exponente_brillo = exponente_brillo;
}

void Material::setIndiceRefraccion(GLfloat indice_refraccion){
    this->indice_refraccion = indice_refraccion;
}

void Material::draw()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, color_ambiental);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color_difuso);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color_especular);
    glMaterialf(GL_FRONT, GL_SHININESS, exponente_brillo);
    glMaterialf(GL_FRONT, GL_INDEX, indice_refraccion);

}
