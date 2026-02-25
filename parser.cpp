#include "parser.hpp"
#include <iostream>
#include <string>
#include "types.hpp"


Command parseInput(const std::string& input)
{
    Command cmd;

    size_t position = input.find(' ');

    if (position == std::string::npos)
    {
        cmd.verb = input;
        cmd.noun = "";
    }
    else
    {
        cmd.verb = input.substr(0, position);
        cmd.noun = input.substr(position + 1);
    }

    return cmd;
}