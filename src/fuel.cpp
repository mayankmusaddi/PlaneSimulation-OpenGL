#include "fuel.h"
#include "main.h"
#include "primitives.h"

Fuel::Fuel(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->direction = glm::mat4(1.0f);
    float size=0.02;
    int n=20;

    GLfloat circle[1000];
    makeCircle(x,y,z, size, n, circle);
    GLfloat triangle[]={
        x-size,y,z,
        x+size,y,z,
        x,y+2*size,z,
    };
    this->circle = create3DObject(GL_TRIANGLES, n*3 , circle, COLOR_DARKGREY, GL_FILL);
    this->triangle = create3DObject(GL_TRIANGLES, 1*3, triangle, COLOR_DARKGREY, GL_FILL);
}

void Fuel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (  translate * direction);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->circle);
    draw3DObject(this->triangle);
}

void Fuel::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Fuel::set_orientation(glm::vec3 x,glm::vec3 y,glm::vec3 z){
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

void Fuel::tick(){
}