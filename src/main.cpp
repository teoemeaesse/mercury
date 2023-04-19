#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#include "utils.h"

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

    log("Verbose mode: " + string(VERBOSE ? "on" : "off"), DEBUG_LOG);
    log("Verbose mode pila: " + string(VERBOSE ? "on" : "off"), DEBUG_LOG);

    return 0;
}

int main(int argc, char * argv[]) {
    parse_cli_args(argc, argv);

    return EXIT_SUCCESS;
}