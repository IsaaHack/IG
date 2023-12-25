#include "gestorIdGeometria.h"

GeneradorID::GeneradorID(){
    contador = 1;
}

unsigned int GeneradorID::getID(){
    if(id_libres.empty()){
        if(contador == MAX_ID)
            throw std::runtime_error("Se ha alcanzado el maximo numero de IDs");
        return contador++;
    }else{
        unsigned int id = *id_libres.begin();
        id_libres.erase(id);
        return id;
    }
}

void GeneradorID::liberaID(unsigned int id){
    id_libres.insert(id);
}

GestorIdGeometria* GestorIdGeometria::instancia = nullptr;

GestorIdGeometria::GestorIdGeometria(){
    modo = MODO_NORMAL;
}

GestorIdGeometria::~GestorIdGeometria(){
    delete instancia;
}

GestorIdGeometria* GestorIdGeometria::getInstancia(){
    if(instancia == nullptr)
        instancia = new GestorIdGeometria();
    return instancia;
}

void GestorIdGeometria::addGeometria(Geometria* geometria){
    geometrias.insert(std::pair<unsigned int, Geometria*>(generadorID.getID(), geometria));
}

void GestorIdGeometria::borraGeometria(Geometria* geometria){
    /**
    for(auto it = geometrias.begin(); it != geometrias.end(); it++){
        if(it->second == geometria){
            generadorID.liberaID(it->first);
            geometrias.erase(it);
            break;
        }
    }
    */
}

void GestorIdGeometria::setModo(bool modo){
    this->modo = modo;
}

bool GestorIdGeometria::getModo() const{
    return modo;
}

unsigned int GestorIdGeometria::getID(Geometria* geometria){
    for(auto it = geometrias.begin(); it != geometrias.end(); it++){
        if(it->second == geometria){
            return it->first;
        }
    }
    
    std::runtime_error("No se ha encontrado la geometria");

    return 0;
}

Geometria* GestorIdGeometria::getGeometria(unsigned int id){
    return geometrias[id];
}