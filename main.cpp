#include "commands.hpp"
#include "log.hpp"
#include "parser.hpp"
#include "types.hpp"
#include "world.hpp"
#include <iostream>
#include <string>

static std::string readInput() {
  std::string input;
  std::cout << "> ";
  std::getline(std::cin, input);
  return input;
}

void mainLoop() {
  GameState state = {};

  state.running = true;
  init_world(&state);

  std::cout << state.narrator[MSG_HELP_HINT] << std::endl;
  std::cout << " " << std::endl;
  std::cout << state.narrator[MSG_WELCOME] << std::endl;

  do {
    std::string input = readInput();
    if (input.empty()) {
      std::cout << "> ?" << input << std::endl;
      continue;
    }
    Command cmd = parseInput(input);
    addToLog(state, input);

    if (cmd.verb == "quit") {
      std::cout << state.narrator[MSG_GOODBYE] << std::endl;
      QuitCommand(state);
    } else if (cmd.verb == "help") {
      HelpCommand(state);
    } else if (cmd.verb == "commands") {
      CommandsList();
    } else if (cmd.verb == "log") {
      LogCommand(state);
    } else if (cmd.verb == "location" || cmd.verb == "position" ||
               cmd.verb == "map") {
      LocationCommand(state);
    } else if (cmd.verb == "inventory") {
      InventoryCommand(state, cmd.noun);
    } else if (cmd.verb == "look") {
      LookCommand(state, cmd.noun);
    } else if (cmd.verb == "go" || cmd.verb == "walk" || cmd.verb == "move") {
      GoCommand(state, cmd.noun);
    } else if (cmd.verb == "exit" || cmd.verb == "push" || cmd.verb == "open") {
      ExitDoorCommand(state, cmd.noun);
    } else if (cmd.verb == "read") {
      ReadCommand(state, cmd.noun);
    } else if (cmd.verb == "scream") {
      ScreamCommand(state, cmd.noun);
    } else if (cmd.verb == "kick") {
      KickCommand(state, cmd.noun);
    } else if (cmd.verb == "take" || cmd.verb == "grab" || cmd.verb == "pick") {
      TakeCommand(state, cmd.noun);
    } else if (cmd.verb == "drop") {
      DropCommand(state, cmd.noun);
    } else if (cmd.verb == "turn") {
      Turn(state, cmd.noun);
    } else if (cmd.verb == "draw" || cmd.verb == "play") {
      DrawCommand(state, cmd.noun);
    } else {
      std::cout << "I don't understand that. -> " << input << std::endl;
    }
  } while (state.running == true);
}

int main() {
  // game loop starts here...
  mainLoop();
  return 0;
}