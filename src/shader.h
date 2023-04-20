#pragma once

class Shader {
    protected:
        unsigned int program;

    public:
        virtual ~Shader();

        // compiles the full shader
        // @throws ShaderCompilationException
        virtual void compile() = 0;

        // attaches the shaders and links the shader program
        // @throws ShaderLinkingException
        virtual void link() = 0;
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

//unsigned int new_render_shader(const char vertex, const char * fragment);

/* Clear opengl errors
void gl_clear_errors();

/ Check for and print opengl errors
void gl_check_error();

/ Log work group and invocations max sizes for compute shaders
void log_wg_sizes();*/
