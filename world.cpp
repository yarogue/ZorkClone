#include "world.hpp"
#include "types.hpp"
#include <string>

void init_world(GameState* state)
{
    state->narrator[MSG_WELCOME]   = "You awaken in a cold, dark place.";
    state->narrator[MSG_HELP_HINT] = "Type 'help' if you are lost, adventurer.";
    state->narrator[MSG_GOODBYE]   = "The darkness swallows you whole. Farewell.";
}