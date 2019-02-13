#include "altimeter.h"
#include "main.h"
#include "primitives.h"

Altimeter::Altimeter(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->direction = glm::mat4(1.0f);
    this->altitude = 0;
    int size=5;

    GLfloat slider[1000];
    GLfloat panel[1000];
    makeCuboid(x,y,z,1,10,2,panel);
    makeCuboid(x,y,z,1.5,1,0,slider);

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

void Altimeter::tick(){
}