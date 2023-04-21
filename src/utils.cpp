#include <iostream>
#include <ctime>
#include <chrono>
#include <sstream>

#include "utils.h"

#define LOG_FILE "log.txt"


// ----- DEBUG -----

// log useful information to the console / log file
void log(std::string message, LogType type) {
    if (VERBOSE) {
        static bool file_exists = false;

        time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::string time = ctime(&t);
        std::string time_prefix = "[" + time.substr(0, time.length() - 1) + "] ";

        std::string line;

        if (type == DEBUG_LOG) {
            line = time_prefix + "[DEBUG] " + message + "\n";
            std::cout << line;
        }
        else if (type == ERROR_LOG) {
            line = time_prefix + "[ERROR] " + message + "\n";
            std::cerr << line;
        }

        if (LOG_TO_FILE) {
            std::ofstream *log_file = file_exists ? open_file_append(LOG_FILE) : open_file_new(LOG_FILE);
            file_exists = true;
            (*log_file) << line;
            close_file_out(*log_file);
        }
    }
}

// print usage information
void print_usage() {
    std::cout << "Usage: ./main [-v (verbose)] [-f (write log to file)]" << std::endl;
}



// ----- FILE I/O -----

// wrapper for fstream open
std::ifstream *open_file_read(const char *path, bool binary) {
    std::ifstream *file = new std::ifstream;

    if (binary)
        (*file).open(path, std::ios::in | std::ios::binary);
    else
        (*file).open(path, std::ios::in);

    if (!(*file)) {
        log("Could not open file for read " + std::string(path), ERROR_LOG);
        return NULL;
    }

    return file;
}

// wrapper for fstream open
std::ofstream *open_file_new(const char *path, bool binary) {
    std::ofstream *file = new std::ofstream;

    if (binary)
        (*file).open(path, std::ios::out | std::ios::trunc | std::ios::binary);
    else
        (*file).open(path, std::ios::out | std::ios::trunc);

    if (!(*file)) {
        log("Could not open new file " + std::string(path), ERROR_LOG);
        return NULL;
    }

    return file;
}

// wrapper for fstream open
std::ofstream *open_file_append(const char *path, bool binary) {
    std::ofstream *file = new std::ofstream;

    if (binary)
        (*file).open(path, std::ios::out | std::ios::app | std::ios::binary);
    else
        (*file).open(path, std::ios::out | std::ios::app);

    if (!(*file)) {
        log("Could not open file for append " + std::string(path), ERROR_LOG);
        return NULL;
    }

    return file;
}

// wrapper for fstream close
bool close_file_in(std::ifstream &file) {
    file.close();

    if (file.is_open()) {
        log("Could not close file", ERROR_LOG);
        return false;
    }
    delete &file;

    return true;
}

// wrapper for fstream close
bool close_file_out(std::ofstream &file) {
    file.close();

    if (file.is_open()) {
        log("Could not close file", ERROR_LOG);
        return false;
    }
    delete &file;

    return true;
}

// read entire file into a c string
const char *read_file_as_string(const char *path) {
    std::ifstream *file = open_file_read(path);
    if (!file) {
        log("Could not read file " + std::string(path), ERROR_LOG);
        return NULL;
    }

    std::stringstream buffer;
    buffer << file->rdbuf();
    close_file_in(*file);

    std::string str = buffer.str();

    char *c_str = new char[str.length() + 1];
    c_str[str.length()] = '\0';
    str.copy(c_str, str.length() + 1, 0);
    
    return c_str;
}