#include "main.h"

#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H


class Speedometer {
public:
    Speedometer() {}
    Speedometer(float x, float y,float z, float speed);
    glm::vec3 position;
    glm::mat4 direction;
    float speed;
    void draw(glm::mat4 VP);
    void tick();
    void set_position(float x,float y,float z);
    void set_orientation(glm::vec3 x,glm::vec3 y,glm::vec3 z);
private:
    VAO *slider;
    VAO *panel;
};

#endif // SPEEDOMETER_H
