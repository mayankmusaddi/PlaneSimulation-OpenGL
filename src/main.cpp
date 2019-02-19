#include "main.h"
#include "timer.h"
#include "plane.h"
#include "ground.h"
#include "altimeter.h"
#include "speedometer.h"
#include "fuel.h"
#include "island.h"
#include "volcano.h"
#include "parachute.h"
#include "missile.h"
#include "fuelpo.h"
#include "enemy.h"
#include "canonball.h"
#include "ring.h"
#include "arrow.h"
#include "bomb.h"
#include "compass.h"

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
Compass compass;
Arrow arrow;
Enemy enemy;
vector <Fuel> fuels;
vector <Island> islands;
vector <Volcano> volcanoes;
vector <Parachute> parachutes;
vector <Missile> missiles;
vector <FuelPO> fuelpos;
vector <Canonball> canonballs;
vector <Ring> rings;
vector <Bomb> bombs;

Timer etime,ptime;
float camera_rotation_angle = 0;
int view=0;
bool cflag = false, rcflag = false, lcflag= false,zflag = false,xflag = false, towerflag = false, dead = false, loopflag = false, brollflag = false;
long long fuel = 5, health = 5, score = 0,prog=0,rotatel = 0,rotateb = 0;
double xpos,ypos;
float dphi = 0, dtheta = -30,zoom=50;
glm::vec3 pos;

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
            towerflag = false;
            //Plane view
            eye = plane.position;
            target = glm::vec3(plane.position.x+plane.direction[1].x , plane.position.y+plane.direction[1].y , plane.position.z+plane.direction[1].z);    
            up = plane.direction[2];
            Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D        
            break;
        }
        case 1:
        {   
            //Top View
            eye = glm::vec3(plane.position.x, plane.position.y,300);
            target = plane.position;
            up = glm::vec3(plane.direction[1].x,plane.direction[1].y,0);
            Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
            break;
        }
        case 2:
        {
            //Tower View
            if(!towerflag)
            {
                pos = plane.position;
                towerflag = true;
            }
            eye = glm::vec3(pos.x+ 50,pos.y+50,pos.z+50);
            target = plane.position;    
            up = glm::vec3(0,0,1);
            Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D        
            break;
        }
        case 3:
        {
            //Follow-Cam View
            eye = glm::vec3(plane.position.x - 10*plane.direction[1].x ,plane.position.y- 10*plane.direction[1].y ,plane.position.z - 10*plane.direction[1].z + 5);
            target = glm::vec3(plane.position.x+plane.direction[1].x , plane.position.y+plane.direction[1].y , plane.position.z+plane.direction[1].z);    
            up = plane.direction[2];
            Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D        
            break;
        }
        case 4:
        {
            //Helicopter View

            float phi = dphi * M_PI/180.0;
            float theta = dtheta * M_PI/180.0;           
            
            float bx =  cos(theta) * sin(phi);
            float by =  cos(theta) * cos(phi);
            float bz =  sin(theta);

            float nx = zoom * bx/sqrt(bx*bx+by*by+bz*bz);
            float ny = zoom * by/sqrt(bx*bx+by*by+bz*bz);
            float nz = zoom * bz/sqrt(bx*bx+by*by+bz*bz);

            eye = glm::vec3(plane.position.x - nx ,plane.position.y- ny ,plane.position.z - nz);
            target = plane.position;    
            up = glm::vec3(0,0,1);
            Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D        
            break;
        }
    }
    // z,x,y for static orientation of any object with respect to screen
    glm::vec3 z = glm::normalize(target-eye);
    glm::vec3 x = glm::normalize(glm::cross(z, up));
    glm::vec3 y = glm::normalize(glm::cross(x,z));

    //static objects are created and aligned here

    //altimeter
    altimeter    = Altimeter(-0.4,0.1,0,plane.position.z);
    altimeter.set_position(eye.x + 0.5*z.x, eye.y + 0.5*z.y , eye.z + 0.5*z.z);
    altimeter.set_orientation(x,y,z);

    //speedometer
    speedometer  = Speedometer(-0.37,-0.27,0,plane.speed);
    speedometer.set_position(eye.x + 0.5*z.x, eye.y + 0.5*z.y , eye.z + 0.5*z.z);
    speedometer.set_orientation(x,y,z);

    //compass
    compass  = Compass(0.4,-0.4,0,plane.direction);
    compass.set_position(eye.x + 0.5*z.x, eye.y + 0.5*z.y , eye.z + 0.5*z.z);
    compass.set_orientation(x,y,z);

    //guiding arrow
    arrow  = Arrow(0,0,0);
    arrow.set_position(eye.x + 0.5*z.x + 0.35*y.x , eye.y + 0.5*z.y + 0.35*y.y, eye.z + 0.5*z.z + 0.35*y.z);

    //fuel bar
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
    compass.draw(VP);
    arrow.draw(VP,enemy.position);
    enemy.draw(VP,plane.position);

    for(int i=0;i<(int)(fuels).size();i++)
        fuels[i].draw(VP);
    for(int i=0;i<(int)(islands).size();i++)
        islands[i].draw(VP);
    for(int i=0;i<(int)(volcanoes).size();i++)
        volcanoes[i].draw(VP);
    for(int i=0;i<(int)(parachutes).size();i++)
        parachutes[i].draw(VP);
    for(int i=0;i<(int)(missiles).size();i++)
        missiles[i].draw(VP);
    for(int i=0;i<(int)(bombs).size();i++)
        bombs[i].draw(VP);
    for(int i=0;i<(int)(fuelpos).size();i++)
        fuelpos[i].draw(VP);
    for(int i=0;i<(int)(canonballs).size();i++)
        canonballs[i].draw(VP);
    for(int i=0;i<(int)(rings).size();i++)
        rings[i].draw(VP);
}

