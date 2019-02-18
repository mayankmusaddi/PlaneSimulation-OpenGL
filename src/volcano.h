#include "main.h"

#ifndef VOLCANO_H
#define VOLCANO_H


class Volcano {
public:
    Volcano() {}
    Volcano(float x, float y,float z);
    glm::vec3 position;
    float rotation;
    float size;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO *side;
    VAO *centre;
};

#endif // VOLCANO_H
