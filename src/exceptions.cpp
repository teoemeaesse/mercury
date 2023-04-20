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