#include <GLFW/glfw3.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "shader.h"

shader_h compile_shader(const char * src, unsigned int type) {
    shader_h id = glCreateShader(type);
    
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(!result) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char * message = (char *) malloc(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        LOG(message);
        free(message);
        
        glDeleteShader(id);

        ERROR(ERR_SHADER_COMPILE(type), 0);
    }

    return id;
}

shader_h new_render_shader(const char * vertex, const char * fragment) {
    char * v_src = read_file_as_string(vertex),
         * f_src = read_file_as_string(fragment);

    shader_h program = glCreateProgram();
    shader_h v_shader = compile_shader(v_src, GL_VERTEX_SHADER);
    shader_h f_shader = compile_shader(f_src, GL_FRAGMENT_SHADER);

    glAttachShader(program, v_shader);
    glAttachShader(program, f_shader);
    glValidateProgram(program);

    glDeleteShader(v_shader);
    glDeleteShader(f_shader);

    return program;
}

int link_program(shader_h program) {
    glLinkProgram(program);

    int result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if(!result) {
        LOG(ERR_SHADER_LINK);

        int length;
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, &length);

        char * message = (char *) malloc(length * sizeof(char));
        glGetShaderInfoLog(program, length, &length, message);
        LOG(message);
        free(message);

        return -1;
    }

    return 0;
}

void gl_clear_errors() {
    unsigned int error;
    while(error = glGetError());
}

void gl_check_error() {
    unsigned int error;
    while((error = glGetError())) {
        LOG_ERROR_GL(error);
    }
}

void log_wg_sizes() {
    int invocations[3] = { 0 };
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &invocations[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &invocations[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &invocations[2]);
    
    int work_groups[3] = { 0 };
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &work_groups[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &work_groups[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &work_groups[2]);

    LOG_COMPUTE_MAX(invocations, work_groups);
}