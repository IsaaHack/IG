#include "malla.h"
#include "lector-jpg.h"

Malla::Malla()
{
    modo_sombreado = GL_SMOOTH;
    id_textura = 0;
}

Malla::~Malla()
{
    if(id_textura != 0)
        glDeleteTextures(1, &id_textura);
}

Punto3D Malla::getVertice(int i) const{
    if(i < 0 || i >= vertices.size() / 3) return Punto3D();
    return Punto3D(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]);
}

void Malla::addNormal(int i, const Vector3D &normal){
    if(i >= 0 && i < normales.size() / 3){
        normales[i * 3] += normal.x;
        normales[i * 3 + 1] += normal.y;
        normales[i * 3 + 2] += normal.z;
    }
}

Vector3D Malla::getNormal(int i) const
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

Triangulo3D Malla::getCara(int i) const
{
    if(i < 0 || i >= caras.size() / 3) return Triangulo3D();
    return Triangulo3D(getVertice(caras[i * 3]), getVertice(caras[i * 3 + 1]), getVertice(caras[i * 3 + 2]));
}

void Malla::setModoSombreado(int modo){
    if(modo == GL_FLAT || modo == GL_SMOOTH)
            modo_sombreado = modo;
}

void Malla::setCoodenadasTextura(int i, float x, float y){
    if(i >= 0 && i < coordenadas_textura.size() / 2){
        coordenadas_textura[i * 2] = x;
        coordenadas_textura[i * 2 + 1] = y;
    }
}

void Malla::drawNormalesVertices() const
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

void Malla::drawNormalesCaras() const
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

void Malla::clear()
{
    vertices.clear();
    caras.clear();
    normales.clear();
    coordenadas_textura.clear();

    if(id_textura != 0){
        glDeleteTextures(1, &id_textura);
        id_textura = 0;
    }
}

void Malla::draw() {
    if(modo_sombreado == GL_FLAT){
        drawFlat();
        return;
    }else
        glShadeModel(GL_SMOOTH);


    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    if(id_textura != 0){
        glEnable(GL_TEXTURE_2D);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glBindTexture(GL_TEXTURE_2D, id_textura);
        glTexCoordPointer(2, GL_FLOAT, 0, &coordenadas_textura[0]);
    }
    
    glNormalPointer(GL_FLOAT, 0, &normales[0]);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);

    glDrawElements(GL_TRIANGLES, caras.size(), GL_UNSIGNED_INT, &caras[0]);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    if(id_textura != 0){
        glDisable(GL_TEXTURE_2D);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
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

    if(id_textura != 0){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, id_textura);
    }

    glBegin(GL_TRIANGLES);
    {
        if(id_textura != 0){ // Si hay textura
            for(int i = 0; i < caras.size(); i += 3){
                glNormal3f(normales[caras[i] * 3], normales[caras[i] * 3 + 1], normales[caras[i] * 3 + 2]);
                glTexCoord2f(coordenadas_textura[caras[i] * 2], coordenadas_textura[caras[i] * 2 + 1]);
                glVertex3f(vertices[caras[i] * 3], vertices[caras[i] * 3 + 1], vertices[caras[i] * 3 + 2]);
                glNormal3f(normales[caras[i + 1] * 3], normales[caras[i + 1] * 3 + 1], normales[caras[i + 1] * 3 + 2]);
                glTexCoord2f(coordenadas_textura[caras[i + 1] * 2], coordenadas_textura[caras[i + 1] * 2 + 1]);
                glVertex3f(vertices[caras[i + 1] * 3], vertices[caras[i + 1] * 3 + 1], vertices[caras[i + 1] * 3 + 2]);
                glNormal3f(normales[caras[i + 2] * 3], normales[caras[i + 2] * 3 + 1], normales[caras[i + 2] * 3 + 2]);
                glTexCoord2f(coordenadas_textura[caras[i + 2] * 2], coordenadas_textura[caras[i + 2] * 2 + 1]);
                glVertex3f(vertices[caras[i + 2] * 3], vertices[caras[i + 2] * 3 + 1], vertices[caras[i + 2] * 3 + 2]);
            }
        }else{ // Si no hay textura
            for(int i = 0; i < caras.size(); i += 3){
                glNormal3f(normales[caras[i] * 3], normales[caras[i] * 3 + 1], normales[caras[i] * 3 + 2]);
                glVertex3f(vertices[caras[i] * 3], vertices[caras[i] * 3 + 1], vertices[caras[i] * 3 + 2]);
                glNormal3f(normales[caras[i + 1] * 3], normales[caras[i + 1] * 3 + 1], normales[caras[i + 1] * 3 + 2]);
                glVertex3f(vertices[caras[i + 1] * 3], vertices[caras[i + 1] * 3 + 1], vertices[caras[i + 1] * 3 + 2]);
                glNormal3f(normales[caras[i + 2] * 3], normales[caras[i + 2] * 3 + 1], normales[caras[i + 2] * 3 + 2]);
                glVertex3f(vertices[caras[i + 2] * 3], vertices[caras[i + 2] * 3 + 1], vertices[caras[i + 2] * 3 + 2]);
            }
        }
    }
    glEnd();

    if(id_textura != 0){
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    }

    glShadeModel(GL_FLAT);

    if(draw_normales) drawNormalesVertices();
}

