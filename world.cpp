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
    state->rooms[0].exits[0].direction = "north";
    state->rooms[0].exits[0].destination = 1;
    state->roomCount = 1;
}
void init_world(GameState* state)
{
    state->narrator[MSG_WELCOME]   = "hey you're finally awake.";
    state->narrator[MSG_HELP_HINT] = "Type 'help' if you are lost.";
    state->narrator[MSG_GOODBYE]   = "Farewell.";

    state->roomCount = 0;
    state->player.currentRoom = 0;

    firstRoom(state);
}