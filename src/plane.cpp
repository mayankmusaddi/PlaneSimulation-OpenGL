#include "plane.h"
#include "main.h"
#include "primitives.h"

Plane::Plane(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->direction = glm::mat4(1.0f);
    this->speed = 0;
    this->distance = 0;
    this->rotationx = 0;
    this->rotationy = 0;
    this->rotationz = 0;
    
    int n=40;
    float size = 1;

    GLfloat body[100000];
    GLfloat nose[100000];
    GLfloat engine[100000];
    GLfloat fire[100000];
    makeSphere(0,0,0,size, size*1.5 , n , body);
    makeCylinder(0,0+size,0, size*0.80 , 0 , 2*size,n, nose);
    makeCylinder(0,0-5*size,0, size, size*0.80 , 4*size ,n, engine);
    makeCylinder(0,0-5*size,0, size*0.9, size*0.80 , size ,n, fire);

    static const GLfloat wings[] = {
         0,       1.5f*size, 0, // triangle 1 : begin
        -size*5, -2.5f*size, 0,
         size*5, -2.5f*size, 0, // triangle 1 : end
    };

    static const GLfloat tail[] = {
         0 ,        -3*size, 0, // triangle 1 : begin
        -2.5f*size, -5*size, 0,
         2.5f*size, -5*size, 0, // triangle 1 : end
    };

    this->wings = create3DObject(GL_TRIANGLES, 1*3, wings, COLOR_DARKGREY, GL_FILL);
    this->tail = create3DObject(GL_TRIANGLES, 1*3, tail, COLOR_DARKGREY, GL_FILL);
    this->body = create3DObject(GL_TRIANGLES, n*n*3, body, color, GL_LINE);
    this->nose = create3DObject(GL_TRIANGLES, 4*n*3, nose, color, GL_LINE);
    this->engine = create3DObject(GL_TRIANGLES, 4*n*3, engine, color, GL_FILL);
    this->fire = create3DObject(GL_TRIANGLES, 4*n*3, fire, COLOR_YELLOW, GL_FILL);
}

void Plane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotatex    = glm::rotate((float) (this->rotationx * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotatey    = glm::rotate((float) (this->rotationy * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotatez    = glm::rotate((float) (this->rotationz * M_PI / 180.0f), glm::vec3(0, 0, 1));

    direction *= rotatey;
    direction *= rotatex;
    direction *= rotatez;
    this->rotationx = 0;
    this->rotationy = 0;
    this->rotationz = 0;

    Matrices.model *= (translate * direction);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->wings);
    draw3DObject(this->tail);
    draw3DObject(this->body);
    draw3DObject(this->nose);
    draw3DObject(this->engine);
    draw3DObject(this->fire);
}

void Plane::yaw(){
    this->rotationz+=1;
}
void Plane::pitch(){
    this->rotationx+=1;
}
void Plane::roll(){
    this->rotationy-=1;
}
void Plane::yawR(){
    this->rotationz-=1;
}
void Plane::pitchR(){
    this->rotationx-=1;
}
void Plane::rollR(){
    this->rotationy+=1;
}

void Plane::tick(){
    this->position.x+= this->speed*direction[1].x;
    this->position.y+= this->speed*direction[1].y;
    this->position.z+= this->speed*direction[1].z;
    this->distance+= sqrt((this->speed*direction[1].x*this->speed*direction[1].x)+(this->speed*direction[1].y*this->speed*direction[1].y)+(this->speed*direction[1].z*this->speed*direction[1].z));
    if(this->position.x > 1500 || this->position.x < -1500 || this->position.y > 1500 || this->position.y < -1500 || this->position.z > 295 || this->position.z < -11)
        this->speed = 0;
}

void Plane::moveForward(){
    if(this->speed < 1)
    this->speed+=0.01;
}
void Plane::moveBackward(){
    if(this->speed >= 0.01)
        this->speed -=0.01;
}

void Plane::crash(){
    this->speed = 2;
    this->rotationx = -3;
}