#ifndef ZORKCLONE_TYPES_HPP
#define ZORKCLONE_TYPES_HPP
#pragma once
#include <iostream>
#include <string>

/// Narrator's enum \\\

enum NarratorMsg { MSG_WELCOME, MSG_HELP_HINT, MSG_GOODBYE, MSG_COUNT };

enum Position {
  POS_FRONT_LEFT,
  POS_FRONT,
  POS_FRONT_RIGHT, // 0, 1, 2 = top row
  POS_LEFT,
  POS_CENTER,
  POS_RIGHT, // 3, 4, 5 = middle
  POS_BACK_LEFT,
  POS_BACK,
  POS_BACK_RIGHT, // 6, 7, 8 = bottom row
  POS_COUNT
};

enum Direction {
  DIR_NORTH, // towards the exit door (front wall) && default
  DIR_SOUTH, // towards the back wall
  DIR_EAST,  // right wall
  DIR_WEST,  // left wall
  DIR_UP,    // ceiling
  DIR_DOWN,  // floor
  DIR_COUNT
};

/// ID types \\\

using ItemID = int;
using RoomID = int;

static constexpr RoomID ROOM_NONE = -1;
static constexpr ItemID ITEM_NONE = -1;
static constexpr RoomID INVENTORY = -2;

static constexpr int MAX_ROOMS = 64;
static constexpr int MAX_ITEMS = 128;
static constexpr int MAX_EXITS = 6;

static constexpr int MAX_LOG = 12;
static constexpr int MAX_LOOPS = 8;

/// Structs \\\

struct Command {
  std::string verb;
  std::string noun;
};

struct Item {
  ItemID id;

  std::string name;
  std::string description;
  std::string store;
  std::string smell;
  std::string listen;
  std::string touch;
  std::string consume;
  std::string read;
  std::string observe;

  RoomID location;

  bool canPickUp;
  bool isConsumable;
};

struct Player {
  RoomID currentRoom;
  Position position;
  Direction direction;
};

struct Exit {
  RoomID destination;
  std::string direction;
  std::string requiredItem;
  bool isLocked;
};

struct Room {
  RoomID id;

  std::string name;
  std::string description;
  std::string smell;
  std::string listen;

  Exit exits[MAX_EXITS];

  int exitCount;
};

struct GameState {
  Player player;

  Room rooms[MAX_ROOMS];
  Item items[MAX_ITEMS];

  std::string narrator[MSG_COUNT];
  std::string commandLog[MAX_LOG];

  // TODO: Loop descriptions — change per loop
  // std::string roomDesc[MAX_LOOPS];
  // std::string roomSmell[MAX_LOOPS];
  // std::string roomListen[MAX_LOOPS];

  int logCount;
  int roomCount;
  int itemCount;
  int loopCount;   // how many times player went through the door
  int actionCount; // total actions (for final score)

  bool running;
  bool escaped;            // true when player wins
  bool chairBroken;        // true after player kicks the chair
  bool chairIsWooden;      // false after entering new room post-kick
  bool entityPresent;      // true when entity is lurking in the room
  Position entityPosition; // grid cell where entity stands

  // Tic-tac-toe
  int tttBoard[9];      // 0=empty, 1=X(player), 2=O(entity)
  bool tttPlayerMoved;  // player made a move this loop
  bool tttPlayerWon;    // player won the game
  int tttEntityWonLoop; // loopCount when entity won (-1 = hasn't)
};

#endif // ZORKCLONE_TYPES_HPP