void tick_input(GLFWwindow *window) {
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int lclick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int rclick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    int b = glfwGetKey(window, GLFW_KEY_B);
    int c = glfwGetKey(window, GLFW_KEY_C);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int q = glfwGetKey(window, GLFW_KEY_Q);
    int e = glfwGetKey(window, GLFW_KEY_E);
    int z = glfwGetKey(window, GLFW_KEY_Z);
    int x = glfwGetKey(window, GLFW_KEY_X);

    if (c && !cflag) {
        changeView();
        cflag = true;
    }
    if(c == GLFW_RELEASE && cflag==true)
        cflag=false;

    if(lclick && !lcflag){
        system("aplay -c 1 -t wav -q ../sound/missile.wav&");
        missiles.push_back(Missile(plane.position.x,plane.position.y,plane.position.z,plane.direction));
        lcflag = true;
    }
    if(lclick == GLFW_RELEASE && lcflag==true)
        lcflag=false;
    
    if(rclick && !rcflag){
        system("aplay -c 1 -t wav -q ../sound/bomb.wav&");
        bombs.push_back(Bomb(plane.position.x,plane.position.y,plane.position.z));
        rcflag = true;
    }
    if(rclick == GLFW_RELEASE && rcflag==true)
        rcflag=false;

    if(z && !zflag){
        system("aplay -c 1 -t wav -q ../sound/loop.wav&");
        loopflag = true;
        zflag = true;
    }
    if(z == GLFW_RELEASE && zflag==true)
        zflag=false;
    
    if(x && !xflag){
        system("aplay -c 1 -t wav -q ../sound/roll.wav&");
        brollflag = true;
        xflag = true;
    }
    if(x == GLFW_RELEASE && xflag==true)
        xflag=false;

    if(w && !dead)
        plane.moveForward();
    if(s && !dead)
        plane.moveBackward();
    if(q && !dead)
        plane.yaw();
    if(e && !dead)
        plane.yawR();
    if(a && !dead)
        plane.roll();
    if(d && !dead)
        plane.rollR();
    if(space && !dead)
        plane.pitch();
    if(b && !dead)
        plane.pitchR();

    glfwGetCursorPos(window,&xpos,&ypos);
    if(xpos > 800 && xpos < 1000 && ypos >0 && ypos <1000)
        dphi--;
    if(xpos < 200 && xpos > 0 && ypos >0 && ypos <1000)
        dphi++;
    if(ypos > 800 && ypos < 1000  && xpos >0 && xpos <1000)
        dtheta++;
    if(ypos < 200 && ypos > 0  && xpos >0 && xpos <1000)
        dtheta--;
}

void changeView() {
    view=(view+1)%5;
}

void loop(){
    if(rotatel < 360 && loopflag)
    {
        plane.pitch();
        rotatel+=1;
    }
    else
    {
        loopflag = false;
        rotatel = 0;
    }
}

void barrelroll(){
    if(rotateb < 360 && brollflag)
    {
        plane.roll();
        rotateb++;
    }
    else
    {
        brollflag = false;
        rotateb = 0;
    }
}

