#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

#include "utils.h"
#include "exceptions.h"
#include "window.h"
#include "particle.h"
#include "octtree.h"
#include "renderer.h"
#include "menu.h"
#include "simulation.pb.h"


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

/*void test_octtree() {
    OctTree tree({vec3(-100.0, -100.0, -100.0), vec3(100.0, 100.0, 100.0)}, 4);
    std::vector<Particle> particles;

    log("----- Testing octtree -----", DEBUG_LOG);

    log("Size of a node: " + std::to_string(sizeof(Node)) + " bytes", DEBUG_LOG);

    log("Created octtree", DEBUG_LOG);

    for (float x = -100.0f; x < 100.0f; x += 10.0)
        for (float y = -100.0f; y < 100.0f; y += 10.0)
            for (float z = -100.0f; z < 100.0f; z += 10.0)
                particles.emplace_back(vec3(x, y, z), vec3(0.0f, 0.0f, 0.0f), 1.0f);
    
    for (auto &particle : particles)
        tree.insert(&particle);


    log("Done inserting " + std::to_string(particles.size()) + " particles into octtree", DEBUG_LOG);

    log(tree.to_string(), DEBUG_LOG);

    log("----- Done testing octtree -----", DEBUG_LOG);
}*/

int main(int argc, char * argv[]) {
    parse_cli_args(argc, argv);

    // test_octtree();

    auto main_menu = build_menu(MenuType::MAIN_MENU);
    main_menu->run();

    Window window(800, 600, 60, true, "Mercury Engine");

    unsigned int invocations[3] = {1, 1, 1};
    ComputeShader compute_shader("shaders/barnes_hut.comp", invocations);

    Renderer renderer("shaders/point.vert", "shaders/point.frag");
    
    window.set_renderer(&renderer);

    window.start(
        [&renderer]() {
            // TODO: update();
        }
    );

    return EXIT_SUCCESS;
}