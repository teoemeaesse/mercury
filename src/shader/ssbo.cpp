#include <GLFW/glfw3.h>

#include "ssbo.h"


SSBO::SSBO() {
    glGenBuffers(1, &ssbo);
}

SSBO::~SSBO() {
    glDeleteBuffers(1, &ssbo);
}

// binds the ssbo
void SSBO::bind(unsigned int binding_point) {
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding_point, ssbo);
}

// unbinds the ssbo
void SSBO::unbind() {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

// writes data to the ssbo
void SSBO::set_data(unsigned long size, void *data, unsigned int usage) {
    glNamedBufferData(ssbo, size, data, usage);
}

// reads all the data from the ssbo
void SSBO::get_data(unsigned long size, void *data) {
    glGetNamedBufferSubData(ssbo, 0, size, data);
}