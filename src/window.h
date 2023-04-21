#pragma once

#include <GLFW/glfw3.h>

#include "io.h"
#include "camera.h"


class Window {
    private:
        int width;
        int height;
        int framerate;
        unsigned long frametime;
        const char *title;
        GLFWwindow *handle;
        Keyboard keyboard;
        Mouse mouse;
        Camera camera;

    public:
        Window(int width, int height, int framerate, const char *title);
        ~Window();

        // start the main loop
        void start();

        // update the window dimensions after resize and set the viewport
        void resize(int width, int height);

        // zoom the camera
        void zoom(float y);
};

// resize callback function
void resize_callback(GLFWwindow *handle, int width, int height);

// keyboard callback function
void keyboard_callback(GLFWwindow *handle, int key, int scancode, int action, int mods);

// mouse wheel callback function
void scroll_callback(GLFWwindow *handle, double x, double y);

// error callback function
void error_callback(int error, const char *description);