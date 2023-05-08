#include <GLFW/glfw3.h>

#include "vao.h"


// ----- LAYOUT -----

Layout::Layout() :
    layout_elements(std::vector<LayoutElement>())
{}

// adds a new element layout to the vbo
template<>
void Layout::push<float>(unsigned int count) {
    layout_elements.push_back({count, GL_FALSE, GL_FLOAT});
    stride += count * Layout::type_size(GL_FLOAT);
}


// ----- VAO -----

VAO::VAO() {
    glGenVertexArrays(1, &vao);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &vao);
}

// binds the vao -- must be called before every frame
void VAO::bind() {
    glBindVertexArray(vao);
}

// unbinds the vao
void VAO::unbind() {
    glBindVertexArray(0);
}

// sets a layout for this vao
void VAO::set_layout(Layout &layout) {
    this->bind();

    unsigned int offset = 0;
    for (unsigned int i = 0; i < layout.get_layout_elements().size(); i++) {
        auto element = layout.get_layout_elements()[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.get_stride(), reinterpret_cast<const void *>(static_cast<uintptr_t>(offset)));
        offset += element.count * Layout::type_size(element.type);
    }

    this->unbind();
}