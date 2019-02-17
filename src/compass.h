#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H


class Compass {
public:
    Compass() {}
    Compass(float x, float y,float z, glm::mat4 direction);
    glm::vec3 position;
    glm::mat4 direction;
    void draw(glm::mat4 VP);
    void set_position(float x,float y,float z);
    void set_orientation(glm::vec3 x,glm::vec3 y,glm::vec3 z);
private:
    VAO *slider;
    VAO *panel;
};

#endif // COMPASS_H
