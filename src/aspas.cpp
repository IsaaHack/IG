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
    *this = Aspas(30, 100);
}

Aspas::Aspas(float velocidad_cabeza, float velocidad_aspas)
{
    cubo = Cubo(1);

    giro_x = 0;
    giro_y = 0;

    if(velocidad_cabeza < 0)
    {
        sentido = false;
        velocidad_cabeza = -velocidad_cabeza;
    }
    else
    {
        sentido = true;
    }

    this->velocidad_cabeza = velocidad_cabeza;
    this->velocidad_aspas = velocidad_aspas;

    rx.set(ejex, giro_x);
    ry.set(ejey, giro_y);

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
}

//IMPORTANTE: Las animaciones estan atadas a los FPS, por lo que si se cambian los FPS, se cambia la velocidad de las animaciones
void Aspas::actualizar()
{
    FiguraAnimada::actualizar();

    double tiempoTranscurrido = getTiempoTranscurrido();

    if(sentido)
        giro_y += velocidad_cabeza * tiempoTranscurrido;
    else
        giro_y -= velocidad_cabeza * tiempoTranscurrido;

    giro_x += velocidad_aspas * tiempoTranscurrido;

    if(giro_x > 360)
        giro_x -= 360;
    else if(giro_x < 0)
        giro_x += 360;
    

    if(giro_y >= ANGULO_MAXIMO)
        sentido = false;
    else if(giro_y <= -ANGULO_MAXIMO)
        sentido = true;

    rx.set(ejex, giro_x);
    ry.set(ejey, giro_y);
}

void Aspas::draw()
{
    //actualizar();
    molino.draw();
}


