#include <algorithm>

#include "window.h"
#include "utils.h"
#include "exceptions.h"
#include "shader.h"
#include "renderer.h"


// ----- PUBLIC METHODS -----

// @throws GLFWException
Window::Window(int width, int height, int framerate, bool vsync, const char *title) 
    : keyboard(), mouse(), camera() {
    
    this->width = width;
    this->height = height;
    this->framerate = framerate;
    this->vsync = vsync;
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
    glfwSetCursorPosCallback(handle, mouse_callback);
    glfwSetMouseButtonCallback(handle, click_callback);
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
    glfwSwapInterval(vsync);

    log("GLFW context setup", DEBUG_LOG);

    // move into renderer
    // TODO: FBOs for bloom

    try {
        Renderer renderer("shaders/point.vert", "shaders/point.frag");

        // TODO: postfx shaders

        log("Starting up main render loop", DEBUG_LOG);
        
        // render loop
        uint64_t delta = 1000000 / framerate,
                 acc = 0, frametime = 0;;
        struct timespec start, end;
        while(!glfwWindowShouldClose(handle)) {
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);

            while(acc >= delta) {
                // TODO: update simulation
                acc -= delta;
            }

            // update the camera
            //camera.update(keyboard, mouse, frametime);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
void Window::handle_resize(int width, int height) {
    this->width = width;
    this->height = height;

    glViewport(0, 0, width, height);
}

// handle keyboard input
void Window::handle_keyboard(int key, int action) {
    keyboard.on_key(key, action);
}

// handle mouse wheel input
void Window::handle_scroll(double y) {
    mouse.on_scroll(y);
}

// handle mouse position input
void Window::handle_mouse(double x, double y) {
    mouse.on_move(x, y);
}

// handle mouse click input
void Window::handle_click(int button, int action) {
    mouse.on_click(button, action);
}



// ----- STATIC CALLBACK FUNCTIONS -----

// resize callback function
void resize_callback(GLFWwindow *handle, int width, int height) {
    Window *window = (Window *) glfwGetWindowUserPointer(handle);
    window->handle_resize(width, std::max(height, 1));
}

// keyboard callback function
void keyboard_callback(GLFWwindow *handle, int key, int scancode, int action, int mods) {
    Window *window = (Window *) glfwGetWindowUserPointer(handle);
    window->handle_keyboard(key, action);

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(handle, GL_TRUE);
    }
}

// mouse wheel callback function
void scroll_callback(GLFWwindow *handle, double x, double y) {
    Window *window = (Window *) glfwGetWindowUserPointer(handle);
    window->handle_scroll(y);
}

// mouse position callback function
void mouse_callback(GLFWwindow *handle, double x, double y) {
    Window *window = (Window *) glfwGetWindowUserPointer(handle);
    window->handle_mouse(x, y);
}

// click callback function
void click_callback(GLFWwindow *handle, int button, int action, int mods) {
    Window *window = (Window *) glfwGetWindowUserPointer(handle);
    window->handle_click(button, action);
}

// error callback function
// @throws GLFWException
void error_callback(int error, const char *description) {
    throw GLFWException(error, description);
}