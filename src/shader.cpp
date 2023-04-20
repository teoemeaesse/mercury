#include <GLFW/glfw3.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

#include "shader.h"
#include "utils.h"
#include "exceptions.h"

// ----- SHADER -----

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
    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if(!result) {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        char *buffer = (char *) malloc(length * sizeof(char));
        glGetShaderInfoLog(shader, length, NULL, buffer);

        string message(buffer);
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
        int length;
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, &length);

        char *buffer = (char *) malloc(length * sizeof(char));
        glGetShaderInfoLog(program, length, &length, buffer);
        string message(buffer);
        free(buffer);

        throw ShaderLinkingException(message);
    }
}



// ----- RENDER SHADER -----

RenderShader::RenderShader(const char *vertex_path, const char *fragment_path) {
    program = glCreateProgram();
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    vertex_src = read_file_as_string(vertex_path);
    fragment_src = read_file_as_string(fragment_path);

    glShaderSource(vertex_shader, 1, &vertex_src, NULL);
    glShaderSource(fragment_shader, 1, &fragment_src, NULL);
}

RenderShader::~RenderShader() {
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    glDeleteProgram(program);
    delete[] vertex_src;
    delete[] fragment_src;
}

// compiles the full shader
// @throws ShaderCompilationException
void RenderShader::compile() {
    if (vertex_src && fragment_src) {
        compile_shader(vertex_shader);
        compile_shader(fragment_shader);
    }

    else throw ShaderCompilationException("Missing shader sources to compile");
}

// attaches the shaders and links the shader program
// @throws ShaderLinkingException
void RenderShader::link() {
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

ComputeShader::ComputeShader(const char *compute_path) {
    compute_shader = glCreateShader(GL_COMPUTE_SHADER);
    program = glCreateProgram();

    compute_src = read_file_as_string(compute_path);

    glShaderSource(compute_shader, 1, &compute_src, NULL);
}

ComputeShader::~ComputeShader() {
    glDeleteShader(compute_shader);
    glDeleteProgram(program);
    delete[] compute_src;
}

// compiles the full shader
// @throws ShaderCompilationException
void ComputeShader::compile() {
    if (compute_src) {
        compile_shader(compute_shader);
    }

    else throw ShaderCompilationException("Missing shader sources to compile");
}

// attaches the shaders and links the shader program
// @throws ShaderLinkingException
void ComputeShader::link() {
    int compute_compiled;
    glGetShaderiv(compute_shader, GL_COMPILE_STATUS, &compute_compiled);

    if (compute_compiled) {
        glAttachShader(program, compute_shader);
        link_shader(program);
    }

    else throw ShaderCompilationException("Can't link before compiling");
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