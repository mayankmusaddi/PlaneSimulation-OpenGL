#include "main.h"
#ifndef PRIMITVES_H
#define PRIMITVES_H

void makeCylinder(float x, float y,float z, float r1, float r2, float length,int n, GLfloat vertex_buffer_data[]);
void makeSphere(float x, float y,float z, float r,float el,int n, GLfloat vertex_buffer_data[]);
void makeSemiSphere(float x, float y,float z, float r,float el,int n, GLfloat vertex_buffer_data[]);
void makeCircle(float x, float y,float z, float r,int n, GLfloat vertex_buffer_data[]);
void makeCuboid(float x, float y,float z, float h, float w, float b, GLfloat vertex_buffer_data[]);
void makeRing(float x, float y,float z, float r1,float r2,int n, GLfloat vertex_buffer_data[]);
void makeTube(float x, float y,float z, float r1, float r2, float length,int n, GLfloat vertex_buffer_data[]);

#endif // PRIMITVES_H
