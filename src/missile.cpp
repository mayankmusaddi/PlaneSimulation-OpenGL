#include "missile.h"
#include "main.h"
#include "primitives.h"

Missile::Missile(float x, float y,float z,glm::mat4 direction) {
    this->position = glm::vec3(x, y, z);
    this->direction = direction;
    this->rotation = 0;
    this->size = 3;
    int n=20;

    GLfloat head[100000];
    GLfloat body[100000];
    makeCylinder(0,0,0, size*0.15 , 0, size , n , head);
    makeCylinder(0,0,0, size*0.14 , 0, size , n , body);
    this->head = create3DObject(GL_TRIANGLES, 4*n*3 , head, COLOR_DARKGREY , GL_FILL);
    this->body = create3DObject(GL_TRIANGLES, 4*n*3 , body, COLOR_ORANGE , GL_FILL);
}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate * this->direction);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->head);
    draw3DObject(this->body);
}

void Missile::tick(){
    this->position.x+= 1.5*this->direction[1].x;
    this->position.y+= 1.5*this->direction[1].y;
    this->position.z+= 1.5*this->direction[1].z;
}
