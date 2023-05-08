#include <GLFW/glfw3.h>

#include "vbo.h"

// ----- VBO -----

VBO::VBO() {
    glGenBuffers(1, &vbo);
}

VBO::~VBO() {
    glDeleteBuffers(1, &vbo);
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::set_data(unsigned long size, void *data, unsigned int usage) {
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}