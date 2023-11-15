#include "aspas.h"
#include <iostream>

Rotacion Aspas::r1 = Rotacion(ejez, -90);
Rotacion Aspas::r2 = Rotacion(ejey, -20);
Rotacion Aspas::r3 = Rotacion(ejey, 40);
Rotacion Aspas::r4 = Rotacion(ejey, 90);

Traslacion Aspas::t1 = Traslacion(Vector3D(1, 11, 1));
Traslacion Aspas::t2 = Traslacion(Vector3D(3.5, 0, 0));
Traslacion Aspas::t3 = Traslacion(Vector3D(-3, 0, -1));
Traslacion Aspas::t4 = Traslacion(Vector3D(0, -6, 0));
Traslacion Aspas::t5 = Traslacion(Vector3D(-0.5, 0, -1));

Escalado Aspas::s_a = Escalado(Vector3D(2, 10, 2));
Escalado Aspas::s_b = Escalado(Vector3D(2, 6, 2));
Escalado Aspas::s_c = Escalado(Vector3D(2, 6, 1));

Aspas::Aspas()
{
    cubo = Cubo(1);

    giro_x = nullptr;
    giro_y = nullptr;
}

Aspas::Aspas(float *giro_x, float *giro_y)
{
    cubo = Cubo(1);

    rx.set(ejex, *giro_x);
    ry.set(ejey, *giro_y);

    a.addHijo(&s_a);
    a.addHijo(&cubo);

    b.addHijo(&s_b);
    b.addHijo(&cubo);

    c.addHijo(&s_c);
    c.addHijo(&cubo);
    
    molino.addHijo(&a);
    molino.addHijo(&t1);
    molino.addHijo(&ry);
    molino.addHijo(&cabeza);
    
    cabeza.addHijo(&b_);
    cabeza.addHijo(&t2);
    cabeza.addHijo(&rx);
    cabeza.addHijo(&aspas);

    b_.addHijo(&t3);
    b_.addHijo(&r1);
    b_.addHijo(&b);

    aspas.addHijo(&r2);
    aspas.addHijo(&aspa);
    aspas.addHijo(&r3);
    aspas.addHijo(&t4);
    aspas.addHijo(&aspa);

    aspa.addHijo(&r4);
    aspa.addHijo(&t5);
    aspa.addHijo(&c);

    this->giro_x = giro_x;
    this->giro_y = giro_y;
}

void Aspas::actualizar()
{
    if (giro_x != nullptr)
    {
        rx.set(ejex, *giro_x);
    }
    if (giro_y != nullptr)
    {
        ry.set(ejey, *giro_y);
    }
}

void Aspas::draw()
{
    actualizar();
    molino.draw();
}


