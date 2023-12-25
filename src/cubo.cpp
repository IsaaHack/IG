#include "cubo.h"
#include "gestorIdGeometria.h"

void Cubo::calcularVertices(){
  Punto3D puntos[8];

  //p0 = (lado, 0, 0)
  //p1 = (lado, 0, lado)
  //p2 = (lado, lado, lado)
  //p3 = (lado, lado, 0)
  //p4 = (0, 0, 0)
  //p5 = (0, 0, lado)
  //p6 = (0, lado, lado)
  //p7 = (0, lado, 0)

  puntos[0].x = puntos[1].x = puntos[2].x = puntos[3].x = lado;
  puntos[4].x = puntos[5].x = puntos[6].x = puntos[7].x = 0;
  puntos[0].y = puntos[1].y = puntos[4].y = puntos[5].y = 0;
  puntos[2].y = puntos[3].y = puntos[6].y = puntos[7].y = lado;
  puntos[0].z = puntos[3].z = puntos[4].z = puntos[7].z = 0;
  puntos[1].z = puntos[2].z = puntos[5].z = puntos[6].z = lado;

  for(int i = 0; i < 8; i++){
    malla.vertices.push_back(puntos[i].x);
    malla.vertices.push_back(puntos[i].y);
    malla.vertices.push_back(puntos[i].z);
  }
}

void Cubo::calcularCaras(){
  int caras[6][4] = {
    {2, 1, 0, 3}, //Lado derecho
    {1, 2, 6, 5}, //Lado superior
    {4, 5, 6, 7}, //Lado izquierdo
    {3, 0, 4, 7}, //Lado inferior
    {1, 5, 4, 0}, //Lado trasero
    {2, 3, 7, 6}  //Lado frontal
  };

  for(int i = 0; i < 6; i++){
    malla.caras.push_back(caras[i][0]);
    malla.caras.push_back(caras[i][1]);
    malla.caras.push_back(caras[i][2]);

    malla.caras.push_back(caras[i][0]);
    malla.caras.push_back(caras[i][2]);
    malla.caras.push_back(caras[i][3]);
  }
}

void Cubo::cargar(const char *nombre_archivo_ply){
  Geometria::clear();

  calcularVertices();
  calcularCaras();
  malla.calcularNormalesVertices();
}

void Cubo::cargarTextura(const char *nombre_archivo_jpg){
  Geometria::cargarTextura(nombre_archivo_jpg);
}

void Cubo::draw()
{
  if(malla.id_textura == 0 || GestorIdGeometria::getInstancia()->getModo() == MODO_SELECCION){
    Geometria::draw();
    return;
  }

  /**
  {2, 1, 0, 3}, //Lado derecho
  {1, 2, 6, 5}, //Lado frontal
  {4, 5, 6, 7}, //Lado izquierdo
  {3, 0, 4, 7}, //Lado trasero
  {1, 5, 4, 0}, //Lado inferior
  {2, 3, 7, 6}  //Lado superior
  */
  Punto3D p0(malla.vertices[0], malla.vertices[1], malla.vertices[2]);
  Punto3D p1(malla.vertices[3], malla.vertices[4], malla.vertices[5]);
  Punto3D p2(malla.vertices[6], malla.vertices[7], malla.vertices[8]);
  Punto3D p3(malla.vertices[9], malla.vertices[10], malla.vertices[11]);
  Punto3D p4(malla.vertices[12], malla.vertices[13], malla.vertices[14]);
  Punto3D p5(malla.vertices[15], malla.vertices[16], malla.vertices[17]);
  Punto3D p6(malla.vertices[18], malla.vertices[19], malla.vertices[20]);
  Punto3D p7(malla.vertices[21], malla.vertices[22], malla.vertices[23]);

  material.draw();

  if(malla.modo_sombreado == GL_FLAT)
    glShadeModel(GL_FLAT);
  else
    glShadeModel(GL_SMOOTH);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, malla.id_textura);

  glBegin(GL_QUADS);
  {
    //Lado derecho (Número 3)
    Vector3D normal = Triangulo3D(p2, p1, p0).getNormal().obtenerNormalizado();
    glNormal3f(normal.x, normal.y, normal.z);
    glTexCoord2f(0.5, 0.5);
    p2.dibuja();
    glTexCoord2f(0.75, 0.5);
    p1.dibuja();
    glTexCoord2f(0.75, 0.25);
    p0.dibuja();
    glTexCoord2f(0.5, 0.25);
    p3.dibuja();

    //Lado frontal (Número 2)
    normal = Triangulo3D(p1, p2, p6).getNormal().obtenerNormalizado();
    glNormal3f(normal.x, normal.y, normal.z);
    glTexCoord2f(0.75, 0.5);
    p1.dibuja();
    glTexCoord2f(0.5, 0.5);
    p2.dibuja();
    glTexCoord2f(0.5, 0.75);
    p6.dibuja();
    glTexCoord2f(0.75, 0.75);
    p5.dibuja();

    //Lado izquierdo (Número 4)
    normal = Triangulo3D(p4, p5, p6).getNormal().obtenerNormalizado();
    glNormal3f(normal.x, normal.y, normal.z);
    glTexCoord2f(0.75, 1);
    p4.dibuja();
    glTexCoord2f(0.75, 0.75);
    p5.dibuja();
    glTexCoord2f(0.5, 0.75);
    p6.dibuja();
    glTexCoord2f(0.5, 1);
    p7.dibuja();

    //Lado trasero (Número 5)
    normal = Triangulo3D(p3, p0, p4).getNormal().obtenerNormalizado();
    glNormal3f(normal.x, normal.y, normal.z);
    glTexCoord2f(0.25, 0.5);
    p3.dibuja();
    glTexCoord2f(0, 0.5);
    p0.dibuja();
    glTexCoord2f(0, 0.75);
    p4.dibuja();
    glTexCoord2f(0.25, 0.75);
    p7.dibuja();

    //Lado inferior (Número 6)
    normal = Triangulo3D(p1, p5, p4).getNormal().obtenerNormalizado();
    glNormal3f(normal.x, normal.y, normal.z);
    glTexCoord2f(0.75, 0.5);
    p1.dibuja();
    glTexCoord2f(0.75, 0.75);
    p5.dibuja();
    glTexCoord2f(1, 0.75);
    p4.dibuja();
    glTexCoord2f(1, 0.5);
    p0.dibuja();

    //Lado superior (Número 1)
    normal = Triangulo3D(p2, p3, p7).getNormal().obtenerNormalizado();
    glNormal3f(normal.x, normal.y, normal.z);
    glTexCoord2f(0.5, 0.5);
    p2.dibuja();
    glTexCoord2f(0.25, 0.5);
    p3.dibuja();
    glTexCoord2f(0.25, 0.75);
    p7.dibuja();
    glTexCoord2f(0.5, 0.75);
    p6.dibuja();

  }
  glEnd();

  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);

  glShadeModel(GL_FLAT);
}