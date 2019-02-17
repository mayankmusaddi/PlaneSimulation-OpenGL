#include "arrow.h"
#include "main.h"
#include "primitives.h"

Arrow::Arrow(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->direction = glm::mat4(1.0f);
    this->rotation = 0;
    
    float size = 0.05;
    float thickness = size/2;

    static const GLfloat head[] = {
        -size, 0, 0,
        0, float(sqrt(3))*size, 0,
        +size, 0, 0, 

        -size, 0, -thickness,
        0, float(sqrt(3))*size, -thickness,
        +size, 0, -thickness, 

        -size, 0, 0,
        0, float(sqrt(3))*size, 0,
        -size, 0, -thickness,

        0, float(sqrt(3))*size, 0,
        -size, 0, -thickness,
        0, float(sqrt(3))*size, -thickness,

        0, float(sqrt(3))*size, 0,
        +size, 0, 0,
        0, float(sqrt(3))*size, -thickness,

        +size, 0, 0,
        0, float(sqrt(3))*size, -thickness,
        +size, 0, -thickness,

        -size, 0, 0,
        +size, 0, 0, 
        -size, 0, -thickness,

        +size, 0, 0, 
        -size, 0, -thickness,
        +size, 0, -thickness,
    };
    GLfloat body[100000];
    makeCuboid(0,-size,-thickness/2, 2*0.6*size, 2*size, thickness, body);

    this->body = create3DObject(GL_TRIANGLES, 12*3, body, COLOR_RED, GL_FILL);
    this->head = create3DObject(GL_TRIANGLES, 8*3, head, COLOR_RED, GL_FILL);
}

void Arrow::draw(glm::mat4 VP,glm::vec3 target) {

    glm::vec3 up = glm::vec3(0,0,-1);
    glm::vec3 y = glm::normalize(target - this->position);
    glm::vec3 x = glm::normalize(glm::cross(y, up));
    glm::vec3 z = glm::normalize(glm::cross(x,y));
    this->set_orientation(x,y,z);

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));

    Matrices.model *= (translate * direction * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->head);
    draw3DObject(this->body);
}

void Arrow::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Arrow::set_orientation(glm::vec3 x,glm::vec3 y,glm::vec3 z){
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