#include "luz.h"

bool Luz::luces[MAX_LUCES] = {false, false, false, false, false, false, false, false};

Luz::Luz(){
    id = 0;

    for (int i = 0; i < MAX_LUCES; i++){
        if (!luces[i]){
            id = GL_LIGHT0 + i;
            luces[i] = true;
            activar();
            porDefecto();
            break;
        }
    }

    if (id == 0)
        throw std::invalid_argument("No se pueden crear más luces");
};

Luz::Luz(GLenum id){
    if(id < GL_LIGHT0 || id > GL_LIGHT7)
        throw std::invalid_argument("El identificador de la luz debe estar entre GL_LIGHT0 y GL_LIGHT7");
    
    if(luces[id - GL_LIGHT0])
        throw std::invalid_argument("La luz ya existe");

    this->id = id;
    luces[id - GL_LIGHT0] = true;
    activar();
    porDefecto();
};

Luz::~Luz(){
    luces[id - GL_LIGHT0] = false;
};

void Luz::setPosicion(GLfloat x, GLfloat y, GLfloat z){
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    pos[3] = 0.0;
};

void Luz::setDireccion(GLfloat x, GLfloat y, GLfloat z){
    dir[0] = x;
    dir[1] = y;
    dir[2] = z;
    dir[3] = 0.0;
};

void Luz::setColorAmbiental(GLfloat r, GLfloat g, GLfloat b){
    color_ambiental[0] = r;
    color_ambiental[1] = g;
    color_ambiental[2] = b;
    color_ambiental[3] = 1.0;
};

void Luz::setColorDifuso(GLfloat r, GLfloat g, GLfloat b){
    color_difuso[0] = r;
    color_difuso[1] = g;
    color_difuso[2] = b;
    color_difuso[3] = 1.0;
};

void Luz::setColorEspecular(GLfloat r, GLfloat g, GLfloat b){
    color_especular[0] = r;
    color_especular[1] = g;
    color_especular[2] = b;
    color_especular[3] = 1.0;
};

void Luz::setCutoff(GLfloat cutoff){
    this->cutoff = cutoff;
};

void Luz::setExponent(GLfloat exponent){
    this->exponent = exponent;
};

void Luz::activar(){;
    glEnable(id);
    activada = true;
};

void Luz::desactivar(){
    glDisable(id);
    activada = false;
};

GLenum Luz::getId(){
    return id;
};

void Luz::draw(){
    glLightfv(id, GL_POSITION, pos);
    glLightfv(id, GL_SPOT_DIRECTION, dir);
    glLightfv(id, GL_AMBIENT, color_ambiental);
    glLightfv(id, GL_DIFFUSE, color_difuso);
    glLightfv(id, GL_SPECULAR, color_especular);
    glLightf(id, GL_SPOT_CUTOFF, cutoff);
    glLightf(id, GL_SPOT_EXPONENT, exponent);
};

void Luz::porDefecto(){
    setPosicion(0.0, 1.0, 0.0);
    setDireccion(0.0, 0.0, -1.0);
    setColorAmbiental(0.2, 0.2, 0.2);
    setColorDifuso(1.0, 1.0, 1.0);
    setColorEspecular(1.0, 1.0, 1.0);
    setCutoff(180.0);
    setExponent(0.0);
};

bool Luz::getActivada(){
    return activada;
};