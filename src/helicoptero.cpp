#include "helicoptero.h"

Helicoptero::Helicoptero()
{
    r1_.set(ejex, 90);
    
    heli.addHijo(&r1_);
    heli.addHijo(&cuerpo);
    heli.addHijo(&helice);
}

Helicoptero::Helicoptero(float velodidad_helice)
{
    r1_.set(ejex, -90);
    giro_x_actual = 0;
    ry.set(ejez, giro_x_actual);
    
    heli.addHijo(&r1_);
    heli.addHijo(&cuerpo);
    heli.addHijo(&asp);

    asp.addHijo(&ry);
    asp.addHijo(&helice);
    
    this->velodidad_helice = velodidad_helice;
}

void Helicoptero::cargar(const char *ply_cuerpo, const char *ply_helice)
{
    cuerpo.cargar(ply_cuerpo);
    helice.cargar(ply_helice);
}

void Helicoptero::cargar(const char *ply)
{
    cuerpo.cargar("plys/heli.ply");
    helice.cargar("plys/helices.ply");
}

void Helicoptero::actualizar()
{
    giro_x_actual += velodidad_helice;
    ry.set(ejez, giro_x_actual);
}

void Helicoptero::draw()
{
    actualizar();
    heli.draw();
}

