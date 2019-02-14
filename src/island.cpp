#include "island.h"
#include "main.h"
#include "primitives.h"

Island::Island(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 90;
    float size = 100;
    int n=40;

    GLfloat island[100000];
    makeCylinder(x,y,z, size , size*0.8, 10.0f , n , island);
    this->island = create3DObject(GL_TRIANGLES, 4*n*3 , island, color , GL_FILL);
}

void Island::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->island);
}
