#include <algorithm>

#include "window.h"
#include "utils.h"
#include "exceptions.h"
#include "shader.h"


// ----- PUBLIC METHODS -----

Window::Window(int width, int height, int framerate, const char *title) {
    this->width = width;
    this->height = height;
    this->framerate = framerate;
    this->title = title;

    if (!glfwInit())
        throw GLFWException(0, "Failed to initialize GLFW");

    // set the window hints - we want a 4.4 core profile
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, true);

    handle = glfwCreateWindow(width, height, title, NULL, NULL);
    if(handle == NULL) {
        glfwTerminate();
        throw GLFWException(0, "Failed to initialize create GLFW window");
    }

    // set all the callbacks
    glfwSetWindowSizeCallback(handle, resize_callback);
    glfwSetKeyCallback(handle, keyboard_callback);
    glfwSetScrollCallback(handle, scroll_callback);
    glfwSetErrorCallback(error_callback);

    // set the user pointer to this window
    glfwSetWindowUserPointer(handle, this);
}

Window::~Window() {
    glfwDestroyWindow(handle);
    glfwTerminate();
}

// start the main loop
void Window::start() {
    glfwMakeContextCurrent(handle);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glfwSwapInterval(0);

    // move into renderer
    // TODO: VAOs, VBOs, FBOs, etc.

    RenderShader shader("shaders/point.vert", "shaders/point.frag");
    shader.compile();
    shader.link();
    shader.use();

    // TODO: postfx shaders



    // render loop
    uint64_t delta = 1000000 / framerate,
             acc = 0;
    struct timespec start, end;
    while(!glfwWindowShouldClose(handle)) {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);

        while(acc >= delta) {
            // TODO: update simulation
            acc -= delta;
        }

        //render(point_shader, sim);

        // TODO: postfx rendering

        glfwSwapBuffers(handle);
        glfwPollEvents();

        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        acc += (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    }
}

// update the window dimensions after resize and set the viewport
void Window::resize(int width, int height) {
    this->width = width;
    this->height = height;

    glViewport(0, 0, width, height);
}



// ----- STATIC CALLBACK FUNCTIONS -----

// resize callback function
void resize_callback(GLFWwindow *handle, int width, int height) {
    Window *window = (Window *) glfwGetWindowUserPointer(handle);
    window->resize(width, std::max(height, 1));
}

// keyboard callback function
void keyboard_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

// mouse wheel callback function
void scroll_callback(GLFWwindow * window, double x, double y) {
    // TODO
}

// error callback function
void error_callback(int error, const char *description) {
    throw GLFWException(error, description);
}