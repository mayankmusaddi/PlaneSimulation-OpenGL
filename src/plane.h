#include "main.h"

#ifndef PLANE_H
#define PLANE_H


class Plane {
public:
    Plane() {}
    Plane(float x, float y,float z, color_t color);
    glm::vec3 position;
    glm::mat4 direction;

    float rotationx;
    float rotationy;
    float rotationz;
    float radius;
    float elongation;
    float speed;
    float distance;
    void draw(glm::mat4 VP);
    void tick();

    void yaw();
    void pitch();
    void roll();
    void yawR();
    void pitchR();
    void rollR();

    void moveForward();
    void moveBackward();
    void crash();
private:
    VAO *wings;
    VAO *tail;
    VAO *body;
    VAO *nose;
    VAO *engine;
    VAO *fire;
};

#endif // PLANE_H
