#include "main.h"

#ifndef SKY_H
#define SKY_H


class Sky {
public:
    Sky() {}
    Sky(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO *object;
};

#endif // SKY_H
