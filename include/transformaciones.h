#ifndef TRANSFORMACIONES_H
#define TRANSFORMACIONES_H

#include "objeto3D.h"
#include <GL/glut.h>
#include <trigonometria.h>


class Transformacion : public Objeto3D{
public:
    virtual void draw() = 0;
};

class Rotacion : public Transformacion{
private:
    Vector3D eje;
    float angulo;
public:
    Rotacion();
    Rotacion(const Rotacion &rotacion);
    Rotacion(const Vector3D &eje, float angulo);
    void set(const Vector3D &eje, float angulo);
    void setEje(const Vector3D &eje);
    void setAngulo(float angulo);
    Vector3D getEje();
    float getAngulo();
    virtual void draw();
};

class Traslacion : public Transformacion{
private:
    Vector3D vector_traslacion;
public:
    Traslacion();
    Traslacion(const Traslacion &traslacion);
    Traslacion(const Vector3D &vector_traslacion);
    void set(const Vector3D &vector_traslacion);
    Vector3D getVectorTraslacion();
    virtual void draw();
};

class Escalado : public Transformacion{
private:
    Vector3D vector_escalado;
    
public:
    Escalado();
    Escalado(const Vector3D &vector_escalado);
    void set(const Vector3D &vector_escalado);
    Vector3D getVectorEscalado();
    virtual void draw();
};

#endif