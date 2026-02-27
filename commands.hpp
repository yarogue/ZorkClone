#ifndef ZORKCLONE_COMMANDS_HPP
#define ZORKCLONE_COMMANDS_HPP
#pragma once
#include "types.hpp"

///General commands\\\

void QuitCommand(GameState& state);

void HelpCommand();

void LogCommand(GameState& state);

///Gameplay commands\\\

void LookCommand(GameState& state, const std::string& noun);

void ScreamCommand(GameState& state, const std::string& noun);

void SmellCommand(GameState& state, const std::string& noun);

void TouchCommand(GameState& state, const std::string& noun);

void ListenCommand(GameState& state, const std::string& noun);

void InventoryCommand(GameState& state, const std::string& noun);

void ReadCommand(GameState& state, const std::string& noun);

void GoCommand(GameState& state, const std::string& noun);

void ExitDoorCommand(GameState& state, const std::string& noun);

#endif //ZORKCLONE_COMMANDS_HPP