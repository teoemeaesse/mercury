#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#include "utils.h"
#include "exceptions.h"
#include "window.h"

bool VERBOSE = false;
bool LOG_TO_FILE = false;

int parse_cli_args(int argc, char *argv[]) {
    int opt;

    // parse command-line arguments
    while((opt = getopt(argc, argv, ":vf")) != -1) {
        switch(opt) {
            case 'v':
                VERBOSE = true;
                break;
            case 'f':
                LOG_TO_FILE = true;
                break;
            default:
                print_usage();
        }
    }

    return 0;
}

void error(int err, const char * description) {
    fputs(description, stderr);
}

int main(int argc, char * argv[]) {
    parse_cli_args(argc, argv);

    Window window(800, 600, 60, true, "Mercury Engine");

    window.start();

    return EXIT_SUCCESS;
}