#include "figuraAnimada.h"

FiguraAnimada::FiguraAnimada()
{
    tiempo_anterior = clock();
    tiempo_actual = clock();
}

void FiguraAnimada::actualizar()
{
    tiempo_anterior = tiempo_actual;
    tiempo_actual = clock();
}

double FiguraAnimada::getTiempoTranscurrido()
{
    return (double)(tiempo_actual - tiempo_anterior) / CLOCKS_PER_SEC;
}