void Malla::drawFlat(bool draw_normales)
{
    glShadeModel(GL_FLAT);

    if(id_textura != 0){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, id_textura);
    }

    glBegin(GL_TRIANGLES);
    {
        if(id_textura != 0){ // Si hay textura
            for(int i = 0; i < caras.size(); i += 3){
                Vector3D normal = getCara(i / 3).getNormal().obtenerNormalizado();
                glNormal3f(normal.x, normal.y, normal.z);
                glTexCoord2f(coordenadas_textura[caras[i] * 2], coordenadas_textura[caras[i] * 2 + 1]);
                glVertex3f(vertices[caras[i] * 3], vertices[caras[i] * 3 + 1], vertices[caras[i] * 3 + 2]);
                glTexCoord2f(coordenadas_textura[caras[i + 1] * 2], coordenadas_textura[caras[i + 1] * 2 + 1]);
                glVertex3f(vertices[caras[i + 1] * 3], vertices[caras[i + 1] * 3 + 1], vertices[caras[i + 1] * 3 + 2]);
                glTexCoord2f(coordenadas_textura[caras[i + 2] * 2], coordenadas_textura[caras[i + 2] * 2 + 1]);
                glVertex3f(vertices[caras[i + 2] * 3], vertices[caras[i + 2] * 3 + 1], vertices[caras[i + 2] * 3 + 2]);
            }
        }else{ // Si no hay textura
            for(int i = 0; i < caras.size(); i += 3){
                Vector3D normal = getCara(i / 3).getNormal().obtenerNormalizado();
                glNormal3f(normal.x, normal.y, normal.z);
                glVertex3f(vertices[caras[i] * 3], vertices[caras[i] * 3 + 1], vertices[caras[i] * 3 + 2]);
                glVertex3f(vertices[caras[i + 1] * 3], vertices[caras[i + 1] * 3 + 1], vertices[caras[i + 1] * 3 + 2]);
                glVertex3f(vertices[caras[i + 2] * 3], vertices[caras[i + 2] * 3 + 1], vertices[caras[i + 2] * 3 + 2]);
            }
        }

    }
    glEnd();

    if(id_textura != 0){
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    }

    if(draw_normales) drawNormalesCaras();
}

void Malla::asignarTextura(unsigned char *data, int width, int height){
    coordenadas_textura.resize(vertices.size()*2, 0);

    glGenTextures(1, &id_textura);
    glBindTexture(GL_TEXTURE_2D, id_textura);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // GL_CLAMP
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // GL_CLAMP
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_NEAREST
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_NEAREST

    glBindTexture(GL_TEXTURE_2D, 0);

    delete[] data;
}

void Malla::escalarVertices(float x, float y, float z){
    for(int i = 0; i < vertices.size(); i += 3){
        vertices[i] *= x;
        vertices[i + 1] *= y;
        vertices[i + 2] *= z;
    }

    calcularNormalesVertices();
    normalizarNormales();
}