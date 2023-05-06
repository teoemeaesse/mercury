#include <GLFW/glfw3.h>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "shader.h"
#include "utils.h"
#include "exceptions.h"


// ----- SHADER -----

Shader::Shader() : 
    program(glCreateProgram())
{}

Shader::~Shader() {
    glDeleteProgram(program);
}

void Shader::use() {
    glUseProgram(program);
}

// compiles the given shader
// @throws ShaderCompilationException
void compile_shader(unsigned int shader) {
    glCompileShader(shader);

    // check for opengl errors
    int result = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if(!result) {
        int length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        char *buffer = (char *) malloc(++length * sizeof(char));
        glGetShaderInfoLog(shader, length, NULL, buffer);
        buffer[length] = '\0';

        std::string message(buffer);
        free(buffer);

        throw ShaderCompilationException(message);
    }
}

// links the given shader program
// @throws ShaderLinkingException
void link_shader(unsigned int program) {
    glLinkProgram(program);

    int result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if(!result) {
        int length = 0;
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, &length);

        char *buffer = (char *) malloc(++length * sizeof(char));
        glGetShaderInfoLog(program, length, &length, buffer);
        buffer[length] = '\0';

        std::string message(buffer);
        free(buffer);

        throw ShaderLinkingException(message);
    }
}



// ----- RENDER SHADER -----

RenderShader::RenderShader(const char *vertex_path, const char *fragment_path) :
    Shader(), 
    vertex_shader(glCreateShader(GL_VERTEX_SHADER)),
    fragment_shader(glCreateShader(GL_FRAGMENT_SHADER)),
    vertex_src(read_file_as_string(vertex_path)),
    fragment_src(read_file_as_string(fragment_path))
{
    const char *c_vertex_src = vertex_src.c_str();
    const char *c_fragment_src = fragment_src.c_str();
    glShaderSource(vertex_shader, 1, &c_vertex_src, NULL);
    glShaderSource(fragment_shader, 1, &c_fragment_src, NULL);
}

RenderShader::~RenderShader() {
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    glDeleteProgram(program);
}

// compiles the full shader
// @throws ShaderCompilationException
void RenderShader::compile() {
    log("Compiling render shader", DEBUG_LOG);

    if (!vertex_src.empty() && !fragment_src.empty()) {
        compile_shader(vertex_shader);
        compile_shader(fragment_shader);
    }

    else throw ShaderCompilationException("Missing shader sources to compile");
}

// attaches the shaders and links the shader program
// @throws ShaderLinkingException
void RenderShader::link() {
    log("Linking render shader", DEBUG_LOG);

    int vertex_compiled, fragment_compiled;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_compiled);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragment_compiled);

    if (vertex_compiled && fragment_compiled){
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glValidateProgram(program);
        link_shader(program);
    }

    else throw ShaderCompilationException("Can't link before compiling");
}



// ----- COMPUTE SHADER -----

ComputeShader::ComputeShader(const char *compute_path, unsigned int invocations[3]) :
    Shader(),
    compute_shader(glCreateShader(GL_COMPUTE_SHADER)),
    compute_src(read_file_as_string(compute_path))
{
    // inject invocation sizes into shader source
    std::string x_loc("#define LOCAL_SIZE_X");
    std::string y_loc("#define LOCAL_SIZE_Y");
    std::string z_loc("#define LOCAL_SIZE_Z");
    insert_after(compute_src, x_loc, " " + std::to_string(invocations[0]));
    insert_after(compute_src, y_loc, " " + std::to_string(invocations[1]));
    insert_after(compute_src, z_loc, " " + std::to_string(invocations[2]));

    const char *c_src = compute_src.c_str(); 
    
    glShaderSource(compute_shader, 1, &c_src, NULL);
}

ComputeShader::~ComputeShader() {
    glDeleteShader(compute_shader);
    glDeleteProgram(program);
}

// compiles the full shader
// @throws ShaderCompilationException
void ComputeShader::compile() {
    log("Compiling compute shader", DEBUG_LOG);

    if (!compute_src.empty()) {
        compile_shader(compute_shader);
    }

    else throw ShaderCompilationException("Missing shader sources to compile");
}

// attaches the shaders and links the shader program
// @throws ShaderLinkingException
void ComputeShader::link() {
    log("Linking compute shader", DEBUG_LOG);

    int compute_compiled;
    glGetShaderiv(compute_shader, GL_COMPILE_STATUS, &compute_compiled);

    if (compute_compiled) {
        glAttachShader(program, compute_shader);
        link_shader(program);
    }

    else throw ShaderCompilationException("Can't link before compiling");
}

// dispatches the compute shader
void ComputeShader::dispatch(unsigned int work_groups[3]) const {
    glDispatchCompute(work_groups[0], work_groups[1], work_groups[2]);
}



// ----- MISC -----

// clear all opengl errors
void gl_clear_errors() {
    unsigned int error;
    while(error = glGetError());
}

// check for opengl errors
void gl_check_error() {
    unsigned int error;
    while((error = glGetError())) {
        log("GL error code: " + error, ERROR_LOG);
    }
}

// log the max work group sizes and invocations for compute shaders
void log_wg_sizes() {
    int invocations[3] = { 0 };
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &invocations[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &invocations[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &invocations[2]);
    
    int work_groups[3] = { 0 };
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &work_groups[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &work_groups[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &work_groups[2]);

    std::stringstream max_invocations;
    max_invocations << "Max invocations: " << invocations[0] << ", " << invocations[1] << ", " << invocations[2];
    log(max_invocations.str(), DEBUG_LOG);

    std::stringstream max_work_groups;
    max_work_groups << "Max work groups: " << work_groups[0] << ", " << work_groups[1] << ", " << work_groups[2];
    log(max_work_groups.str(), DEBUG_LOG);
}