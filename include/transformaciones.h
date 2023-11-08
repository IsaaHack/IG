#ifndef TRANSFORMACIONES_H
#define TRANSFORMACIONES_H

#include <GL/glut.h>
#include <geometria3D.h>
#include "modelo.h"

class Transformacion : public Objeto3D{
public:
    virtual void aplicar() = 0;
    virtual void draw() = 0;
};

class Rotacion : public Transformacion{
private:
    Vector3D eje;
    float angulo;
public:
    Rotacion();
    Rotacion(const Vector3D &eje, float angulo);
    void aplicar();
    void set(const Vector3D &eje, float angulo);
    void setEje(const Vector3D &eje);
    void setAngulo(float angulo);
    Vector3D getEje();
    float getAngulo();
    void draw(){};
};

class Traslacion : public Transformacion{
private:
    Vector3D vector_traslacion;
public:
    Traslacion();
    Traslacion(const Vector3D &vector_traslacion);
    void aplicar();
    void set(const Vector3D &vector_traslacion);
    Vector3D getVectorTraslacion();
    void draw(){};
};

class Escalado : public Transformacion{
private:
    Vector3D vector_escalado;
    
public:
    Escalado();
    Escalado(const Vector3D &vector_escalado);
    void aplicar();
    void set(const Vector3D &vector_escalado);
    Vector3D getVectorEscalado();
    void draw(){};
};

#endif