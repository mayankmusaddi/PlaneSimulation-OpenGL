#include "main.h"

#ifndef FUELPO_H
#define FUELPO_H


class FuelPO {
public:
    FuelPO() {}
    FuelPO(float x, float y,float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO *cone;
    VAO *sphere;
};

#endif // FUELPO_H
