#pragma once

#include <vector>
#include <string>

#include "shader.h"

class VBO {
    private:
        unsigned int vbo;

    public:
        VBO();
        ~VBO();

        // binds the vbo
        void bind();

        // unbinds the vbo
        void unbind();

        // load vertex data
        void set_data(size_t size, void *data, unsigned int usage);
};

class Layout {
    struct LayoutElement {
        unsigned int count;
        unsigned int normalized;
        unsigned int type;
    };
    
    private:
        std::vector<LayoutElement> layout_elements;
        unsigned int stride;

    public:
        Layout();

        // adds a new element layout to the vbo
        template <typename T>
        void push(unsigned int count);

        // gets the list of layout elements
        std::vector<LayoutElement> get_layout_elements() const { return layout_elements; }

        // gets the stride
        unsigned int get_stride() const { return stride; }

        // sizeof(type)
        static unsigned int type_size(unsigned int type) {
            switch (type) {
                case GL_FLOAT: return sizeof(float);
                case GL_UNSIGNED_INT: return sizeof(unsigned int);
                case GL_UNSIGNED_BYTE: return sizeof(unsigned char);
            }
            return 0;
        }
};

class VAO {
    private:
        unsigned int vao;

    public:
        VAO();
        ~VAO();

        // binds the vao
        void bind();

        // unbinds the vao
        void unbind();

        // sets a layout for this vao
        void set_layout(Layout &layout);
};

class Renderer {
    private:
        RenderShader *render_shader;
        VBO particle_vbo;
        VAO particle_vao;

    public:
        Renderer();
        Renderer(const char *vertex_path, const char *fragment_path);
        ~Renderer();

        // checks if the renderer is ready to draw a frame
        bool ready() const { return render_shader != nullptr; }

        // draws all the particles in a given frame
        void render_particles(/* frame data */);

        // sets the render shader
        void set_render_shader(RenderShader *render_shader);
        void set_render_shader(const char *vertex_path, const char *fragment_path);
};