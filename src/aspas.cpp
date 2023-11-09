#include "aspas.h"

Aspas::Aspas()
{
    cubo = Cubo(1);

    a.addEscalado(Vector3D(2, 10, 2));
    a.addObjeto(&cubo);


    b.addEscalado(Vector3D(2, 6, 2));
    b.addObjeto(&cubo);

    c.addEscalado(Vector3D(1, 6, 1));
    c.addObjeto(&cubo);

    d = c;

    b_.addTransladacion(Vector3D(-3, 1, -1));
    b_.addRotacion(Vector3D(0, 0, 1), -90);
    b_.addNodo(&b);

    aspas.addRotacion(Vector3D(0, 1, 0), -20);
    aspas.addNodo(&aspa);
    aspas.addRotacion(Vector3D(0, 1, 0), 40);
    aspas.addTransladacion(Vector3D(0, -6, 0));
    aspas.addNodo(&aspa);

    aspa.addRotacion(Vector3D(0, 1, 0), 90);
    aspa.addTransladacion(Vector3D(-0.5, 0, -1));
    aspa.addNodo(&c);

    giro_x = nullptr;
    giro_y = nullptr;
}

Aspas::Aspas(float *giro_x, float *giro_y)
{
    cubo = Cubo(1);

    a.addEscalado(Vector3D(2, 10, 2));
    a.addObjeto(&cubo);


    b.addEscalado(Vector3D(2, 6, 2));
    b.addObjeto(&cubo);

    c.addEscalado(Vector3D(1, 6, 1));
    c.addObjeto(&cubo);

    d = c;

    b_.addTransladacion(Vector3D(-3, 1, -1));
    b_.addRotacion(Vector3D(0, 0, 1), -90);
    b_.addNodo(&b);

    aspas.addRotacion(Vector3D(0, 1, 0), -20);
    aspas.addNodo(&aspa);
    aspas.addRotacion(Vector3D(0, 1, 0), 40);
    aspas.addTransladacion(Vector3D(0, -6, 0));
    aspas.addNodo(&aspa);

    aspa.addRotacion(Vector3D(0, 1, 0), 90);
    aspa.addTransladacion(Vector3D(-0.5, 0, -1));
    aspa.addNodo(&c);

    this->giro_x = giro_x;
    this->giro_y = giro_y;
}

void Aspas::arbolTransformaciones()
{
    raiz.clear();
    raiz.addObjeto(&a);
    raiz.addTransladacion(Vector3D(1, 11, 1));
    raiz.addRotacion(Vector3D(0, 1, 0), *giro_y);
    raiz.addNodo(&cabeza);

    cabeza.clear();
    cabeza.addNodo(&b_);
    cabeza.addTransladacion(Vector3D(3.5, 0, 0));
    cabeza.addRotacion(Vector3D(1, 0, 0), *giro_x);
    cabeza.addNodo(&aspas);
}

void Aspas::draw()
{
    arbolTransformaciones();
    raiz.aplicar();
}


