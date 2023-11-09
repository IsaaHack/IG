#include "transformaciones.h"

Rotacion::Rotacion()
{
    eje = Vector3D(0, 0, 0);
    angulo = 0;
}

Rotacion::Rotacion(const Vector3D &eje, float angulo)
{
    this->eje = eje;
    this->angulo = angulo;
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

Traslacion::Traslacion()
{
    vector_traslacion = Vector3D(0, 0, 0);
}

Traslacion::Traslacion(const Vector3D &vector_traslacion)
{
    this->vector_traslacion = vector_traslacion;
}

void Traslacion::aplicar()
{
    glTranslatef(vector_traslacion.x, vector_traslacion.y, vector_traslacion.z);
}

void Traslacion::set(const Vector3D &vector_traslacion)
{
    this->vector_traslacion = vector_traslacion;
}

Vector3D Traslacion::getVectorTraslacion()
{
    return vector_traslacion;
}

Escalado::Escalado()
{
    vector_escalado = Vector3D(0, 0, 0);
}

Escalado::Escalado(const Vector3D &vector_escalado)
{
    this->vector_escalado = vector_escalado;
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
