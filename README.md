# 2d-particle-sim
2D N-body particle simulator and player in C using OpenGL and GLFW.
The goal of this project is to create a fast, easy to use and fully customizable N-body particle simulator in 2D for linux.

## System Requirements
To compile and run you need the following:
- A GPU with **OpenGL 4.5** (or higher) support;
- **G++** and [**GLFW**](https://stackoverflow.com/questions/17768008/how-to-build-install-glfw-3-and-use-it-in-a-linux-project) installed on your machine.

## Compile && Run
Run `make` to compile the simulator and player.
- simulator mode: `./main -s [output file] [config file]`
- player mode: `./main -p [input file] [framerate]`
