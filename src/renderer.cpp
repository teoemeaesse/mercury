#include <GLFW/glfw3.h>

#include "renderer.h"
#include "utils.h"


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

void VBO::set_data(size_t size, void *data, unsigned int usage) {
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}



// ----- VBO LAYOUT -----

Layout::Layout() {
    layout_elements = std::vector<LayoutElement>();
}

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
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.get_stride(), (const void *) offset);
        offset += element.count * Layout::type_size(element.type);
    }

    this->unbind();
}



// ----- RENDERER -----

Renderer::Renderer() 
    : particle_vbo(), particle_vao(), camera() {
    
    render_shader = nullptr;
}

Renderer::Renderer(const char *vertex_path, const char *fragment_path)
    : particle_vbo(), particle_vao() {

    render_shader = new RenderShader(vertex_path, fragment_path);
    render_shader->compile();
}

Renderer::~Renderer() {
    if (render_shader != nullptr)
        delete render_shader;
}


// update all renderer information
void Renderer::update(Keyboard &keyboard, Mouse &mouse, float frametime) {
    camera.update(keyboard, mouse, frametime);
}

// draws all the particles in a given frame
void Renderer::render(int target_width, int target_height) {
    if (!ready())
        return;

    Layout particle_layout;
    
    // (x, y, z)
    particle_layout.push<float>(3);
    // (vx, vy, vz)
    //particle_layout.push<float>(3);
    // (mass)
    // particle_layout.push<float>(1);
    particle_vao.set_layout(particle_layout);

    render_shader->use();

    particle_vbo.bind();
    particle_vao.bind();

    // TODO: draw the particles
    
    /* Render particles */
    render_shader->set_uniform_vec2("window", target_width, target_height);

    const mat4 u_view = camera.view_matrix();
    render_shader->set_uniform_mat4("view", &u_view[0][0]);

    const mat4 u_perspective = camera.perspective_matrix(target_width, target_height);
    render_shader->set_uniform_mat4("perspective", &u_perspective[0][0]);

    //particle_vbo.set_data(size, data, GL_DYNAMIC_DRAW);
    //glDrawArrays(GL_POINTS, 0, sim->settings->n);

    particle_vao.unbind();
}

// sets the render shader
void Renderer::set_render_shader(RenderShader *render_shader) {
    if (this->render_shader != nullptr)
        delete this->render_shader;
    
    this->render_shader = render_shader;
}

// sets the render shader
void Renderer::set_render_shader(const char *vertex_path, const char *fragment_path) {
    if (this->render_shader != nullptr)
        delete this->render_shader;
        
    this->render_shader = new RenderShader(vertex_path, fragment_path);
}