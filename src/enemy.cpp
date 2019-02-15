#include "enemy.h"
#include "main.h"
#include "primitives.h"

Enemy::Enemy(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->direction = glm::mat4(1.0f);
    float size = 3;
    int n=20;

    GLfloat base[100000];
    GLfloat body[100000];
    makeCylinder(0,   0,0,    0 , size*1.2 , 2*size   , n , base);
    makeCylinder(0,size,0, size , size     , 5*size , n , body);
    this->base = create3DObject(GL_TRIANGLES, 4*n*3 , base, COLOR_RED , GL_FILL);
    this->body = create3DObject(GL_TRIANGLES, 4*n*3 , body, COLOR_DARKGREY , GL_FILL);
}

void Enemy::draw(glm::mat4 VP,glm::vec3 target) {

    glm::vec3 up = glm::vec3(0,0,-1);
    glm::vec3 y = -glm::normalize(target - this->position);
    glm::vec3 x = glm::normalize(glm::cross(y, up));
    glm::vec3 z = glm::normalize(glm::cross(x,y));
    this->set_orientation(x,y,z);

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate * direction);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->base);
    draw3DObject(this->body);
}

void Enemy::set_orientation(glm::vec3 x,glm::vec3 y,glm::vec3 z){
    this->direction[0][0] = x.x;
    this->direction[0][1] = x.y;
    this->direction[0][2] = x.z;
    this->direction[0][3] = 0;

    this->direction[1][0] = y.x;
    this->direction[1][1] = y.y;
    this->direction[1][2] = y.z;
    this->direction[1][3] = 0;

    this->direction[2][0] = z.x;
    this->direction[2][1] = z.y;
    this->direction[2][2] = z.z;
    this->direction[2][3] = 0;

    this->direction[3][0] = 0;
    this->direction[3][1] = 0;
    this->direction[3][2] = 0;
    this->direction[3][3] = 1;
}