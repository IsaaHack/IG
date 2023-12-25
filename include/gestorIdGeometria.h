#ifndef GESTOR_ID_GEOMETRIA_H
#define GESTOR_ID_GEOMETRIA_H

#include <map>
#include <set>
#include <geometria.h>

#define MODO_NORMAL 0
#define MODO_SELECCION 1

#define MAX_ID 1 << 24

class GeneradorID{
private:
    unsigned int contador;
    set<unsigned int> id_libres;
public:
    GeneradorID();
    unsigned int getID();
    void liberaID(unsigned int id);
};

class GestorIdGeometria{
private:
    static GestorIdGeometria* instancia;

    GeneradorID generadorID;
    map<unsigned int, Geometria*> geometrias;
    bool modo;

    GestorIdGeometria();
    ~GestorIdGeometria();
public:
    static GestorIdGeometria* getInstancia();
    void addGeometria(Geometria* geometria);
    void borraGeometria(Geometria* geometria);
    unsigned int getID(Geometria* geometria);
    void setModo(bool modo);
    bool getModo() const;
    Geometria* getGeometria(unsigned int id);
};

#endif