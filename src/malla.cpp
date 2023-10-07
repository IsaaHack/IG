#include "malla.h"

void Malla::cargar(const char *nombre_archivo_ply){
    read(nombre_archivo_ply, vertices, caras);

    for(int i = 0; i < caras.size(); i += 3){
        
    }
}

void Malla::draw()
{
}
