#include "world.hpp"
#include "types.hpp"
#include <string>

void Room(GameState *state) {
  state->rooms[0].id = 0;
  state->rooms[0].name = "Dark Cell";
  state->rooms[0].description =
      "You awaken on old wooden chair. There a door in few steps away from you "
      "with green light text EXIT.";
  state->rooms[0].smell = "The air reeks of mildew and decay.";
  state->rooms[0].listen =
      "You can hear machine working in a far room repeatedly dumping something "
      "heavy again and again ";
  state->rooms[0].exitCount = 1;
  state->rooms[0].exits[0].direction = "door";
  state->rooms[0].exits[0].destination = 0; // leads back to same room!
  state->roomCount = 1;

  // Front Door
  state->items[0].id = 0;
  state->items[0].name = "door";
  state->items[0].description =
      " A heavy metal door with a horizontal push bar. \n"
      "The type you see at emergency exits in hotels and restaurants — push to "
      "open,\n"
      "can't be opened from the other side.\n"
      "A green EXIT sign glows above it.\n"
      "There's a small note taped to the frame.\n";
  state->items[0].location = 0;
  state->items[0].canPickUp = false;

  // Note on the door
  state->items[1].id = 1;
  state->items[1].name = "note";
  state->items[1].description =
      "A crumpled paper note taped to the door frame.";
  state->items[1].read = "WARNING: Opening this door will trigger the alarm.";
  state->items[1].location = 0;
  state->items[1].canPickUp = true;

  // Chair
  state->items[2].id = 2;
  state->items[2].name = "chair";
  state->items[2].description =
      "An old wooden chair. Looks like it could fall apart at any moment.";
  state->items[2].location = 0;
  state->items[2].canPickUp = false;

  // Rusty nail — hidden until chair is kicked
  state->items[3].id = 3;
  state->items[3].name = "nail";
  state->items[3].description = "A sharp, rusty nail from the broken chair.";
  state->items[3].location = ROOM_NONE; // hidden!
  state->items[3].canPickUp = true;

  state->itemCount = 4;
}

void init_world(GameState *state) {
  state->narrator[MSG_WELCOME] = "hey you're finally awake.";
  state->narrator[MSG_HELP_HINT] = "Type 'help' if you are lost.";
  state->narrator[MSG_GOODBYE] = "Farewell.";

  state->roomCount = 0;
  state->player.currentRoom = 0;
  state->loopCount = 0;
  state->actionCount = 0;
  state->escaped = false;
  state->chairBroken = false;
  state->chairIsWooden = true;
  state->entityPresent = false;
  state->entityPosition = POS_CENTER;
  for (int i = 0; i < 9; i++)
    state->tttBoard[i] = 0;
  state->tttPlayerMoved = false;
  state->tttPlayerWon = false;
  state->tttEntityWonLoop = -1;
  state->player.position = POS_CENTER;
  state->player.direction = DIR_NORTH;

  Room(state);
}