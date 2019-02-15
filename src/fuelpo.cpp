#include "fuelpo.h"
#include "main.h"
#include "primitives.h"

FuelPO::FuelPO(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = -90;
    float size = 2;
    int n=20;

    GLfloat cone[100000];
    GLfloat sphere[100000];
    makeSemiSphere(0,0,0, size , 1 , n , sphere);
    makeCylinder(0,-2*size,0, 0 , size, 2*size , n , cone);
    this->sphere = create3DObject(GL_TRIANGLES, n*n*3 , sphere, COLOR_DARKGREY , GL_FILL);
    this->cone = create3DObject(GL_TRIANGLES, 4*n*3 , cone, COLOR_DARKGREY , GL_FILL);
}

void FuelPO::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->sphere);
    draw3DObject(this->cone);
}
