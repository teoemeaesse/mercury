#include <GLFW/glfw3.h>

#include "io.h"


// ----- KEYBOARD -----

Keyboard::Keyboard() {
    this->w_down = false;
    this->a_down = false;
    this->s_down = false;
    this->d_down = false;
    this->r_down = false;
    this->f_down = false;
    this->space_down = false;
    this->lshift_down = false;
    this->plus_down = false;
    this->minus_down = false;
}

// handle keyboard input
void Keyboard::on_key(int key, int action) {
    if(action == GLFW_PRESS || action == GLFW_RELEASE) {
        if(key == GLFW_KEY_W)
            this->w_down = action;
        if(key == GLFW_KEY_A)
            this->a_down = action;
        if(key == GLFW_KEY_S)
            this->s_down = action;
        if(key == GLFW_KEY_D)
            this->d_down = action;
        if(key == GLFW_KEY_R)
            this->r_down = action;
        if(key == GLFW_KEY_F)
            this->f_down = action;
        if(key == GLFW_KEY_SPACE)
            this->space_down = action;
        if(key == GLFW_KEY_LEFT_SHIFT)
            this->lshift_down = action;
        if(key == GLFW_KEY_KP_ADD)
            this->plus_down = action;
        if(key == GLFW_KEY_KP_SUBTRACT)
            this->minus_down = action;
    }
}



// ----- MOUSE -----

Mouse::Mouse() {
    this->x = 0;
    this->y = 0;
    this->left_down = false;
}

// handle mouse move input
void Mouse::move(float x, float y, unsigned long frametime) {
    // TODO: rotate camera, comparing new and old mouse position

    this->x = x;
    this->y = y;
}

// handle mouse scroll input
void Mouse::scroll(float y, Camera &camera, unsigned long frametime) {
    Camera::Direction dir = y > 0 ? Camera::Direction::IN : Camera::Direction::OUT;
    camera.zoom(dir, frametime);
}

// handle mouse click input
void Mouse::click(int button, int action) {
    // TODO: handle mouse click input
}