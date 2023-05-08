#pragma once

#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "camera.h"


class Renderer {
    private:
        RenderShader *render_shader;
        VBO particle_vbo;
        VAO particle_vao;
        Camera camera;

    public:
        Renderer();
        Renderer(const char *vertex_path, const char *fragment_path);
        ~Renderer();

        // checks if the renderer is ready to draw a frame
        bool ready() const { return render_shader; }

        // update all renderer information
        void update(Keyboard &keyboard, Mouse &mouse, float frametime);

        // draws all the particles in a given frame
        void render(int target_width, int target_height);

        // configure the renderer
        void set_render_shader(RenderShader *render_shader);
        void set_render_shader(const char *vertex_path, const char *fragment_path);

        Camera &get_camera() { return camera; }
};