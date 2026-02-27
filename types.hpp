#ifndef ZORKCLONE_TYPES_HPP
#define ZORKCLONE_TYPES_HPP
#pragma once
#include <string>
#include <iostream>

/// Narrator's enum \\\

enum NarratorMsg
{
    MSG_WELCOME,
    MSG_HELP_HINT,
    MSG_GOODBYE,
    MSG_COUNT
};

/// ID types \\\

using ItemID = int;
using RoomID = int;

static constexpr RoomID ROOM_NONE  = -1;
static constexpr ItemID ITEM_NONE  = -1;
static constexpr RoomID INVENTORY  = -2;

static constexpr int MAX_ROOMS      = 64;
static constexpr int MAX_ITEMS      = 128;
static constexpr int MAX_EXITS      = 6;

static constexpr int MAX_LOG        =12;

/// Structs \\\

struct Command
{
    std::string verb;
    std::string noun;
};

struct Item
{
    ItemID      id;

    std::string name;
    std::string description;
    std::string store;
    std::string smell;
    std::string listen;
    std::string touch;
    std::string consume;
    std::string read;
    std::string observe;

    RoomID      location;

    bool        canPickUp;
    bool        isConsumable;

};

struct Player
{
    RoomID      currentRoom;
};

struct Exit
{
    RoomID      destination;

    std::string direction;
    std::string requiredItem;
    bool        isLocked;
};

struct Room
{
    RoomID      id;

    std::string name;
    std::string description;
    std::string smell;
    std::string listen;

    Exit        exits[MAX_EXITS];

    int         exitCount;
};

struct GameState
{
    Player      player;

    Room        rooms[MAX_ROOMS];
    Item        items[MAX_ITEMS];

    std::string narrator[MSG_COUNT];
    std::string commandLog[MAX_LOG];

    int         logCount;
    int         roomCount;
    int         itemCount;

    bool        running;
};

#endif //ZORKCLONE_TYPES_HPP