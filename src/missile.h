#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(float x, float y,float z,glm::mat4 direction);
    glm::vec3 position;
    float rotation;
    float size;
    glm::mat4 direction;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *head;
    VAO *body;
};

#endif // MISSILE_H