void tick_elements() {
    plane.tick();
    loop();
    barrelroll();
    if(prog==10)
    {
        printf("OBSTACLE COURSE COMPLETED\n");
        printf("Score : %lld\n",score);
    }
    if(health == 0)
        plane.crash();

    bounding_box_t pl;
    pl.pos.x=plane.position.x;
    pl.pos.y=plane.position.y - plane.size;
    pl.pos.z=plane.position.z;
    pl.width = plane.size*4;
    pl.height = plane.size*4;
    pl.breadth = plane.size;

    //Fuel Decrease
    if(plane.distance > 2500)
    {
        fuel--;
        fuels.pop_back();
        plane.distance = 0;
    }
    if(fuel == 0)
        plane.crash();

    //COLLISION DETECTION for PLANE
    //for Ground
    if(plane.position.z < -10)
    {
        printf("YOU ARE DEAD\n");
        printf("Score : %lld\n",score);
        printf("CheckPoint Remaining : %lld\n",10-prog);
        quit(window);
    }
    //for Volcano
    for(int i=0;i<(int)(volcanoes).size();i++)
    {
        bounding_box_t vl;
        vl.pos = volcanoes[i].position;
        vl.width = volcanoes[i].size/4;
        vl.height = volcanoes[i].size/4;
        vl.breadth = 600;

        if(detect_collision(pl,vl))
            plane.crash();
    }
    //for Fuel Powerup
    for(int i=0;i<(int)(fuelpos).size();i++)
    {
        bounding_box_t fpo;
        fpo.pos.x = fuelpos[i].position.x;
        fpo.pos.y = fuelpos[i].position.y;
        fpo.pos.z = fuelpos[i].position.z + fuelpos[i].size/2.0;
        fpo.width = 2*fuelpos[i].size;
        fpo.height = 2*fuelpos[i].size;
        fpo.breadth = 3*fuelpos[i].size;

        if(detect_collision(pl,fpo))
        {
            fuelpos.erase(fuelpos.begin()+i);
            fuels.push_back(Fuel(-0.45 + 0.05*(fuel),-0.45,0));
            fuel+=1;
            system("aplay -c 1 -t wav -q ../sound/fuelup.wav&");
        }
    }
    //for Ring
    for(int i=0;i<(int)(rings).size();i++)
    {
        bounding_box_t r;
        r.pos = rings[i].position;
        r.width = rings[i].size;
        r.height = 1;
        r.breadth = rings[i].size;

        if(detect_collision(pl,r))
        {
            rings.erase(rings.begin()+i);
            score+=10;
            system("aplay -c 1 -t wav -q ../sound/ring.wav&");
        }
    }
    //for CanonBall
    for(int i=0;i<(int)(canonballs).size();i++)
    {
        bounding_box_t cb;
        cb.pos = canonballs[i].position;
        cb.width = 2*canonballs[i].size;
        cb.height = 2*canonballs[i].size;
        cb.breadth = 2*canonballs[i].size;

        if(detect_collision(pl,cb))
        {
            canonballs.erase(canonballs.begin()+i);
            health-=1;
            system("aplay -c 1 -t wav -q ../sound/loss.wav&");
        }
    }

    //COLLISION DETECTION for MISSILE
    for(int i=0;i<(int)(missiles).size();i++)
    {
        bounding_box_t m;
        m.pos = missiles[i].position;
        m.width = missiles[i].size;
        m.height = missiles[i].size;
        m.breadth = missiles[i].size;

        for(int j=0;j<(int)(parachutes).size();j++)
        {
            bounding_box_t p;
            p.pos = parachutes[j].position;
            p.width = 2*parachutes[j].size;
            p.height = 2*parachutes[j].size;
            p.breadth = 2*parachutes[j].size;

            if(detect_collision(p,m))
            {
                parachutes.erase(parachutes.begin()+j);
                missiles.erase(missiles.begin()+i);
                score+=10;
                system("aplay -c 1 -t wav -q ../sound/hit.wav&");
            }
        }
        bounding_box_t e;
        e.pos = enemy.position;
        e.width = 4*enemy.size;
        e.height = 4*enemy.size;
        e.breadth = 4*enemy.size;

        if(detect_collision(e,m))
        {
            Island island = islands[rand()%50];
            enemy.set_position(island.position.x + rand()%int(0.8*island.size-60)+40, island.position.y + rand()%int(0.8*island.size-60)+40,5);
            prog++;
            missiles.erase(missiles.begin()+i);
            score+=10;
            system("aplay -c 1 -t wav -q ../sound/checkpoint.wav&");
        }
        if(missiles[i].position.z < 0)
            missiles.erase(missiles.begin()+i);
    }

    //COLLISION DETECTION for BOMBS
    for(int i=0;i<(int)(bombs).size();i++)
    {
        bounding_box_t b;
        b.pos = bombs[i].position;
        b.width = bombs[i].size;
        b.height = bombs[i].size;
        b.breadth = bombs[i].size;

        for(int j=0;j<(int)(parachutes).size();j++)
        {
            bounding_box_t p;
            p.pos = parachutes[j].position;
            p.width = 2*parachutes[j].size;
            p.height = 2*parachutes[j].size;
            p.breadth = 2*parachutes[j].size;

            if(detect_collision(p,b))
            {
                parachutes.erase(parachutes.begin()+j);
                bombs.erase(bombs.begin()+i);
                score+=10;
                system("aplay -c 1 -t wav -q ../sound/hit.wav&");
            }
        }
        bounding_box_t e;
        e.pos = enemy.position;
        e.width = 4*enemy.size;
        e.height = 4*enemy.size;
        e.breadth = 4*enemy.size;

        if(detect_collision(e,b))
        {
            Island island = islands[rand()%50];
            enemy.set_position(island.position.x + rand()%int(0.8*island.size-60)+40, island.position.y + rand()%int(0.8*island.size-60)+40,5);
            prog++;
            bombs.erase(bombs.begin()+i);
            score+=10;
            system("aplay -c 1 -t wav -q ../sound/checkpoint.wav&");
        }
        if(bombs[i].position.z < 0){
            bombs.erase(bombs.begin()+i);
            system("aplay -c 1 -t wav -q ../sound/bombhit.wav&");
        }
    }
    
    //MOVEMENT AND GENERATION
    //for Parachutes
    for(int i=0;i<(int)(parachutes).size();i++)
        parachutes[i].tick();
    if(ptime.processTick())
    {
        for(int i=0;i<20;i++)
            parachutes.push_back(Parachute(rand()%2901-1450 , rand()%2901-1450,300));
    }
    //for Missiles and Bomb
    for(int i=0;i<(int)(missiles).size();i++)
        missiles[i].tick();
    for(int i=0;i<(int)(bombs).size();i++)
        bombs[i].tick();
    //for Enemy and CanonBalls
    if( glm::distance(plane.position,enemy.position) < 300 && etime.processTick())
        canonballs.push_back(Canonball(enemy.position.x,enemy.position.y,enemy.position.z,enemy.direction));
    for(int i=0;i<(int)(canonballs).size();i++)
        canonballs[i].tick();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    plane       = Plane(0, 0, 200, COLOR_GREY);
    ground      = Ground(0, 0,-10, COLOR_BLUE);

    for(int i=0;i<50;i++)
    {
        int x = rand()%3000-1500;
        int y = rand()%3000-1500;
        int size = (rand()%(1500 - max(abs(x),abs(y))))%250+70;
        islands.push_back(Island(x,y,-10,size));
    }
    for(int i=0;i<20;i++)
    {
        Island island = islands[rand()%50];
        volcanoes.push_back(Volcano(island.position.x, island.position.y,0));
    }
    for(int i=0;i<20;i++)
    {
        fuelpos.push_back(FuelPO( rand()%2901-1450 , rand()%2901-1450 , rand()%280+ 10 ));
        rings.push_back(Ring(rand()%2901-1450,rand()%2901-1450,rand()%280+ 10));
    }
    for(int i=0;i<20;i++)
        parachutes.push_back(Parachute(rand()%2901-1450 , rand()%2901-1450,300));
    ptime = Timer(50);

    Island island = islands[rand()%50];
    enemy = (Enemy(island.position.x + rand()%int(0.8*island.size-60)+40, island.position.y + rand()%int(0.8*island.size-60)+40,5));
    etime = Timer(1);

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
    int width  = 1000;
    int height = 1000;

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

            string sc = "Score : "+to_string(score)+" | Health : "+to_string(health) + " | Remaining : "+to_string(10-prog);
            char scr[1000];
            strcpy(scr,sc.c_str());
            glfwSetWindowTitle(window,scr);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.pos.x - b.pos.x) * 2 < (a.width + b.width)) &&
           (abs(a.pos.y - b.pos.y) * 2 < (a.height + b.height)) &&
           (abs(a.pos.z - b.pos.z) * 2 < (a.breadth + b.breadth));
}

void reset_screen() {
    Matrices.projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 3000.0f);
}
