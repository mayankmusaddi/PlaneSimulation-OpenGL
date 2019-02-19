# Fighter Plane Simulation using OpenGL

You are Link and you operate one of the finest fighter plane.
The goal of the game is to obtain the maximum amount of points in the duration of your game.  The game consists of the following:
  - Hover and move through the Map which is randomly generated.
  - Shoot Missiles and Bombs to kill your enemies (Canon and Parachutes).
  - Dodge the Canonballs and Avoid Volcanoes.
  - Collect Fuel Powerups on the way to make sure you dont run out of fuel and crash.
  - Pass through rings to gain extra scores.
  - Swap through different views.
  		- Plane view: This is a view from the plane’s position where only a part of the world in front is visible. In other words, in this view, we see what the plane sees, as if we were the plane.
  		- Top View: This is a top-down view, as if we were looking vertically downwards from a position in the sky. This gives a clear picture of the path.
  		- Tower view: Here, the camera is sitting on a tower, to the side of the plane of playing, observing it at an angle.
  		- Follow-cam view: This is a view of the plane and the region in front of it from a location behind and above it, as if the camera is following the plane.
  		- Helicopter-cam view: Here, the camera is movable with the mouse in an intuitive manner. Clicking and dragging should change the look angle and the scroll wheel will move the camera closer or farther away from the scene.

# New Features!

  - Perform stunts like Loop in a Loop and Barrel Roll.
  - Sound Effects.
  - Compass to guide you the North Direction.
  - Enemy Canon pointing towards you always.

# Controls

Following are the Keyboard Controls : 
  - 'W' and 'S' : To increase and decrease speed. Speed can be monitored in the speedometer in the dashboard.
  - 'A' and 'D' : To make the plane roll left and right respectively.
  - 'Q' and 'E' : To make the plane yaw left and right respectively.
  - 'Space' and 'B' : To make the plane litch up and down respectively.
  - 'C' : To change the View of the Plane.
  - 'Z' : To perform a loop in a loop.
  - 'X' : To perform a barrel roll.

The Mouse Controls are as follows : 
  - Left Click : To shoot Missiles.
  - Right Click : To shoot Bombs.
  - In Helicopter View (by pressing 'C' 4 times from the start)
  	- Hover on Right side of the screen : To rotate view clockwise
  	- Hover on Left side of the screen : To rotate view anticlockwise
  	- Hover on Top of the scree, : To rotate along the top of the plane
  	- Hover on Bottom of the scree, : To rotate along the bottom of the plane
  	- Scroll Up : Zoom in
  	- Scroll Down : Zoom out

# Installation

Jetpack Funride requires C++ and OpenGl to run.
The following development packages of the following libraries should be installed:
 - GLEW
 - GLFW3
 - GLM

Installation instructions
### For Fedora
```
$ sudo pkgconf-pkg-config dnf install glew-devel glfw-devel glm-devel cmake pkgconf 
```
### For Ubuntu
```
$ sudo apt install libglew-dev libglfw3-dev libglm-dev cmake pkg-config
```
(Use apt-get if you don’t have aptitude installed but I suggest installing it)
### For Mac
Install homebrew
```
brew install glew glfw glm cmake pkg-config
```
### For Other distros
Use the equivalent of apt search or dnf search and make sure you install the devel packages
### Driver Issues
If you do face driver issues, try to update your drivers. If you continue facing issues even after installing, I suggest you update your operating system to the latest stable release. You can also try building the libraries, but it would be a waste of time IMO.

# How to Run

To run, clone the directory, make sure all the required packages are installed, then type the following commands, inside the cloned directory.

```sh
$ cd build
$ ./graphics_asgn1
```
If you want to make some edits then make sure to run the following commands to compile the changes:
```
$ cd build
$ make all
```

License
-------
The MIT License https://mayankmusaddi.mit-license.org/

Copyright &copy; 2019 Mayank Musaddi <mayank.musaddi@research.iiit.ac.in>
