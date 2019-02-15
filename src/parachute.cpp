#include "parachute.h"
#include "main.h"
#include "primitives.h"

Parachute::Parachute(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 90;
    float size = 5;
    int n=20;

    GLfloat canopy[100000];
    GLfloat thread[] = {
        size,0.0f,0.0f,
        size*0.9f,0.0f,0.0f,
        size*0.5f,-size,0.0f,

        -size,0.0f,0.0f,
        -size*0.9f,0.0f,0.0f,
        -size*0.5f,-size,0.0f,

        0.0f,0.0f,size,
        0.0f,0.0f,size*0.9f,
        0.0f,-size,0.5f*size,

        0.0f,0.0f,-size,
        0.0f,0.0f,-size*0.9f,
        0.0f,-size,-0.5f*size,
    };
    GLfloat turret[100000];
    makeSemiSphere(0,0,0, size , 1 , n , canopy);
    makeCylinder(0,-1.5*size,0, size*0.5 , size*0.5, size*0.5 , 4 , turret);
    this->canopy = create3DObject(GL_TRIANGLES, n*n*3 , canopy, COLOR_RED , GL_FILL);
    this->turret = create3DObject(GL_TRIANGLES, 4*4*3 , turret, COLOR_ORANGE , GL_FILL);
    this->thread = create3DObject(GL_TRIANGLES, 4*3 , thread, COLOR_BLACK , GL_FILL);
}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->canopy);
    draw3DObject(this->turret);
    draw3DObject(this->thread);
}

void Parachute::tick(){
    this->position.z-=0.1;
}
