#include "main.h"

#ifndef ALTIMETER_H
#define ALTIMETER_H


class Altimeter {
public:
    Altimeter() {}
    Altimeter(float x, float y,float z);
    glm::vec3 position;
    glm::mat4 direction;
    float altitude;
    void draw(glm::mat4 VP);
    void tick();
    void set_position(float x,float y,float z);
private:
    VAO *slider;
    VAO *panel;
};

#endif // ALTIMETER_H
