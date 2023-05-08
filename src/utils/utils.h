#pragma once

#include <string>
#include <fstream>

extern bool VERBOSE;
extern bool LOG_TO_FILE;

enum LogType {
    DEBUG_LOG,  // log to stdout only
    ERROR_LOG   // log to stderr only
};


// ----- DEBUG -----

// log useful information to the console / log file
void log(std::string message, LogType type);

// print usage information
void print_usage();



// ----- FILE I/O -----

// wrapper for open
std::ifstream *open_file_read(const char *path, bool binary = false);

// wrapper for open
std::ofstream *open_file_new(const char *path, bool binary = false);

// wrapper for open
std::ofstream *open_file_append(const char *path, bool binary = false);

// wrapper for close
bool close_file_in(std::ifstream &file);

// wrapper for close
bool close_file_out(std::ofstream &file);

// read entire file into a c string
const std::string read_file_as_string(const char *path);

// insert a string directly after a given expression in a string
void insert_after(std::string &original, const std::string &after, const std::string &piece);