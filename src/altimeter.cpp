#include "altimeter.h"
#include "main.h"
#include "primitives.h"

Altimeter::Altimeter(float x, float y,float z, float altitude) {
    this->position = glm::vec3(x, y, z);
    this->direction = glm::mat4(1.0f);
    this->altitude = altitude;
    float size=0.4;

    GLfloat slider[1000];
    GLfloat panel[1000];
    makeCuboid(x ,y, z, size/10 ,size  ,0,panel);
    makeCuboid(x ,y + (altitude+10)*size/300 - size/2, z, 3*size/20,size/10,0,slider);

    this->slider = create3DObject(GL_TRIANGLES, 12*3 , slider, COLOR_RED, GL_FILL);
    this->panel = create3DObject(GL_TRIANGLES, 12*3, panel, COLOR_BLACK, GL_FILL);
}

void Altimeter::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (  translate * direction);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->panel);
    draw3DObject(this->slider);
}

void Altimeter::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Altimeter::set_orientation(glm::vec3 x,glm::vec3 y,glm::vec3 z){
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

void Altimeter::tick(){
}