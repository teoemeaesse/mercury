#pragma once

#include <GLFW/glfw3.h>

#include "io.h"
#include "camera.h"


class Window {
    private:
        int width;
        int height;
        int framerate;
        bool vsync;
        const char *title;
        GLFWwindow *handle;
        Keyboard keyboard;
        Mouse mouse;
        Camera camera;

    public:
        Window(int width, int height, int framerate, bool vsync, const char *title);
        ~Window();

        // start the main loop
        void start();

        // update the window dimensions after resize and set the viewport
        void handle_resize(int width, int height);

        // handle keyboard input
        void handle_keyboard(int key, int action); 
        
        // handle mouse wheel input
        void handle_scroll(double y);

        // handle mouse position input
        void handle_mouse(double x, double y);

        // handle mouse click input
        void handle_click(int button, int action);
};

// resize callback function
void resize_callback(GLFWwindow *handle, int width, int height);

// keyboard callback function
void keyboard_callback(GLFWwindow *handle, int key, int scancode, int action, int mods);

// mouse wheel callback function
void scroll_callback(GLFWwindow *handle, double x, double y);

// mouse position callback function
void mouse_callback(GLFWwindow *handle, double x, double y);

// click callback function
void click_callback(GLFWwindow *handle, int button, int action, int mods);

// error callback function
void error_callback(int error, const char *description);