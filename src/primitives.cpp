#include "primitives.h"

void makeCylinder(float x, float y,float z, float r1, float r2, float length,int n, GLfloat vertex_buffer_data[]) {
    int k=0;
    for(int i=0;i<n;i++)
    {
        vertex_buffer_data[k++]= x+0.0f;
        vertex_buffer_data[k++]= y+0.0f;
        vertex_buffer_data[k++]= z+0.0f;

        vertex_buffer_data[k++]= x+(r1*cos(2*M_PI/n*i));
        vertex_buffer_data[k++]= y+0.0f;
        vertex_buffer_data[k++]= z+(r1*sin(2*M_PI/n*i));

        vertex_buffer_data[k++]= x+(r1*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data[k++]= y+0.0f;
        vertex_buffer_data[k++]= z+(r1*sin(2*M_PI/n*(i+1)));
    }
    for(int i=0;i<n;i++)
    {
        vertex_buffer_data[k++]= x+0.0f;
        vertex_buffer_data[k++]= y+length;
        vertex_buffer_data[k++]= z+0.0f;

        vertex_buffer_data[k++]= x+(r2*cos(2*M_PI/n*i));
        vertex_buffer_data[k++]= y+length;
        vertex_buffer_data[k++]= z+(r2*sin(2*M_PI/n*i));

        vertex_buffer_data[k++]= x+(r2*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data[k++]= y+length;
        vertex_buffer_data[k++]= z+(r2*sin(2*M_PI/n*(i+1)));
    }
    for(int i=0;i<n;i++)
    {
        vertex_buffer_data[k++]= x+(r1*cos(2*M_PI/n*i));
        vertex_buffer_data[k++]= y+0.0f;
        vertex_buffer_data[k++]= z+(r1*sin(2*M_PI/n*i));

        vertex_buffer_data[k++]= x+(r1*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data[k++]= y+0.0f;
        vertex_buffer_data[k++]= z+(r1*sin(2*M_PI/n*(i+1)));

        vertex_buffer_data[k++]= x+(r2*cos(2*M_PI/n*i));
        vertex_buffer_data[k++]= y+length;
        vertex_buffer_data[k++]= z+(r2*sin(2*M_PI/n*i));

        vertex_buffer_data[k++]= x+(r2*cos(2*M_PI/n*i));
        vertex_buffer_data[k++]= y+length;
        vertex_buffer_data[k++]= z+(r2*sin(2*M_PI/n*i));

        vertex_buffer_data[k++]= x+(r2*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data[k++]= y+length;
        vertex_buffer_data[k++]= z+(r2*sin(2*M_PI/n*(i+1)));

        vertex_buffer_data[k++]= x+(r1*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data[k++]= y+0.0f;
        vertex_buffer_data[k++]= z+(r1*sin(2*M_PI/n*(i+1)));
    }
    return;
}

void makeSphere(float x, float y,float z, float r,float el,int n, GLfloat vertex_buffer_data[]) {
    int k=0;
    for(int j=-n/4;j<n/4;j++)
    {
        float r1 = (r*cos(2*M_PI/n*j));
        float r2 = (r*cos(2*M_PI/n*(j+1)));
        for(int i=0;i<n;i++)
        {
            vertex_buffer_data[k++]= (r1*cos(2*M_PI/n*i));
            vertex_buffer_data[k++]= el*(r*sin(2*M_PI/n*j));
            vertex_buffer_data[k++]= (r1*sin(2*M_PI/n*i));

            vertex_buffer_data[k++]= (r1*cos(2*M_PI/n*(i+1)));
            vertex_buffer_data[k++]= el*(r*sin(2*M_PI/n*j));
            vertex_buffer_data[k++]= (r1*sin(2*M_PI/n*(i+1)));

            vertex_buffer_data[k++]= (r2*cos(2*M_PI/n*i));
            vertex_buffer_data[k++]= el*(r*sin(2*M_PI/n*(j+1)));
            vertex_buffer_data[k++]= (r2*sin(2*M_PI/n*i));

            vertex_buffer_data[k++]= (r2*cos(2*M_PI/n*i));
            vertex_buffer_data[k++]= el*(r*sin(2*M_PI/n*(j+1)));
            vertex_buffer_data[k++]= (r2*sin(2*M_PI/n*i));

            vertex_buffer_data[k++]= (r2*cos(2*M_PI/n*(i+1)));
            vertex_buffer_data[k++]= el*(r*sin(2*M_PI/n*(j+1)));
            vertex_buffer_data[k++]= (r2*sin(2*M_PI/n*(i+1)));

            vertex_buffer_data[k++]= (r1*cos(2*M_PI/n*(i+1)));
            vertex_buffer_data[k++]= el*(r*sin(2*M_PI/n*j));
            vertex_buffer_data[k++]= (r1*sin(2*M_PI/n*(i+1)));
        }
    }
    return;
}

void makeCuboid(float x, float y,float z, float w, float h, float b, GLfloat vertex_buffer_data[]) {
    GLfloat temp[] = {
        -w/2+x,-h/2+y,-b/2+z, // triangle 1 : begin
        -w/2+x,-h/2+y, b/2+z,
        -w/2+x, h/2+y, b/2+z, // triangle 1 : end
         w/2+x, h/2+y,-b/2+z, // triangle 2 : begin
        -w/2+x,-h/2+y,-b/2+z,
        -w/2+x, h/2+y,-b/2+z, // triangle 2 : end
         w/2+x,-h/2+y, b/2+z,
        -w/2+x,-h/2+y,-b/2+z,
         w/2+x,-h/2+y,-b/2+z,
         w/2+x, h/2+y,-b/2+z,
         w/2+x,-h/2+y,-b/2+z,
        -w/2+x,-h/2+y,-b/2+z,
        -w/2+x,-h/2+y,-b/2+z,
        -w/2+x, h/2+y, b/2+z,
        -w/2+x, h/2+y,-b/2+z,
         w/2+x,-h/2+y, b/2+z,
        -w/2+x,-h/2+y, b/2+z,
        -w/2+x,-h/2+y,-b/2+z,
        -w/2+x, h/2+y, b/2+z,
        -w/2+x,-h/2+y, b/2+z,
         w/2+x,-h/2+y, b/2+z,
         w/2+x, h/2+y, b/2+z,
         w/2+x,-h/2+y,-b/2+z,
         w/2+x, h/2+y,-b/2+z,
         w/2+x,-h/2+y,-b/2+z,
         w/2+x, h/2+y, b/2+z,
         w/2+x,-h/2+y, b/2+z,
         w/2+x, h/2+y, b/2+z,
         w/2+x, h/2+y,-b/2+z,
        -w/2+x, h/2+y,-b/2+z,
         w/2+x, h/2+y, b/2+z,
        -w/2+x, h/2+y,-b/2+z,
        -w/2+x, h/2+y, b/2+z,
         w/2+x, h/2+y, b/2+z,
        -w/2+x, h/2+y, b/2+z,
         w/2+x,-h/2+y, b/2+z
    };
    std::copy( temp, temp+110 , vertex_buffer_data);
    return;
}
// this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);