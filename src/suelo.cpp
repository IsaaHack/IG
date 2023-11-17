#include "suelo.h"

void Suelo::draw(){
    glPushMatrix();
        float color[4] = {1.0, 1.0, 1.0, 1.0};
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
        glBegin(GL_QUADS);
            glNormal3f(0.0, 1.0, 0.0); // Normal vertical
            glVertex3f(200.0, 0.0, 200.0);
            glVertex3f(200.0, 0.0, -200.0);
            glVertex3f(-200.0, 0.0, -200.0);
            glVertex3f(-200.0, 0.0, 200.0);
        glEnd();
    glPopMatrix();
}