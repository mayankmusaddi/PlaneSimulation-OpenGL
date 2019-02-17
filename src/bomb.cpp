#include "bomb.h"
#include "main.h"
#include "primitives.h"

Bomb::Bomb(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    float size = 3;
    int n=20;

    GLfloat bomb[100000];
    makeCuboid(0,0,0, size , size, size , bomb);
    this->bomb = create3DObject(GL_TRIANGLES, 12*3 , bomb, COLOR_RED , GL_FILL);
}

void Bomb::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->bomb);
}

void Bomb::tick(){
    this->position.z-= 1;
}
