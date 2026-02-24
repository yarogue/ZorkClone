#include <iostream>
#include <string>
#include "types.hpp"
#include "world.hpp"
#include  "commands.hpp"

static std::string readInput()
{
    std::string input;
    std::cout << "> ";
    std::getline(std::cin, input);
    return input;
}

void mainLoop()
{
    GameState state = {};

    state.running = true;
    init_world(&state);
    std::string input;

    // print welcome through narrator
    std::cout << state.narrator[MSG_WELCOME] << std::endl;
    std::cout << state.narrator[MSG_HELP_HINT] << std::endl;

    while (state.running == true)
    {
        std::string input = readInput();
        if (input == "quit" || input == "q") {
            QuitCommand(state);
        } else if (input == "help") {
            HelpCommand();
        } else if (input == "log") {
            LogCommand();
        }else if (input == "look") {
            LookCommand();
        }else if (input.empty()) {
            std::cout << "> ?" << input<< std::endl;
        }else {
            std::cout << "I don't understand that. -> " << input<< std::endl;
        }

    }
}

int main()
{

    // game loop starts here...

    mainLoop();

    return 0;
}

