#include <iostream>

#include "menu.h"


// ----- MENU -----

Menu::Menu(std::string title)
    : title(std::move(title)) {}

// add an element to the menu
Menu& Menu::add_item(std::unique_ptr<MenuItem> item) {
    options.push_back(std::move(item));
    return *this;
}

// draw the menu and display the options
void Menu::render() const {
    std::cout << "\n======== " << title << " ========" << std::endl;
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << (i + 1) << ". ";
        options[i]->render();
    }
    std::cout << "q. Quit" << std::endl;
}

// handle user input
void Menu::run() {
    while (true) {
        render();

        std::string input;
        std::getline(std::cin, input);
        if (input == "q") {
            break;
        }

        size_t input_value;
        try {
            input_value = std::stoul(input);
        } catch (...) {
            std::cout << "Invalid input: " << input << std::endl;
            continue;
        }

        if (input_value == 0 || input_value > options.size()) {
            std::cout << "Option out of bounds: " << input << std::endl;
            continue;
        }

        options[input_value - 1]->run();
    }
}



// ----- OPTION -----

Option::Option(std::string text, std::function<void()> action)
            : text(std::move(text)), action(std::move(action)) {}

// display the descriptive text
void Option::render() const {
    std::cout << text << "\n";
}

// execute an action
void Option::run() {
    action();
}



// ----- PROMPT -----

Prompt::Prompt(std::string display, std::string prompt, std::function<void(const std::string&)> action)
        : display(std::move(display)), prompt(std::move(prompt)), action(std::move(action)) {}

// display the prompting text (i.e. "Enter a value: ")
void Prompt::render() const {
    std::cout << display << std::endl;
}

// read the response and execute an action
void Prompt::run() {
    std::cout << prompt << "> ";
    std::string answer;
    std::getline(std::cin, answer);
    action(answer);
}



// ----- MENU BUILDER -----

// define custom menus
std::unique_ptr<Menu> build_menu(MenuType menu_type) {
    std::unique_ptr<Menu> menu;

    switch (menu_type) {
        case MenuType::MAIN_MENU:
            menu = std::make_unique<Menu>("Main Menu");
            menu->
                add_item(std::make_unique<Prompt>("New simulation", "Enter simulation name", [](const std::string& answer) {
                    std::cout << "Answer was: " << answer << std::endl;
            })).
                add_item(std::make_unique<Option>("Load simulation", []() {
                    auto load_simulation_menu = build_menu(MenuType::LOAD_SIMULATION_MENU);
                    load_simulation_menu->run();
            }));
            break;
            
        case MenuType::LOAD_SIMULATION_MENU:
            menu = std::make_unique<Menu>("Load Simulation");
            menu->
                add_item(std::make_unique<Option>("Load from file", []() {
                    std::cout << "Starting..." << std::endl;
                }))
                .add_item(std::make_unique<Option>("Load from database", []() {
                    std::cout << "Starting..." << std::endl;
                }));
            break;
    }

    return menu;
}