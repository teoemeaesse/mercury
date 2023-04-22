# mercury
3D N-body particle engine in C++ using OpenGL and GLFW.
The goal of this project is to create a fast, easy to use and fully customizable N-body particle simulator in 3D, using the [**Barnes-Hut algorithm**](http://arborjs.org/docs/barnes-hut).

## System Requirements
To compile and run you need the following:
- A GPU with **OpenGL 4.5** (or higher) support;
- **G++** and [**GLFW 3**](https://stackoverflow.com/questions/17768008/how-to-build-install-glfw-3-and-use-it-in-a-linux-project) installed on your machine.

## Compile && Run
Run `make` to compile the simulator and player.
- player mode: `./mercury [-v (verbose)] [-f (log to file)] [sim file] [config file]`
