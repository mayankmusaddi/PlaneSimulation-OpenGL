#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y,float z);
    glm::vec3 position;
    glm::mat4 direction;
    float rotation;
    float size;
    void draw(glm::mat4 VP,glm::vec3 target);
    void set_position(float x, float y, float z);
    void set_orientation(glm::vec3 x,glm::vec3 y,glm::vec3 z);
private:
    VAO *base;
    VAO *body;
};

#endif // ENEMY_H
