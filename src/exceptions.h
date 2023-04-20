#pragma once

#include <string>

class ShaderCompilationException : public std::exception {
private:
    std::string message;

public:
    ShaderCompilationException(std::string message);

    const char *what() const throw();
};

class ShaderLinkingException : public std::exception {
private:
    std::string message;

public:
    ShaderLinkingException(std::string message);

    const char *what() const throw();
};