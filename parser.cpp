#include "parser.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include "types.hpp"

std::string toLowerCase(const std::string& input)
{
    std::string s = input;
    for (char & i : s)
        i = tolower(i);
    return s;
}

bool hasNumbers(const std::string& s) {
    for (char c : s) {
        if (c >= '0' && c <= '9')
            return true;
    }
    return false;
}

bool isStopWord(const std::string& word) {

    std::string stopWords []= {
        "at",
        "the",
        "a",
        "an",
        "in",
        "on",
        "to",
        "with",
        "into",
        "from"
    };

    for (const std::string& sw : stopWords) {
        if (word == sw) {
            return true;
        }
    }
    return false;
}

std::string cleanNoun(const std::string& noun) {

    std::stringstream ss(noun);
    std::string word;
    std::string result;

    while (ss>>word) {
        if (!isStopWord(word)) {
            result = word;
        }
    }
    return result;
}

Command parseInput(const std::string& input)
{
    Command cmd;

    std::string lower = toLowerCase(input);
    size_t position = lower.find(' ');

    if (position == std::string::npos)
    {
        cmd.verb = lower;
        cmd.noun = "";
    }
    else
    {
        cmd.verb = lower.substr(0, position);
        cmd.noun = lower.substr(position + 1);
    }

    cmd.noun = cleanNoun(cmd.noun);

    return cmd;
}