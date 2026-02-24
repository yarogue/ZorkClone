#ifndef ZORKCLONE_TYPES_HPP
#define ZORKCLONE_TYPES_HPP
#pragma once
#include <string>
#include <cstdio>
#include <cstring>

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

/// Structs \\\

struct Item
{
    ItemID      id;

    std::string name;
    std::string description;

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
    std::string direction;
    RoomID      destination;
    std::string requiredItem;
    bool        isLocked;
};

struct Room
{
    RoomID      id;

    std::string name;
    std::string description;

    Exit        exits[MAX_EXITS];

    int         exitCount;
};

struct Narator
{

};

struct GameState
{
    Player      player;
    Narator     narator;

    Room        rooms[MAX_ROOMS];
    Item        items[MAX_ITEMS];

    std::string narrator[MSG_COUNT];

    int         roomCount;
    int         itemCount;

    bool        running;
};


#endif //ZORKCLONE_TYPES_HPP