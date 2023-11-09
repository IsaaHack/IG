#include "cubo.h"

void Cubo::draw()
  {
    float x, y, z;
    x = y = z = lado;
    //float color[4] = {0.8, 0.0, 1, 1};
    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glBegin(GL_QUAD_STRIP);
    {                            /* Caras transversales */
      glNormal3f(0.0, 0.0, 1.0); /*Vertical delantera */
      glVertex3f(x, y, z);
      glVertex3f(0, y, z);
      glVertex3f(x, 0, z);
      glVertex3f(0, 0, z);
      glNormal3f(0.0, -1.0, 0.0); /*Inferior */
      glVertex3f(x, 0, 0);
      glVertex3f(0, 0, 0);
      glNormal3f(0.0, 0.0, -1.0); /* Vertical hacia atras */
      glVertex3f(x, y, 0);
      glVertex3f(0, y, 0);
      glNormal3f(0.0, 1.0, 0.0); /* Superior, horizontal */
      glVertex3f(x, y, z);
      glVertex3f(0, y, z);
    }
    glEnd();
    glBegin(GL_QUADS);
    { /* Costados */
      glNormal3f(1.0, 0.0, 0.0);
      glVertex3f(x, 0, 0);
      glVertex3f(x, y, 0);
      glVertex3f(x, y, z);
      glVertex3f(x, 0, z);
      glNormal3f(-1.0, 0.0, 0.0);
      glVertex3f(0, 0, 0);
      glVertex3f(0, 0, z);
      glVertex3f(0, y, z);
      glVertex3f(0, y, 0);
    }
    glEnd();
  }