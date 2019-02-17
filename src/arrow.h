#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y,float z);
    glm::vec3 position;
    glm::mat4 direction;

    float rotation;
    void draw(glm::mat4 VP,glm::vec3 target);
    // void tick(glm::vec3 target,glm::vec3 position,glm::mat4 direction);
    void set_position(float x, float y, float z);
    void set_orientation(glm::vec3 x,glm::vec3 y,glm::vec3 z);
private:
    VAO *head;
    VAO *body;
};

#endif // ARROW_H
