#include "world.hpp"
#include "types.hpp"
#include <string>

void firstRoom(GameState* state)
{
    state->rooms[0].id = 0;
    state->rooms[0].name = "Dark Cell";
    state->rooms[0].description = "You awaken on old wooden chair. There a door in few steps away from you with green light text EXIT.";
    state->rooms[0].smell = "The air reeks of mildew and decay.";
    state->rooms[0].listen = "You can hear machine working in a far room repeatedly dumping something heavy again and again ";
    state->rooms[0].exitCount = 1;
    state->rooms[0].exits[0].direction = "door";
    state->rooms[0].exits[0].destination = 0;  // leads back to same room!
    state->roomCount = 1;

    state->items[0].id = 0;
    state->items[0].name = "door";
    state->items[0].description = " A heavy metal door with a horizontal push bar. \n"
                                  "The type you see at emergency exits in hotels and restaurants — push to open,\n"
                                  "can't be opened from the other side.\n"
                                  "A green EXIT sign glows above it.\n"
                                  "There's a small note taped to the frame.\n";
    state->items[0].location = 0;        // in room 0
    state->items[0].canPickUp = false;

    // ============================================================
    // TODO 1: Set up item — paper note on the door
    //
    // state->items[0].id = 0;
    // state->items[0].name = "note";
    // state->items[0].description = "A crumpled paper note taped to the door.";
    // state->items[0].read = "WARNING: Opening this door will trigger the alarm.";
    // state->items[0].location = 0;        // in room 0
    // state->items[0].canPickUp = true;     // player can take it
    // state->itemCount = 1;
    // ============================================================

    state->items[1].id = 1;
    state->items[1].name = "note";
    state->items[1].description = "A crumpled paper note taped to the door frame.";
    state->items[1].read = "WARNING: Opening this door will trigger the alarm.";
    state->items[1].location = 0;
    state->items[1].canPickUp = true;
    state->itemCount = 2;

    // ============================================================
    // TODO 2: Add more items that appear in later loops
    // These items start with location = ROOM_NONE (hidden)
    // When loopCount increases, change their location to 0
    //
    // state->items[1].id = 1;
    // state->items[1].name = "screwdriver";
    // state->items[1].description = "A rusty screwdriver.";
    // state->items[1].location = ROOM_NONE;   // hidden until loop 2
    // state->items[1].canPickUp = true;
    //
    // state->items[2].id = 2;
    // state->items[2].name = "keycard";
    // state->items[2].description = "A worn keycard with faded text.";
    // state->items[2].location = ROOM_NONE;   // hidden until loop 4
    // state->items[2].canPickUp = true;
    // ============================================================
}

void init_world(GameState*  state)
{
    state->narrator[MSG_WELCOME]   = "hey you're finally awake.";
    state->narrator[MSG_HELP_HINT] = "Type 'help' if you are lost.";
    state->narrator[MSG_GOODBYE]   = "Farewell.";

    state->roomCount = 0;
    state->player.currentRoom = 0;
    state->loopCount = 0;
    state->actionCount = 0;
    state->escaped = false;

    firstRoom(state);
}