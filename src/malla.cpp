#include "malla.h"

Punto3D Malla::getVertice(int i){
    return Punto3D(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]);
}

void Malla::addNormal(int i, const Vector3D &normal){
    if(i >= 0 && i < normales.size() / 3){
        normales[i * 3] += normal.x;
        normales[i * 3 + 1] += normal.y;
        normales[i * 3 + 2] += normal.z;
    }
}

Vector3D Malla::getNormal(int i)
{
    if(i < 0 || i >= normales.size() / 3) return Vector3D();
    return Vector3D(normales[i * 3], normales[i * 3 + 1], normales[i * 3 + 2]);
}

void Malla::normalizarNormales(){
    for(int i = 0; i < normales.size(); i += 3){
        Vector3D normal(normales[i], normales[i + 1], normales[i + 2]);
        normal.normalizar();
        setNormal(i / 3, normal);
    }
}

void Malla::calcularNormalesVertices(){
    normales.resize(vertices.size(), 0);
    
    for(int i = 0; i < caras.size(); i += 3){
        Vector3D normal = getCara(i / 3).getNormal();

        addNormal(caras[i], normal);
        addNormal(caras[i + 1], normal);
        addNormal(caras[i + 2], normal);
    }
    
    normalizarNormales();
}

void Malla::setNormal(int i, const Vector3D &normal){
    if(i >= 0 && i < normales.size() / 3){
        normales[i * 3] = normal.x;
        normales[i * 3 + 1] = normal.y;
        normales[i * 3 + 2] = normal.z;
    }
}

Triangulo3D Malla::getCara(int i)
{
    if(i < 0 || i >= caras.size() / 3) return Triangulo3D();
    return Triangulo3D(getVertice(caras[i * 3]), getVertice(caras[i * 3 + 1]), getVertice(caras[i * 3 + 2]));
}

void Malla::setModoSombreado(int modo){
    if(modo == GL_FLAT || modo == GL_SMOOTH)
            modo_sombreado = modo;
}

void Malla::drawNormalesVertices()
{
    for(int i = 0; i < normales.size(); i += 3){
        float c = 0.5;
        glBegin(GL_LINES);
        {
            glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
            glVertex3f(vertices[i] + normales[i]*c, vertices[i + 1] + normales[i + 1]*c, vertices[i + 2] + normales[i + 2]*c);
        }
        glEnd();
    }
}

void Malla::drawNormalesCaras()
{
    for(int i = 0; i < caras.size(); i += 3){
        float c = 0.5;
        Punto3D centro = getCara(i / 3).getCentro();
        Vector3D normal = getCara(i / 3).getNormal();
        normal.normalizar();

        glBegin(GL_LINES);
        {
            glVertex3f(centro.x, centro.y, centro.z);
            glVertex3f(centro.x + normal.x*c, centro.y + normal.y*c, centro.z + normal.z*c);
        }
        glEnd();
    }
}

void Malla::draw() {
    if(modo_sombreado == GL_FLAT)
        glShadeModel(GL_FLAT);
    else
        glShadeModel(GL_SMOOTH);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    glNormalPointer(GL_FLOAT, 0, &normales[0]);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);

    glDrawElements(GL_TRIANGLES, caras.size(), GL_UNSIGNED_INT, &caras[0]);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glShadeModel(GL_FLAT);
}

void Malla::draw(bool draw_normales)
{
    draw();

    if(draw_normales){
        if(modo_sombreado == GL_FLAT)
            drawNormalesCaras();
        else
            drawNormalesVertices();
    }
}

void Malla::drawSmooth(bool draw_normales)
{
    glShadeModel(GL_SMOOTH);

    glBegin(GL_TRIANGLES);
    {
        for(int i = 0; i < caras.size(); i += 3){
            glNormal3f(normales[caras[i] * 3], normales[caras[i] * 3 + 1], normales[caras[i] * 3 + 2]);
            glVertex3f(vertices[caras[i] * 3], vertices[caras[i] * 3 + 1], vertices[caras[i] * 3 + 2]);
            glNormal3f(normales[caras[i + 1] * 3], normales[caras[i + 1] * 3 + 1], normales[caras[i + 1] * 3 + 2]);
            glVertex3f(vertices[caras[i + 1] * 3], vertices[caras[i + 1] * 3 + 1], vertices[caras[i + 1] * 3 + 2]);
            glNormal3f(normales[caras[i + 2] * 3], normales[caras[i + 2] * 3 + 1], normales[caras[i + 2] * 3 + 2]);
            glVertex3f(vertices[caras[i + 2] * 3], vertices[caras[i + 2] * 3 + 1], vertices[caras[i + 2] * 3 + 2]);
        }
    }
    glEnd();

    glShadeModel(GL_FLAT);

    if(draw_normales) drawNormalesVertices();
}

void Malla::drawFlat(bool draw_normales)
{
    glShadeModel(GL_FLAT);

    glBegin(GL_TRIANGLES);
    {
        for(int i = 0; i < caras.size(); i += 3){
            Vector3D normal = getCara(i / 3).getNormal().obtenerNormalizado();
            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3f(vertices[caras[i] * 3], vertices[caras[i] * 3 + 1], vertices[caras[i] * 3 + 2]);
            glVertex3f(vertices[caras[i + 1] * 3], vertices[caras[i + 1] * 3 + 1], vertices[caras[i + 1] * 3 + 2]);
            glVertex3f(vertices[caras[i + 2] * 3], vertices[caras[i + 2] * 3 + 1], vertices[caras[i + 2] * 3 + 2]);
        }
    }
    glEnd();

    if(draw_normales) drawNormalesCaras();
}
