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
    this->x_acc = 0;
    this->y_acc = 0;
    this->scroll_acc = 0;
    this->sensitivity = 25;
    this->left_down = false;
}

// handle mouse move input
void Mouse::on_move(float x, float y) {
    if (left_down) {
        this->x_acc += (x - this->x) * sensitivity;
        this->y_acc += (y - this->y) * sensitivity;
    }
    this->x = x;
    this->y = y;
}

// handle mouse scroll input
void Mouse::on_scroll(float y) {
    scroll_acc += y;
}

// handle mouse click input
void Mouse::on_click(int button, int action) {
    if(action == GLFW_PRESS || action == GLFW_RELEASE)
        if(button == GLFW_MOUSE_BUTTON_LEFT)
            this->left_down = action;
}

// get and clear the accumulated x mouse movement
float Mouse::consume_x_acc() {
    float x = this->x_acc;
    this->x_acc = 0;
    return x;
}

// get and clear the accumulated y mouse movement
float Mouse::consume_y_acc() {
    float y = this->y_acc;
    this->y_acc = 0;
    return y;
}

// get and clear the accumulated mouse scroll
float Mouse::consume_scroll_acc() {
    float scroll = this->scroll_acc;
    this->scroll_acc = 0;
    return scroll;
}