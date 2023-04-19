#include <iostream>
#include <ctime>
#include <chrono>

#include "utils.h"

using namespace std;

#define LOG_FILE "log.txt"


// ----- DEBUG -----

// log useful information to the console / log file
void log(string message, LogType type) {
    if (VERBOSE) {
        static bool file_exists = false;

        time_t t = chrono::system_clock::to_time_t(chrono::system_clock::now());
        string time = ctime(&t);
        string time_prefix = "[" + time.substr(0, time.length() - 1) + "] ";

        string line;

        if (type == DEBUG_LOG) {
            line = time_prefix + "[DEBUG] " + message + "\n";
            cout << line;
        }
        else if (type == ERROR_LOG) {
            line = time_prefix + "[ERROR] " + message + "\n";
            cerr << line;
        }

        if (LOG_TO_FILE) {
            ofstream *log_file = file_exists ? open_file_append(LOG_FILE) : open_file_new(LOG_FILE);
            file_exists = true;
            (*log_file) << line;
            close_file_out(*log_file);
        }
    }
}

// print usage information
void print_usage() {
    cout << "Usage: ./main [-v (verbose)] [-f (write log to file)]" << endl;
}



// ----- FILE I/O -----

// wrapper for fstream open
ifstream *open_file_read(const char *path, bool binary) {
    ifstream *file = new ifstream;

    if (binary)
        (*file).open(path, ios::in | ios::binary);
    else
        (*file).open(path, ios::in);

    if (!(*file)) {
        log("Could not open file for read " + string(path), ERROR_LOG);
        return NULL;
    }

    return file;
}

// wrapper for fstream open
ofstream *open_file_new(const char *path, bool binary) {
    ofstream *file = new ofstream;

    if (binary)
        (*file).open(path, ios::out | ios::trunc | ios::binary);
    else
        (*file).open(path, ios::out | ios::trunc);

    if (!(*file)) {
        log("Could not open new file " + string(path), ERROR_LOG);
        return NULL;
    }

    return file;
}

// wrapper for fstream open
ofstream *open_file_append(const char *path, bool binary) {
    ofstream *file = new ofstream;

    if (binary)
        (*file).open(path, ios::out | ios::app | ios::binary);
    else
        (*file).open(path, ios::out | ios::app);

    if (!(*file)) {
        log("Could not open file for append " + string(path), ERROR_LOG);
        return NULL;
    }

    return file;
}

// wrapper for fstream close
bool close_file_in(ifstream file) {
    file.close();

    if (file.is_open()) {
        log("Could not close file", ERROR_LOG);
        return false;
    }
    delete &file;

    return true;
}

// wrapper for fstream close
bool close_file_out(ofstream &file) {
    file.close();

    if (file.is_open()) {
        log("Could not close file", ERROR_LOG);
        return false;
    }
    delete &file;

    return true;
}