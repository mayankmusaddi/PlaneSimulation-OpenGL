#include "main.h"

#ifndef ISLAND_H
#define ISLAND_H


class Island {
public:
    Island() {}
    Island(float x, float y,float z, float size);
    glm::vec3 position;
    float rotation;
    float size;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO *island;
};

#endif // ISLAND_H
