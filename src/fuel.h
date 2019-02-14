#include "main.h"

#ifndef FUEL_H
#define FUEL_H


class Fuel {
public:
    Fuel() {}
    Fuel(float x, float y,float z);
    glm::vec3 position;
    glm::mat4 direction;
    float altitude;
    void draw(glm::mat4 VP);
    void tick();
    void set_position(float x,float y,float z);
    void set_orientation(glm::vec3 x,glm::vec3 y,glm::vec3 z);
private:
    VAO *circle;
    VAO *triangle;
};

#endif // FUEL_H
