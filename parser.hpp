#ifndef ZORKCLONE_PARSER_HPP
#define ZORKCLONE_PARSER_HPP
#pragma once
#include <string>
#include "types.hpp"

std::string toLowerCase(const std::string& input);

bool hasNumbers(const std::string& s);

bool isStopWord(const std::string& word);

std::string cleanNoun(const std::string& noun);

Command parseInput(const std::string& input);

#endif //ZORKCLONE_PARSER_HPP