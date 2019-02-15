#include "volcano.h"
#include "main.h"
#include "primitives.h"

Volcano::Volcano(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 90;
    int size = 40;
    int n=40;

    GLfloat side[100000];
    GLfloat centre[100000];
    makeCylinder(0,0,0, size , size*0.25f, 40.0f , n , side);
    makeCylinder(0,0,0, size*0.25 , size*0.24f, 40.0f , n , centre);
    this->side = create3DObject(GL_TRIANGLES, 4*n*3 , side, COLOR_BROWN , GL_FILL);
    this->centre = create3DObject(GL_TRIANGLES, 4*n*3 , centre, COLOR_ORANGE , GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->side);
    draw3DObject(this->centre);
}
