#include "canonball.h"
#include "main.h"
#include "primitives.h"

Canonball::Canonball(float x, float y,float z,glm::mat4 direction) {
    this->position = glm::vec3(x, y, z);
    this->direction = direction;
    this->rotation = 0;
    this->size = 1;
    int n=20;

    GLfloat ball[100000];
    makeSphere(0,0,0, size , 1,  n , ball);
    this->ball = create3DObject(GL_TRIANGLES, n*n*3 , ball, COLOR_ORANGE , GL_FILL);
}

void Canonball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate * this->direction);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ball);
}

void Canonball::tick(){
    this->position.x-= 2*this->direction[1].x;
    this->position.y-= 2*this->direction[1].y;
    this->position.z-= 2*this->direction[1].z;
}
