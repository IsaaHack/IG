#ifndef TRASNFORMACIONES_H
#define TRASNFORMACIONES_H

#include <GL/glut.h>
#include <geometria3D.h>

class Trasformacion{
public:
    virtual void aplicar() = 0;
};

class Rotacion : public Trasformacion{
private:
    static Rotacion* instancia;

    Vector3D eje;
    float angulo;

    Rotacion();
    ~Rotacion();
    
public:
    static Rotacion* getInstancia();
    void aplicar();
    void set(const Vector3D &eje, float angulo);
    void setEje(const Vector3D &eje);
    void setAngulo(float angulo);
    Vector3D getEje();
    float getAngulo();
};

class Traslacion : public Trasformacion{
private:
    static Traslacion* instancia;

    Vector3D vector_traslacion;

    Traslacion();
    ~Traslacion();
public:
    static Traslacion* getInstancia();
    void aplicar();
    void set(const Vector3D &vector_traslacion);
    Vector3D getVectorTraslacion();
};

class Escalado : public Trasformacion{
private:
    static Escalado *instancia;

    Vector3D vector_escalado;

    Escalado();
    ~Escalado();
public:
    static Escalado *getInstancia();
    void aplicar();
    void set(const Vector3D &vector_escalado);
    Vector3D getVectorEscalado();
};

#endif