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