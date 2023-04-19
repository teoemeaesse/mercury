#pragma once

class Shader {
    private:
        unsigned int handle;

    public:
        Shader(const char &src, unsigned int type);
        ~Shader();

}

/* compiles the shader
void compile_shader();

/* Creates a shader program from the given shader source paths and returns a handle to it.
*/
unsigned int new_render_shader(const char * vertex, const char * fragment);

/* Links the given shader program and returns 0 on success or -1 on failure
*/
int link_program(shader_h program);

/* Clear opengl errors
*/
void gl_clear_errors();

/* Check for and print opengl errors
*/
void gl_check_error();

/* Log work group and invocations max sizes for compute shaders
*/
void log_wg_sizes();