#include "ring.h"
#include "main.h"
#include "primitives.h"

Ring::Ring(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->size = 6;
    int n=40;

    GLfloat ring[100000];
    makeTube(0,0,0, size , size*0.8, 1, n , ring);
    this->ring = create3DObject(GL_TRIANGLES, 24*n , ring, COLOR_ORANGE , GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ring);
}