#include "exceptions.h"

using namespace std;

ShaderCompilationException::ShaderCompilationException(string message) {
    this->message = "Error compiling shader:\n----- OPENGL ERROR ------\n" + message + "\n----- END OPENGL ERROR ------";
}

const char *ShaderCompilationException::what() const throw() {
    return this->message.c_str();
}


ShaderLinkingException::ShaderLinkingException(string message) {
    this->message = "Error linking shader:\n----- OPENGL ERROR ------\n" + message + "\n----- END OPENGL ERROR ------";
}

const char *ShaderLinkingException::what() const throw() {
    return this->message.c_str();
}


GLFWException::GLFWException(int error, string message) {
    this->message = "GLFW Error code " + to_string(error) + ":\n----- GLFW ERROR ------\n" + message + "\n----- END GLFW ERROR ------";
}

const char *GLFWException::what() const throw() {
    return this->message.c_str();
}