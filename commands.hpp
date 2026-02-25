#ifndef ZORKCLONE_COMMANDS_HPP
#define ZORKCLONE_COMMANDS_HPP
#pragma once
#include "types.hpp"

///General commands\\\

void QuitCommand(GameState& state);

void HelpCommand();

void LogCommand();

///Gameplay commands\\\

void LookCommand(GameState& state, const std::string& noun);

void ScreamCommand(GameState& state, const std::string& noun);

#endif //ZORKCLONE_COMMANDS_HPP