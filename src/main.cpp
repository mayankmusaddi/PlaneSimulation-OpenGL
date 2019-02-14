#include "main.h"
#include "timer.h"
#include "plane.h"
#include "ground.h"
#include "altimeter.h"
#include "speedometer.h"
#include "fuel.h"
#include "island.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
Plane plane;
Ground ground;
Altimeter altimeter;
Speedometer speedometer;
vector <Fuel> fuels;

Island island;

// float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int view=0;
bool shot = false;
long long fuel = 10;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 eye,target,up;
    
    switch(view)
    {
        case 0:
        {   
            //Top View
            eye = glm::vec3(plane.position.x, plane.position.y,300);
            target = plane.position;
            up = glm::vec3(0, 1, 0);
            Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
            break;
        }
        case 1:
        {
            //Plane view
            eye = plane.position;
            target = glm::vec3(plane.position.x+plane.direction[1].x , plane.position.y+plane.direction[1].y , plane.position.z+plane.direction[1].z);    
            up = plane.direction[2];
            Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D        
            break;
        }
        case 2:
        {
            //Follow-Cam View
            eye = glm::vec3(plane.position.x - 10*plane.direction[1].x ,plane.position.y- 10*plane.direction[1].y ,plane.position.z - 10*plane.direction[1].z + 5);
            target = glm::vec3(plane.position.x+plane.direction[1].x , plane.position.y+plane.direction[1].y , plane.position.z+plane.direction[1].z);    
            up = plane.direction[2];
            Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D        
            break;
        }
        case 3:
        {
            //Tower View
            eye = glm::vec3(50,50,25);
            target = glm::vec3(0,0,0);    
            up = glm::vec3(0,0,1);
            Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D        
            break;
        }
    }
    // z,x,y for static orientation of any object with respect to screen

    glm::vec3 z = glm::normalize(target-eye);
    glm::vec3 x = glm::normalize(glm::cross(z, up));
    glm::vec3 y = glm::normalize(glm::cross(x,z));

    altimeter    = Altimeter(-0.4,0.1,0,plane.position.z);
    altimeter.set_position(eye.x + 0.5*z.x, eye.y + 0.5*z.y , eye.z + 0.5*z.z);
    altimeter.set_orientation(x,y,z);

    speedometer  = Speedometer(-0.37,-0.27,0,plane.speed);
    speedometer.set_position(eye.x + 0.5*z.x, eye.y + 0.5*z.y , eye.z + 0.5*z.z);
    speedometer.set_orientation(x,y,z);

    for(int i=0;i<(int)(fuels).size();i++)
    {   
        fuels[i].set_position(eye.x + 0.5*z.x, eye.y + 0.5*z.y , eye.z + 0.5*z.z);
        fuels[i].set_orientation(x,y,z);
    }
    // Compute Camera matrix (view)
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    plane.draw(VP);
    ground.draw(VP);
    altimeter.draw(VP);
    speedometer.draw(VP);
    for(int i=0;i<(int)(fuels).size();i++)
        fuels[i].draw(VP);
    island.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int b = glfwGetKey(window, GLFW_KEY_B);
    int c = glfwGetKey(window, GLFW_KEY_C);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int q = glfwGetKey(window, GLFW_KEY_Q);
    int e = glfwGetKey(window, GLFW_KEY_E);

    if (c && !shot) {
        changeView();
        shot = true;
    }
    if(c == GLFW_RELEASE && shot==true)
        shot=false;
    
    if(w)
        plane.moveForward();
    if(s)
        plane.moveBackward();
    if(q)
        plane.yaw();
    if(e)
        plane.yawR();
    if(a)
        plane.roll();
    if(d)
        plane.rollR();
    if(space)
        plane.pitch();
    if(b)
        plane.pitchR();
    if(left)
        camera_rotation_angle+=1;
}

void changeView() {
    view=(view+1)%4;
}

void tick_elements() {
    plane.tick();
    if(plane.distance > 2500)
    {
        fuel--;
        fuels.pop_back();
        plane.distance = 0;
    }
    if(fuel == 0)
        plane.crash();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    plane       = Plane(0, 0, 0, COLOR_GREY);
    ground      = Ground(0,0,-10, COLOR_BLUE);
    island      = Island(0,0,-10,COLOR_YELLOW);
    for(int i=0;i<fuel;i++)
        fuels.push_back(Fuel(-0.45 + 0.05*(i),-0.45,0));

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    Matrices.projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 3000.0f);
}
