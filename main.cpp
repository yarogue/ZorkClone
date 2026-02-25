#include <iostream>
#include <string>
#include "types.hpp"
#include "world.hpp"
#include  "commands.hpp"
#include "parser.hpp"

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
    std::cout << state.narrator[MSG_HELP_HINT] << std::endl;
    std::cout << " " << std::endl;
    std::cout << state.narrator[MSG_WELCOME] << std::endl;

    while (state.running == true)
    {
        std::string input = readInput();
        if (hasNumbers(input)) {
            std::cout << "Please enter words only!" << std::endl;
            continue;
        }

        if (input.empty()) {
            std::cout << "> ?" << input<< std::endl;
            continue;
        }
        Command cmd = parseInput(input);

        if (cmd.verb == "quit") {
            std::cout << state.narrator[MSG_GOODBYE] << std::endl;
            QuitCommand(state);
        } else if (cmd.verb == "help") {
            HelpCommand();
        } else if (cmd.verb == "log") {
            LogCommand();
        }else if (cmd.verb == "look") {
            LookCommand(state, cmd.noun);
        }else if (cmd.verb == "scream") {
            ScreamCommand(state, cmd.noun);
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