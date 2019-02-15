#include "main.h"

#ifndef CANONBALL_H
#define CANONBALL_H


class Canonball {
public:
    Canonball() {}
    Canonball(float x, float y,float z,glm::mat4 direction);
    glm::vec3 position;
    float rotation;
    glm::mat4 direction;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *ball;
};

#endif // CANONBALL_H
