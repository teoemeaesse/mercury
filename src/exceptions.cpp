#include "exceptions.h"

ShaderCompilationException::ShaderCompilationException(std::string message) {
    this->message = "Error compiling shader:\n----- OPENGL ERROR ------\n" + message + "\n----- END OPENGL ERROR ------";
}

const char *ShaderCompilationException::what() const throw() {
    return this->message.c_str();
}


ShaderLinkingException::ShaderLinkingException(std::string message) {
    this->message = "Error linking shader:\n----- OPENGL ERROR ------\n" + message + "\n----- END OPENGL ERROR ------";
}

const char *ShaderLinkingException::what() const throw() {
    return this->message.c_str();
}


GLFWException::GLFWException(int error, std::string message) {
    this->message = "GLFW Error code " + std::to_string(error) + ":\n----- GLFW ERROR ------\n" + message + "\n----- END GLFW ERROR ------";
}

const char *GLFWException::what() const throw() {
    return this->message.c_str();
}