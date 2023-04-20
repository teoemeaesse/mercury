#pragma once

#include <string>
#include <fstream>

extern bool VERBOSE;
extern bool LOG_TO_FILE;

enum LogType {
    DEBUG_LOG,  // log to stdout only
    ERROR_LOG   // log to stderr only
};

using namespace std;


// ----- DEBUG -----

// log useful information to the console / log file
void log(string message, LogType type);

// print usage information
void print_usage();


// ----- FILE I/O -----

// wrapper for open
ifstream *open_file_read(const char *path, bool binary = false);

// wrapper for open
ofstream *open_file_new(const char *path, bool binary = false);

// wrapper for open
ofstream *open_file_append(const char *path, bool binary = false);

// wrapper for close
bool close_file_in(ifstream &file);

// wrapper for close
bool close_file_out(ofstream &file);

// read entire file into a std::string
const char *read_file_as_string(const char *path);