#include "commands.hpp"
#include <cstdio>
#include <iostream>
#include <string>

void QuitCommand(GameState& state)
{
    std::cout << "Goodbye!" << std::endl;
    state.running = false;
}

void HelpCommand()
{
    std::cout << "Help" << std::endl;
}

void LogCommand()
{
    std::cout << "Log" << std::endl;
}

void LookCommand()
{
    std::cout << "Looking around" << std::endl;
}