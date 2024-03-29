#include "speedometer.h"
#include "main.h"
#include "primitives.h"

Speedometer::Speedometer(float x, float y,float z, float speed) {
    this->position = glm::vec3(x, y, z);
    this->direction = glm::mat4(1.0f);
    this->speed = speed;

    float size=0.1f;
    int n=20;
    GLfloat panel[1000];
    float angle = (7.0/6.0 * M_PI) - (this->speed*(4.0/3.0)*M_PI);
    makeCircle(x,y,z, size, n, panel);
    GLfloat slider[] = {
        x - float((size/10)*sin(angle)), y + float((size/10)*cos(angle)) ,z + 0.0f,
        x + float(size * cos(angle)) , y + float(size*sin(angle)) , z + 0.0f,
        x + float((size/10)*sin(angle)), y - float((size/10)*cos(angle)) ,z + 0.0f,
    };
    this->slider = create3DObject(GL_TRIANGLES, 1*3 , slider, COLOR_RED, GL_FILL);
    this->panel = create3DObject(GL_TRIANGLES, n*3, panel, COLOR_BLACK, GL_FILL);
}

void Speedometer::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (  translate * direction);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->panel);
    draw3DObject(this->slider);
}

void Speedometer::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Speedometer::set_orientation(glm::vec3 x,glm::vec3 y,glm::vec3 z){
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

void Speedometer::tick(){
}