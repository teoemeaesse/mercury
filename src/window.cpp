#include <algorithm>

#include "window.h"
#include "utils.h"
#include "exceptions.h"
#include "shader.h"
#include "renderer.h"


// ----- PUBLIC METHODS -----

// @throws GLFWException
Window::Window(int width, int height, int framerate, const char *title) 
    : keyboard(), mouse(), camera() {
    
    this->width = width;
    this->height = height;
    this->framerate = framerate;
    this->frametime = 1000000 / framerate;
    this->title = title;

    if (!glfwInit())
        throw GLFWException(0, "Failed to initialize GLFW");

    log("GLFW initialized", DEBUG_LOG);

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

    log("Window setup finished", DEBUG_LOG);
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

    log("GLFW context setup", DEBUG_LOG);

    // move into renderer
    // TODO: FBOs for bloom

    try {
        Renderer renderer("shaders/point.vert", "shaders/point.frag");

        // TODO: postfx shaders

        log("Starting up main render loop", DEBUG_LOG);
        
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

            // renderer.render_particles(/* frame data */);

            // TODO: postfx rendering

            glfwSwapBuffers(handle);
            glfwPollEvents();

            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            frametime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
            acc += frametime;
        }
    } catch (ShaderCompilationException &e) {
        log(e.what(), ERROR_LOG);
    }

    log("Shutting down", DEBUG_LOG);
}

// update the window dimensions after resize and set the viewport
void Window::resize(int width, int height) {
    this->width = width;
    this->height = height;

    glViewport(0, 0, width, height);
}

// zoom the camera
void Window::zoom(float y) {
    Direction dir = y > 0 ? Direction::IN : Direction::OUT;
    camera.zoom(dir, frametime);
}



// ----- STATIC CALLBACK FUNCTIONS -----

// resize callback function
void resize_callback(GLFWwindow *handle, int width, int height) {
    Window *window = (Window *) glfwGetWindowUserPointer(handle);
    window->resize(width, std::max(height, 1));
}

// keyboard callback function
void keyboard_callback(GLFWwindow *handle, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(handle, GL_TRUE);
    }
}

// mouse wheel callback function
void scroll_callback(GLFWwindow *handle, double x, double y) {
    Window *window = (Window *) glfwGetWindowUserPointer(handle);
    window->zoom(y);
}

// error callback function
// @throws GLFWException
void error_callback(int error, const char *description) {
    throw GLFWException(error, description);
}