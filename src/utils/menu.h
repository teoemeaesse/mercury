#pragma once

#include <string>
#include <vector>
#include <functional>
#include <memory>


enum class MenuType {
    MAIN_MENU,
    LOAD_SIMULATION_MENU,
};



class MenuItem {
    public:
        // draw the menu item
        virtual void render() const = 0;
        
        // execute the menu item
        virtual void run() = 0;
};



class Menu : public MenuItem {
    private:
        std::string title;
        std::vector<std::unique_ptr<MenuItem>> options;

    public:
        explicit Menu(std::string title);
        
        // add an element to the menu
        Menu& add_item(std::unique_ptr<MenuItem> item);

        // draw the menu and display the options
        void render() const override;

        // handle user input
        void run() override;
};



class Option : public MenuItem {
    private:
        std::string text;
        std::function<void()> action;

    public:
        Option(std::string text, std::function<void()> action);

        // display the descriptive text
        void render() const override;

        // execute an action
        void run() override;
};



class Prompt : public MenuItem {
    private:
        std::string display;
        std::string prompt;
        std::function<void(const std::string&)> action;

    public:
        Prompt(std::string display, std::string prompt, std::function<void(const std::string&)> action);

        // display the prompting text (i.e. "Enter a value: ")
        void render() const override;

        // read the response and execute an action
        void run() override;
};


// define custom menus
std::unique_ptr<Menu> build_menu(MenuType menu_type);