#include "ground.h"
#include "main.h"

Ground::Ground(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    float length = 1500;

    GLfloat waves1[1000000];
    GLfloat waves2[1000000];
    int k=0,l=0,div=15;
    for(int j=0;j<2*length;j+=div)
    {
        for(int i=0;i<2*length;i+=div)
        {
            float height = 2;
            waves1[k++] = i+(j%2)*div  -length    ; waves1[k++] = j      -length; waves1[k++] = height;
            waves1[k++] = i+(j%2)*div  -length    ; waves1[k++] = j+div    -length; waves1[k++] = 0;
            waves1[k++] = i+((j+1)%2)*div-length    ; waves1[k++] = j+(i%2)*div-length; waves1[k++] = height;

            waves2[l++] = i+((j+1)%2)*div-length    ; waves2[l++] = j          -length; waves2[l++] = height;
            waves2[l++] = i+((j+1)%2)*div-length    ; waves2[l++] = j+div        -length; waves2[l++] = 0;
            waves2[l++] = i+(j%2)*div  -length    ; waves2[l++] = j+((i+1)%2)*div-length; waves2[l++] = height;
        }
    }
    GLfloat waves3[]= {
        -length, -length, 0,
        -length,  length, 0,
         length, -length, 0,
         length, -length, 0,
         length,  length, 0,
        -length,  length, 0,
    };
    this->waves1 = create3DObject(GL_TRIANGLES, 3*4*length/div*length/div, waves1, COLOR_BLUE , GL_FILL);
    this->waves2 = create3DObject(GL_TRIANGLES, 3*4*length/div*length/div, waves2, COLOR_LIGHTBLUE , GL_FILL);
    this->waves3 = create3DObject(GL_TRIANGLES, 2*3, waves3, COLOR_DARKBLUE , GL_FILL);
}

void Ground::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->waves1);
    draw3DObject(this->waves2);
    draw3DObject(this->waves3);
}
