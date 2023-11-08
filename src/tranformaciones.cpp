#include "tranformaciones.h"

Rotacion* Rotacion::instancia = nullptr;

Rotacion::Rotacion()
{
    eje = Vector3D(0, 0, 0);
    angulo = 0;
}

Rotacion::~Rotacion()
{
    delete instancia;
}

Rotacion *Rotacion::getInstancia()
{
    if (instancia == NULL)
        instancia = new Rotacion();
    return instancia;
}

void Rotacion::aplicar()
{
    glRotatef(angulo, eje.x, eje.y, eje.z);
}

void Rotacion::set(const Vector3D &eje, float angulo)
{
    this->eje = eje;
    this->angulo = angulo;
}

void Rotacion::setEje(const Vector3D &eje)
{
    this->eje = eje;
}

void Rotacion::setAngulo(float angulo)
{
    this->angulo = angulo;
}

Vector3D Rotacion::getEje()
{
    return this->eje;
}

float Rotacion::getAngulo()
{
    return angulo;
}

Traslacion* Traslacion::instancia = nullptr;

Traslacion::Traslacion()
{
    vector_traslacion = Vector3D(0, 0, 0);
}

Traslacion::~Traslacion()
{
    delete instancia;
}

Traslacion *Traslacion::getInstancia()
{
    if (instancia == nullptr)
        instancia = new Traslacion();
    return instancia;
}

void Traslacion::aplicar()
{
    glTranslatef(vector_traslacion.x, vector_traslacion.y, vector_traslacion.z);
}

void Traslacion::set(const Vector3D &vector_traslacion)
{
    this->vector_traslacion = vector_traslacion;
}

Escalado* Escalado::instancia = nullptr;

Escalado::Escalado()
{
    vector_escalado = Vector3D(0, 0, 0);
}

Escalado::~Escalado()
{
    delete instancia;
}

Escalado *Escalado::getInstancia()
{
    if (instancia == nullptr)
        instancia = new Escalado();
    return instancia;
}

void Escalado::aplicar()
{
    glScalef(vector_escalado.x, vector_escalado.y, vector_escalado.z);
}

void Escalado::set(const Vector3D &vector_escalado)
{
    this->vector_escalado = vector_escalado;
}

Vector3D Escalado::getVectorEscalado()
{
    return vector_escalado;
}
