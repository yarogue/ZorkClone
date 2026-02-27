#include "commands.hpp"
#include <iostream>
#include <string>

void QuitCommand(GameState& state)
{
    state.running = false;
}

void HelpCommand()
{
    std::cout << "Help" << std::endl;

}

void LogCommand(GameState& state)
{
    std::cout << "=== Command Log ===" << std::endl;
    for (int i = 0; i < state.logCount; i++) {
        std::cout << "[" << i << "] " << state.commandLog[i] << std::endl;
    }
}

void LookCommand(GameState& state, const std::string& noun)
{
    Room& room = state.rooms[state.player.currentRoom];

    if (noun.empty() || noun == "around") {
        // print room name
        std::cout << "=== " << room.name << " ===" << std::endl;
        // print room description
        std::cout << room.description << std::endl;
        // print exits
        std::cout << "Exits:";
        for (int i = 0; i < room.exitCount; i++) {
            std::cout << " " << room.exits[i].direction << std::endl;
        }
    }
    /*
        else → look at something specific:
        {
            // later: search for item matching noun
            // for now just print:
            std::cout << "You don't see '" << noun << "' here." << std::endl;
        }
     */
}

void SmellCommand(GameState& state, const std::string& noun)
{

}

void TouchCommand(GameState& state, const std::string& noun)
{

}

void ListenCommand(GameState& state, const std::string& noun)
{

}

void ScreamCommand(GameState& state, const std::string& noun)
{
    std::cout << "AAAAAAARGGHHh!!!" << std::endl;
}