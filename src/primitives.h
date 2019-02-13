#include "main.h"
#ifndef PRIMITVES_H
#define PRIMITVES_H

void makeCylinder(float x, float y,float z, float r1, float r2, float length,int n, GLfloat vertex_buffer_data[]);
void makeSphere(float x, float y,float z, float r,float el,int n, GLfloat vertex_buffer_data[]);
void makeCuboid(float x, float y,float z, float h, float w, float b, GLfloat vertex_buffer_data[]);

#endif // PRIMITVES_H
