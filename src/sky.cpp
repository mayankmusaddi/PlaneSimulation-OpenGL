#include "sky.h"
#include "main.h"
#include "primitives.h"

Sky::Sky(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    float radius = 1500;
    int n=40;

    GLfloat sky[100000];
    makeSphere(x,y,z, radius , 1 , n , sky);
    this->object = create3DObject(GL_TRIANGLES, n*n*3, sky, color , GL_FILL);
}

void Sky::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
