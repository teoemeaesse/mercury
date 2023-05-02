#pragma once

#include <unordered_map>

class Shader {
    protected:
        unsigned int program;
        mutable std::unordered_map<const char *, int> uniform_locations;

    public:
        virtual ~Shader();

        // compiles the full shader
        // @throws ShaderCompilationException
        virtual void compile() = 0;

        // attaches the shaders and links the shader program
        // @throws ShaderLinkingException
        virtual void link() = 0;

        // sets a uniform float
        void set_uniform_float(const char *name, const float value) const {
            glUniform1f(get_uniform_location(name), value);
        }

        // sets a uniform float vector
        void set_uniform_vec2(const char *name, const float x, const float y) const {
            glUniform2f(get_uniform_location(name), x, y);
        }

        // sets a uniform 4x4 float matrix
        void set_uniform_mat4(const char *name, const float *value) const {
            glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, value);
        }

        // returns the uniform location for the given name
        // stores the location in a cache for future use
        int get_uniform_location(const char *name) const {
            if (uniform_locations.find(name) == uniform_locations.end())
                uniform_locations[name] = glGetUniformLocation(program, name);

            return uniform_locations[name];
        }

        void use();
};

class RenderShader : public Shader {
    private:
        unsigned int vertex_shader;
        unsigned int fragment_shader;
        const char *vertex_src;
        const char *fragment_src;

    public:
        RenderShader(const char *vertex_path, const char *fragment_path);
        ~RenderShader();

        // compiles the full shader
        // @throws ShaderCompilationException
        void compile();

        // attaches the shaders and links the shader program
        // @throws ShaderLinkingException
        void link();
};

class ComputeShader : public Shader {
    private:
        unsigned int compute_shader;
        const char *compute_src;

    public:
        ComputeShader(const char *compute_path);
        ~ComputeShader();

        // compiles the full shader
        // @throws ShaderCompilationException
        void compile();

        // attaches the shaders and links the shader program
        // @throws ShaderLinkingException
        void link();
};

// clear all opengl errors
void gl_clear_errors();

// check for opengl errors
void gl_check_error();

// log the max work group sizes and invocations for compute shaders
void log_wg_sizes();
