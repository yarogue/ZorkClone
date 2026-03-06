#include "commands.hpp"
#include <cstring>
#include <iostream>
#include <string>

void QuitCommand(GameState &state) { state.running = false; }

void HelpCommand(const GameState &state) {
  std::cout << std::endl;
  std::cout << "You are trapped in a room." << std::endl;
  std::cout << "Something is not right about this place." << std::endl;
  std::cout << "Use your senses. Observe carefully." << std::endl;
  std::cout << "Things may not be the same as they were before..." << std::endl;
  std::cout << "Find a way out." << std::endl;
  std::cout << "To see all commands type commands." << std::endl;
  if (state.entityPresent) {
    std::cout << std::endl;
    std::cout << "!! AVOID THE ENTITY !!" << std::endl;
    std::cout << "Don't look at it. Don't walk towards it." << std::endl;
  }
  std::cout << std::endl;
}

void CommandsList() {
  std::cout << "=== Commands ===" << std::endl;
  std::cout << "  location        - see your location" << std::endl;
  std::cout << "  look            - observe the room" << std::endl;
  std::cout << "  look <item>     - examine something specific" << std::endl;
  std::cout << "  read <item>     - read text on something" << std::endl;
  std::cout << "  smell           - what does it smell like?" << std::endl;
  std::cout << "  listen          - what can you hear?" << std::endl;
  std::cout << "  go <direction>  - move somewhere" << std::endl;
  std::cout << "  exit            - to exit room ..." << std::endl;
  std::cout << "  look <dir>      - look north/south/east/west/up/down"
            << std::endl;
  std::cout << "  look left/right - look relative to facing" << std::endl;
  std::cout << "  turn <dir>      - turn to face a direction" << std::endl;
  std::cout << "  turn left/right - turn relative to facing" << std::endl;
  std::cout << "  kick <item>     - kick something" << std::endl;
  std::cout << "  take <item>     - pick something up" << std::endl;
  std::cout << "  drop <item>     - put something down" << std::endl;
  std::cout << "  inventory       - check what you carry" << std::endl;
  std::cout << "  scream          - ...if you must" << std::endl;
  std::cout << "  log             - recent command history" << std::endl;
  std::cout << "  quit            - give up and leave" << std::endl;
  std::cout << std::endl;
}

void LogCommand(GameState &state) {
  std::cout << "=== Command Log ===" << std::endl;
  for (int i = 0; i < state.logCount; i++) {
    std::cout << "[" << i << "] " << state.commandLog[i] << std::endl;
  }
}

// Helper to location command

std::string directionToString(const Direction direction) {
  switch (direction) {
  case DIR_NORTH:
    return "North";
  case DIR_SOUTH:
    return "South";
  case DIR_EAST:
    return "East";
  case DIR_WEST:
    return "West";
  case DIR_UP:
    return "Up";
  case DIR_DOWN:
    return "Down";
  default:
    return "Unknown";
  }
}

void LocationCommand(const GameState &state) {

  std::cout << " you are at [X]" << std::endl;
  std::string labels[9] = {" N.W  ", "  N   ", " N.E  ", "  W   ", "center",
                           "  E   ", " S.W  ", "  S   ", " S.E  "};

  labels[state.player.position] = " [X]  ";
  if (state.entityPresent) {
    labels[state.entityPosition] = " [O]  ";
  }
  std::cout << "+------+------+------+" << std::endl;
  std::cout << "|" << labels[0] << "|" << labels[1] << "|" << labels[2] << "|"
            << std::endl;
  std::cout << "+------+------+------+" << std::endl;
  std::cout << "|" << labels[3] << "|" << labels[4] << "|" << labels[5] << "|"
            << std::endl;
  std::cout << "+------+------+------+" << std::endl;
  std::cout << "|" << labels[6] << "|" << labels[7] << "|" << labels[8] << "|"
            << std::endl;
  std::cout << "+------+------+------+" << std::endl;

  // Direction output
  std::cout << "Facing: " << directionToString(state.player.direction)
            << std::endl;
}

// ===== Tic-tac-toe helpers =====

void printTTTBoard(const int board[9]) {
  std::cout << "+---+---+---+" << std::endl;
  for (int r = 0; r < 3; r++) {
    std::cout << "| ";
    for (int c = 0; c < 3; c++) {
      int idx = r * 3 + c;
      if (board[idx] == 1)
        std::cout << "X";
      else if (board[idx] == 2)
        std::cout << "O";
      else
        std::cout << ".";
      std::cout << " | ";
    }
    std::cout << std::endl;
    std::cout << "+---+---+---+" << std::endl;
  }
}

bool checkTTTWin(const int board[9], int player) {
  const int wins[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6},
                          {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
  for (int i = 0; i < 8; i++) {
    if (board[wins[i][0]] == player && board[wins[i][1]] == player &&
        board[wins[i][2]] == player)
      return true;
  }
  return false;
}

int tttAIMove(const int board[9]) {
  // 1. Win if possible
  for (int i = 0; i < 9; i++) {
    if (board[i] == 0) {
      int test[9];
      std::memcpy(test, board, sizeof(int) * 9);
      test[i] = 2;
      if (checkTTTWin(test, 2))
        return i;
    }
  }
  // 2. Center
  if (board[4] == 0)
    return 4;
  // 4. Corners
  int corners[] = {0, 2, 6, 8};
  for (int c : corners)
    if (board[c] == 0)
      return c;
  // 5. Sides
  int sides[] = {1, 3, 5, 7};
  for (int s : sides)
    if (board[s] == 0)
      return s;
  return -1; // board full
}

void describeFacing(const GameState &state) {
  Position pos = state.player.position;
  Direction dir = state.player.direction;

  if (dir == DIR_UP) {
    if (pos == POS_FRONT_RIGHT) {
      std::cout << "You look up. You can see the CCTV camera in the corner."
                << std::endl;
    } else {
      std::cout << "You look up. A bare fluorescent light flickers."
                << std::endl;
    }
    return;
  }
  if (dir == DIR_DOWN) {
    std::cout << "You look down. Cold concrete floor with scattered dust."
              << std::endl;
    return;
  }
  if (dir == DIR_NORTH) {
    switch (pos) {
    case POS_CENTER:
      std::cout << "You see the exit door ahead with a green EXIT sign."
                << std::endl;
      break;
    case POS_FRONT:
      std::cout << "The exit door is right in front of you." << std::endl;
      break;
    case POS_BACK:
      std::cout << "The exit door is far across the room. I can see  the "
                   "camera on right top corner"
                << std::endl;
      break;
    default:
      std::cout << "Nothing to see here ..." << std::endl;
    }
  } else if (dir == DIR_SOUTH) {
    switch (pos) {
    case POS_CENTER:
      std::cout << "You see the back wall with door without any handlers"
                << std::endl;
      break;
    case POS_FRONT:
      std::cout << "You see the chair  in center of room and unaccessible door "
                   "on back side of room."
                << std::endl;
      break;
    default:
      std::cout << "Nothing to see here ..." << std::endl;
    }

  } else if (dir == DIR_EAST) {
    std::cout << "You see the right wall." << std::endl;
  } else if (dir == DIR_WEST) {
    // Only show grid detail if close to the wall
    if (pos != POS_LEFT && pos != POS_FRONT_LEFT && pos != POS_BACK_LEFT) {
      std::cout << "You see the left wall with graffiti on it." << std::endl;
    } else {
      // Show tic-tac-toe grid on the wall
      bool hasOs = false;
      for (int i = 0; i < 9; i++)
        if (state.tttBoard[i] == 2)
          hasOs = true;

      std::cout << "Some vandals drew vulgar graffiti and male genital organs"
                << std::endl;
      std::cout << "all over the wall... not much to see here really..."
                << std::endl;
      std::cout << "except there is a 9-celled grid that reminds me of"
                << std::endl;
      if (!hasOs) {
        std::cout << "a tic-tac-toe game." << std::endl;
      } else {
        std::cout << "a tic-tac-toe game. Ah, somebody started playing already!"
                  << std::endl;
      }
      std::cout << "\"I wish I had something sharp to draw X on it..."
                << std::endl;
      std::cout << "maybe somebody will see it and want to continue...\""
                << std::endl;
      printTTTBoard(state.tttBoard);
    }
  }
}

// Helper functions for LookCommand

bool isDirection(const std::string &noun) {
  return (noun == "north" || noun == "south" || noun == "east" ||
          noun == "west" || noun == "up" || noun == "down");
}

Direction toDirection(const std::string &noun) {
  if (noun == "north")
    return DIR_NORTH;
  if (noun == "south")
    return DIR_SOUTH;
  if (noun == "east")
    return DIR_EAST;
  if (noun == "west")
    return DIR_WEST;
  if (noun == "up")
    return DIR_UP;
  if (noun == "down")
    return DIR_DOWN;
  return DIR_NORTH; // fallback
}

Direction rotateClockwise(Direction current) {
  switch (current) {
  case DIR_NORTH:
    return DIR_EAST;
  case DIR_EAST:
    return DIR_SOUTH;
  case DIR_SOUTH:
    return DIR_WEST;
  case DIR_WEST:
    return DIR_NORTH;
  default:
    return current;
  }
}
Direction rotateCounterClockwise(Direction current) {
  switch (current) {
  case DIR_NORTH:
    return DIR_WEST;
  case DIR_WEST:
    return DIR_SOUTH;
  case DIR_SOUTH:
    return DIR_EAST;
  case DIR_EAST:
    return DIR_NORTH;
  default:
    return current;
  }
}
Direction rotateOpposite(Direction current) {
  switch (current) {
  case DIR_NORTH:
    return DIR_SOUTH;
  case DIR_SOUTH:
    return DIR_NORTH;
  case DIR_EAST:
    return DIR_WEST;
  case DIR_WEST:
    return DIR_EAST;
  default:
    return current;
  }
}

// Forward declaration for entity detection
bool tryMove(int row, int col, Direction dir, int &outNewPos);

// Entity detection helpers
bool wouldFaceEntity(const GameState &state) {
  if (!state.entityPresent)
    return false;
  if (state.player.direction == DIR_UP || state.player.direction == DIR_DOWN)
    return false;
  int pos = state.player.position;
  int row = pos / 3;
  int col = pos % 3;
  int facedPos = -1;
  tryMove(row, col, state.player.direction, facedPos);
  return (facedPos != -1 && facedPos == state.entityPosition);
}

void entityGameOver(GameState &state) {
  std::cout << std::endl;
  std::cout << "You looked at it..." << std::endl;
  std::cout << std::endl;
  std::cout << "The dark figure turns towards you. Its eyeless face"
            << std::endl;
  std::cout << "locks onto yours. A piercing shriek fills the room."
            << std::endl;
  std::cout << "The lights flicker and go out." << std::endl;
  std::cout << std::endl;
  std::cout << "=== GAME OVER ===" << std::endl;
  state.running = false;
}

void LookCommand(GameState &state, const std::string &noun) {
  Room &room = state.rooms[state.player.currentRoom];

  if (isDirection(noun)) {
    state.player.direction = toDirection(noun);
    std::cout << "You turn face to " << noun << "." << std::endl;
    if (wouldFaceEntity(state)) {
      entityGameOver(state);
      return;
    }
    describeFacing(state);
    return;
  }

  if (noun == "right") {
    state.player.direction = rotateClockwise(state.player.direction);
    std::cout << "You look to your right." << std::endl;
    if (wouldFaceEntity(state)) {
      entityGameOver(state);
      return;
    }
    describeFacing(state);
    return;
  }
  if (noun == "left") {
    state.player.direction = rotateCounterClockwise(state.player.direction);
    std::cout << "You look to your left." << std::endl;
    if (wouldFaceEntity(state)) {
      entityGameOver(state);
      return;
    }
    describeFacing(state);
    return;
  }
  if (noun == "forward" || noun == "straight" || noun == "wall") {
    std::cout << "You look ahead." << std::endl;
    if (wouldFaceEntity(state)) {
      entityGameOver(state);
      return;
    }
    describeFacing(state);
    return;
  }
  if (noun == "behind" || noun == "back") {
    state.player.direction = rotateOpposite(state.player.direction);
    std::cout << "You look behind you." << std::endl;
    if (wouldFaceEntity(state)) {
      entityGameOver(state);
      return;
    }
    describeFacing(state);
    return;
  }

  if (noun.empty() || noun == "around") {
    // General room description
    std::cout << "=== " << room.name << " ===" << std::endl;

    // Position-specific description
    switch (state.player.position) {
    case POS_CENTER:
      if (state.chairBroken) {
        std::cout << "You stand in the middle of the room. The chair is gone."
                  << std::endl;
      } else if (state.chairIsWooden) {
        std::cout << "You stand in the middle of the room next to an old "
                     "wooden chair."
                  << std::endl;
      } else {
        std::cout << "You stand in the middle of the room next to a cheap "
                     "plastic chair."
                  << std::endl;
      }
      std::cout << "A door with an EXIT sign is ahead. Walls on all sides."
                << std::endl;

      // Player commentary on look — changes per loop
      std::cout << std::endl;
      if (state.loopCount == 0) {
        std::cout << "\"This is some kind of transition back side room?"
                  << std::endl;
        std::cout << "I need to escape out of here at once." << std::endl;
        std::cout
            << "There is a door with EXIT sign, surely I need to go there.\""
            << std::endl;
      } else {
        std::cout << "\"This is the same back side room. Nothing special."
                  << std::endl;
        std::cout << "Same door in middle far with EXIT sign." << std::endl;
        std::cout << "Near right wall center there two dumpsters, blue one"
                  << std::endl;
        std::cout << "for recycle, other black for all type of garbage."
                  << std::endl;
        std::cout << "In right far corner on top I can see CCTV camera"
                  << std::endl;
        std::cout << "indicator blinking." << std::endl;
        std::cout << "On left wall nothing special, just vulgar texts and"
                  << std::endl;
        std::cout << "graffiti carved by some rascals with sharp objects.\""
                  << std::endl;
      }
      break;
    case POS_FRONT:
      std::cout
          << "You stand in front of the door. The EXIT sign glows green above."
          << std::endl;
      std::cout << "A note is taped to the door frame." << std::endl;
      break;
    case POS_FRONT_LEFT:
      std::cout << "You stand in left front corner of the room. " << std::endl;
      std::cout << "There few sealed electric sockets at bottom.\n"
                   " All of them are damaged and some wires dangerously exposed"
                << std::endl;
      break;
    case POS_FRONT_RIGHT:
      std::cout << "You stand in right front corner of the room. \n"
                << std::endl;
      std::cout << "On top CCTV camera is observing the room. \n"
                   "The red light indicator is blinking ."
                << std::endl;
      break;
    case POS_BACK:
      if (state.chairBroken) {
        std::cout << "Wreckage of the old chair lies against the back wall."
                  << std::endl;
        std::cout << "In the wooden pile, a sharp rusty nail dramatically"
                  << std::endl;
        std::cout << "stands out from the broken parts." << std::endl;
      } else {
        std::cout
            << "You face the back wall.\n"
               "There a same door like on opposite side of room.\n"
               "How ever this door doesnt have any handler or way to open it.\n"
            << std::endl;
      }
      break;
    case POS_LEFT:
      std::cout << "The left wall. Bare concrete,  cold to the touch. \n"
                   "There some writings curved on the wall."
                << std::endl;
      break;
      // ... add descriptions for each position
    }

    // List items at this position
    for (int i = 0; i < state.itemCount; i++) {
      if (state.items[i].location == state.player.currentRoom) {
        std::cout << "You see: " << state.items[i].name << std::endl;
      }
    }
  }

  else if (noun == "inventory") {
    InventoryCommand(state, noun);
  } else {
    // search for item in room or inventory
    for (int i = 0; i < state.itemCount; i++) {
      if (state.items[i].name == noun &&
          (state.items[i].location == state.player.currentRoom ||
           state.items[i].location == INVENTORY)) {
        std::cout << state.items[i].description << std::endl;
        return;
      }
    }
    std::cout << "You don't see '" << noun << "' here." << std::endl;
  }
}

void Turn(GameState &state, const std::string &noun) {
  if (noun.empty()) {
    std::cout << "Turn where?" << std::endl;
    return;
  }

  // Absolute directions: "turn north", "turn south", etc.
  if (isDirection(noun)) {
    state.player.direction = toDirection(noun);
    std::cout << "You turn to face "
              << directionToString(state.player.direction) << "." << std::endl;
    return;
  }

  // Relative directions: "turn left", "turn right", "turn around"
  if (noun == "right") {
    state.player.direction = rotateClockwise(state.player.direction);
  } else if (noun == "left") {
    state.player.direction = rotateCounterClockwise(state.player.direction);
  } else if (noun == "around" || noun == "behind") {
    state.player.direction = rotateOpposite(state.player.direction);
  } else {
    std::cout << "Turn where?" << std::endl;
    return;
  }

  std::cout << "You turn to face " << directionToString(state.player.direction)
            << "." << std::endl;
}

bool tryMove(int row, int col, Direction dir, int &outNewPos) {
  switch (dir) {
  case DIR_NORTH:
    if (row > 0) {
      outNewPos = (row - 1) * 3 + col;
      return true;
    }
    return false;
  case DIR_SOUTH:
    if (row < 2) {
      outNewPos = (row + 1) * 3 + col;
      return true;
    }
    return false;
  case DIR_WEST:
    if (col > 0) {
      outNewPos = row * 3 + (col - 1);
      return true;
    }
    return false;
  case DIR_EAST:
    if (col < 2) {
      outNewPos = row * 3 + (col + 1);
      return true;
    }
    return false;
  default:
    return false;
  }
}

void GoCommand(GameState &state, const std::string &noun) {
  if (noun.empty()) {
    std::cout << "Go where?" << std::endl;
    return;
  }

  int pos = state.player.position;
  int row = pos / 3;
  int col = pos % 3;
  int newPos = -1;

  // Determine movement direction — relative or absolute
  Direction moveDir;
  if (noun == "forward" || noun == "ahead") {
    moveDir = state.player.direction;
  } else if (noun == "back" || noun == "backward") {
    moveDir = rotateOpposite(state.player.direction);
  } else if (noun == "left") {
    moveDir = rotateCounterClockwise(state.player.direction);
  } else if (noun == "right") {
    moveDir = rotateClockwise(state.player.direction);
  } else if (noun == "north" || noun == "south" || noun == "east" ||
             noun == "west") {
    moveDir = toDirection(noun);
  } else {
    std::cout << "You can't go there." << std::endl;
    return;
  }

  // Can't walk up or down
  if (moveDir == DIR_UP) {
    std::cout << "\"I can't fly...\"" << std::endl;
    return;
  }
  if (moveDir == DIR_DOWN) {
    std::cout << "\"Not yet...\"" << std::endl;
    return;
  }

  if (!tryMove(row, col, moveDir, newPos)) {
    std::cout << "You can't go that way, there's a wall." << std::endl;
    return;
  }

  if (newPos != -1) {
    // Check if walking into entity
    if (state.entityPresent && newPos == state.entityPosition) {
      std::cout << "You walk into the darkness..." << std::endl;
      entityGameOver(state);
      return;
    }
    state.player.position = (Position)newPos;
    state.player.direction = moveDir; // face the direction you walked
    state.actionCount++;
    std::cout << "You walk " << noun << "." << std::endl;
  }
}

void ExitDoorCommand(GameState &state, const std::string &noun) {
  // Entity blocks direct exit from far away
  if (state.entityPresent && state.player.position != POS_FRONT) {
    std::cout << "\"I can't just go straight there... I need to avoid..."
              << std::endl;
    std::cout << "this... whatever it is.\"" << std::endl;
    return;
  }

  // Different message based on where the player is
  std::cout << std::endl;
  if (state.player.position == POS_FRONT) {
    std::cout << "You push the door and the door opens." << std::endl;
  } else {
    std::cout << "You go straight forward to the exit door," << std::endl;
    std::cout << "you push it and the door opens." << std::endl;
  }

  // Only increment AFTER check passes
  state.loopCount++;
  state.actionCount++;
  state.player.position = POS_BACK;   // enter next room from the back door
  state.player.direction = DIR_NORTH; // look at north when as default

  // Handle chair state for next loop
  if (state.chairBroken) {
    state.items[2].name = "chair";
    state.items[2].description =
        "A cheap plastic chair. It replaced the old wooden one.";
    state.items[2].location = 0; // visible again
    state.items[2].canPickUp = false;
    if (state.items[3].location != INVENTORY) {
      state.items[3].location = ROOM_NONE; // hide nail only if not picked up
    }
    state.chairBroken = false;   // reset for plastic chair
    state.chairIsWooden = false; // it's plastic now
  }

  std::cout << std::endl;
  std::cout << "You exit through the door and it slaps loudly behind you..."
            << std::endl;
  std::cout << std::endl;
  if (!state.chairIsWooden) {
    std::cout << "It is the same room but there is a new plastic chair"
              << std::endl;
    std::cout << "instead of the wooden one." << std::endl;
  } else {
    std::cout << "Once you exit you see the exact same room in front of you."
              << std::endl;
  }

  // --- Tic-tac-toe: entity plays O ---
  if (!state.tttPlayerWon && state.tttEntityWonLoop < 0) {
    int move = tttAIMove(state.tttBoard);
    if (move >= 0) {
      state.tttBoard[move] = 2;
      if (checkTTTWin(state.tttBoard, 2)) {
        state.tttEntityWonLoop = state.loopCount;
        // Ripped note appears when entity wins
        state.items[1].description =
            "A ripped piece of paper taped hastily to the door frame.";
        state.items[1].read = "DONT LOOK AT IT !";
        state.items[1].location = 0;
      }
    }
  }
  state.tttPlayerMoved = false; // reset for next loop

  // --- Handle entity appearance (one loop after entity wins TTT) ---
  if (state.tttEntityWonLoop >= 0 && state.loopCount > state.tttEntityWonLoop) {
    state.entityPresent = true;
    state.entityPosition = POS_CENTER;
    state.player.direction = DIR_DOWN;

    std::cout << std::endl;
    std::cout << "While entering, with your side look you notice a human-shaped"
              << std::endl;
    std::cout << "dark entity standing in the middle of the room." << std::endl;
    std::cout << "The horror bursts in you and you don't know what to do."
              << std::endl;
    std::cout << std::endl;
    std::cout << "\"What the hell is this!? I better avoid it.\"" << std::endl;
  }

  // --- Handle player TTT win → escape ---
  if (state.tttPlayerWon) {
    std::cout << std::endl;
    std::cout << "\"Finally, I am free!\"" << std::endl;
    std::cout << std::endl;
    std::cout << "=== YOU ESCAPED ===" << std::endl;
    std::cout << "Actions taken: " << state.actionCount << std::endl;
    std::cout << "Loops survived: " << state.loopCount << std::endl;
    state.running = false;
    return;
  }

  // Player commentary — changes with each loop (only if entity hasn't won)
  if (state.tttEntityWonLoop < 0 || state.loopCount <= state.tttEntityWonLoop) {
    std::cout << std::endl;
    if (state.loopCount == 1) {
      std::cout << "\"Hmm... strange. This room looks almost the same as the"
                << std::endl;
      std::cout << "previous one? Could it be...\"" << std::endl;
    } else if (state.loopCount == 2) {
      std::cout << "\"What is going on? How could it be? Is it a long corridor"
                << std::endl;
      std::cout << "with same rooms or am I going insane?\"" << std::endl;
    } else if (state.loopCount >= 3 && state.tttEntityWonLoop < 0) {
      std::cout << "\"IS THIS A JOKE!? OR IS SOME KIND OF SOCIAL EXPERIMENT!!?"
                << std::endl;
      std::cout << "LET ME OUT!!!\"" << std::endl;
    }
  }
}

void SmellCommand(GameState &state, const std::string &noun) {
  // ============================================================
  // TODO 3: Smell the room or a specific item
  //
  // if noun is empty:
  //     Room& room = state.rooms[state.player.currentRoom];
  //     std::cout << room.smell << std::endl;
  // else:
  //     search for item matching noun
  //     if found: print item.smell
  //     else: "You can't smell that."
  // ============================================================
}

void TouchCommand(GameState &state, const std::string &noun) {
  // ============================================================
  // TODO 4: Touch an item
  // search for item matching noun in room or inventory
  // if found: print item.touch
  // else: "You can't touch that."
  // ============================================================
}

void ListenCommand(GameState &state, const std::string &noun) {
  // ============================================================
  // TODO 5: Listen to the room
  //
  // if noun is empty:
  //     Room& room = state.rooms[state.player.currentRoom];
  //     std::cout << room.listen << std::endl;
  // else:
  //     "You listen closely to the " + noun + "... nothing."
  // ============================================================
}

void ScreamCommand(GameState &state, const std::string &noun) {
  std::cout << "AAAAAAARGGHHh!!!" << std::endl;
}

void KickCommand(GameState &state, const std::string &noun) {
  if (noun.empty()) {
    std::cout << "Kick what?" << std::endl;
    return;
  }
  if (noun == "chair") {
    if (state.chairBroken) {
      std::cout << "The chair is already broken." << std::endl;
      return;
    }
    if (state.player.position != POS_CENTER) {
      std::cout << "You're too far from the chair." << std::endl;
      return;
    }

    state.actionCount++;

    if (state.chairIsWooden) {
      // BREAK THE WOODEN CHAIR!
      state.chairBroken = true;
      state.items[2].location = ROOM_NONE; // chair disappears as item
      state.items[3].location = 0;         // nail appears in room

      std::cout << std::endl;
      std::cout << "You kicked the chair! It smacks against the back wall"
                << std::endl;
      std::cout << "and falls apart. The crack echoes through the room"
                << std::endl;
      std::cout << "as it shatters into pieces." << std::endl;
      std::cout << std::endl;
      std::cout << "\"I don't know why I did that... but it felt good.\""
                << std::endl;
    } else {
      // KICK THE PLASTIC CHAIR — it bounces but doesn't break
      std::cout << std::endl;
      std::cout << "Plastic chair been sent to the air. It falls quickly"
                << std::endl;
      std::cout << "bouncing on the ground a few times." << std::endl;
    }
  } else if (noun == "door") {
    std::cout << "In contrast to your feet, nothing happens to the door."
              << std::endl;
  } else {
    std::cout << "I'd rather not do that." << std::endl;
  }
}

void TakeCommand(GameState &state, const std::string &noun) {
  if (noun.empty()) {
    std::cout << "Take what?" << std::endl;
    return;
  }
  for (int i = 0; i < state.itemCount; i++) {
    if (state.items[i].name == noun &&
        state.items[i].location == state.player.currentRoom) {
      if (state.items[i].canPickUp) {
        state.items[i].location = INVENTORY;
        state.actionCount++;
        std::cout << "You pick up the " << noun << "." << std::endl;
      } else {
        std::cout << "You can't pick that up." << std::endl;
      }
      return;
    }
  }
  std::cout << "You don't see that here." << std::endl;
}

void DropCommand(GameState &state, const std::string &noun) {
  if (noun.empty()) {
    std::cout << "Drop what?" << std::endl;
    return;
  }
  for (int i = 0; i < state.itemCount; i++) {
    if (state.items[i].name == noun && state.items[i].location == INVENTORY) {
      state.items[i].location = ROOM_NONE; // disappears!
      state.actionCount++;
      std::cout << "You drop the " << noun << ". It vanishes into the darkness."
                << std::endl;
      return;
    }
  }
  std::cout << "You're not carrying that." << std::endl;
}

void ReadCommand(GameState &state, const std::string &noun) {
  if (noun.empty()) {
    std::cout << "Read what?" << std::endl;
    return;
  }
  // find the item
  for (int i = 0; i < state.itemCount; i++) {
    if (state.items[i].name == noun &&
        (state.items[i].location == state.player.currentRoom ||
         state.items[i].location == INVENTORY)) {
      // found it — but is the player close enough?

      // if (state.player.nearObject != "door" && state.player.nearObject !=
      // "note" && noun == "note") {
      //     std::cout << "The note is too far. You can barely make out some
      //     writing." << std::endl; return;
      // }
      // check if there's anything to read
      if (state.items[i].read.empty()) {
        std::cout << "There's nothing to read on the " << noun << "."
                  << std::endl;
      } else {
        std::cout << state.items[i].read << std::endl;
      }
      return;
    }
  }
  std::cout << "You don't see that here." << std::endl;
}

// ============================================================
// TODO 6: ReadCommand — read text on an item (like the note)
//
// void ReadCommand(GameState& state, const std::string& noun)
// {
//     if noun is empty:
//         "Read what?"
//     else:
//         search for item by name in room or inventory
//         if found AND item.read is not empty:
//             print item.read
//         else if found but item.read is empty:
//             "There's nothing to read on the " + noun
//         else:
//             "You don't see that here."
// }
// ============================================================

// ============================================================
// TODO 7: GoCommand — the loop mechanic!
//
// void GoCommand(GameState& state, const std::string& noun)
// {
//     if noun is empty:
//         "Go where?"
//         return
//
//     // check if noun matches an exit direction
//     Room& room = state.rooms[state.player.currentRoom];
//     for each exit in room.exits:
//         if exit.direction == noun:
//             // FOUND THE EXIT!
//             state.loopCount++
//             state.actionCount++
//             print "You push through the door..."
//             print "...and find yourself back in the same room."
//             print "But something feels different."
//             // room description will change next time player types "look"
//             return
//
//     // no exit matched
//     "You can't go that way."
// }
// ============================================================

void InventoryCommand(GameState &state, const std::string &noun) {
  std::cout << "=== Inventory ===" << std::endl;
  bool hasItems = false;
  for (int i = 0; i < state.itemCount; i++) {
    if (state.items[i].location == INVENTORY) {
      std::cout << "  " << state.items[i].name << std::endl;
      hasItems = true;
    }
  }
  if (!hasItems) {
    std::cout << "You are carrying nothing." << std::endl;
  }
}

// ============================================================
// TODO 8: InventoryCommand — show items player is carrying
//
// void InventoryCommand(GameState& state)
// {
//     std::cout << "=== Inventory ===" << std::endl;
//     bool hasItems = false;
//     for (int i = 0; i < state.itemCount; i++) {
//         if (state.items[i].location == INVENTORY) {
//             std::cout << "  " << state.items[i].name << std::endl;
//             hasItems = true;
//         }
//     }
//     if (!hasItems):
//         "You are carrying nothing."
// }
// ============================================================

// ============================================================
// TODO 9: TakeCommand — pick up an item
//
// void TakeCommand(GameState& state, const std::string& noun)
// {
//     if noun is empty:
//         "Take what?"
//     else:
//         search items where name == noun AND location == currentRoom
//         if found AND canPickUp:
//             item.location = INVENTORY
//             "You pick up the " + noun
//         else if found but !canPickUp:
//             "You can't pick that up."
//         else:
//             "You don't see that here."
// }
// ============================================================

// ============================================================
// TODO 10: DropCommand — drop an item from inventory
//
// void DropCommand(GameState& state, const std::string& noun)
// {
//     if noun is empty:
//         "Drop what?"
//     else:
//         search items where name == noun AND location == INVENTORY
//         if found:
//             item.location = currentRoom
//             "You drop the " + noun
//         else:
//             "You're not carrying that."
// }
// ============================================================

// ===== Draw / Play Command (Tic-tac-toe) =====

void DrawCommand(GameState &state, const std::string &noun) {
  // Must be at a west-side cell
  if (state.player.position != POS_LEFT &&
      state.player.position != POS_FRONT_LEFT &&
      state.player.position != POS_BACK_LEFT) {
    std::cout << "There's nothing to draw on here." << std::endl;
    return;
  }
  // Must be facing the wall
  if (state.player.direction != DIR_WEST) {
    std::cout << "You're not facing the wall." << std::endl;
    return;
  }
  // Must have nail
  bool hasNail = false;
  for (int i = 0; i < state.itemCount; i++) {
    if (state.items[i].name == "nail" && state.items[i].location == INVENTORY) {
      hasNail = true;
      break;
    }
  }
  if (!hasNail) {
    std::cout << "\"I wish I had something sharp to draw with...\""
              << std::endl;
    return;
  }
  // Already moved this loop
  if (state.tttPlayerMoved) {
    std::cout << "You already made your move this turn." << std::endl;
    return;
  }
  // Game already over
  if (state.tttPlayerWon || state.tttEntityWonLoop >= 0) {
    std::cout << "The game is already over." << std::endl;
    return;
  }
  // No cell specified — show board
  if (noun.empty()) {
    std::cout << "Where do you want to draw X? (1-9)" << std::endl;
    printTTTBoard(state.tttBoard);
    return;
  }
  // Parse cell number
  int cell = -1;
  if (noun.size() == 1 && noun[0] >= '1' && noun[0] <= '9') {
    cell = noun[0] - '1';
  }
  if (cell < 0 || cell > 8) {
    std::cout << "Pick a number between 1 and 9." << std::endl;
    return;
  }
  if (state.tttBoard[cell] != 0) {
    std::cout << "That cell is already taken." << std::endl;
    return;
  }
  // Place X
  state.tttBoard[cell] = 1;
  state.tttPlayerMoved = true;
  state.actionCount++;

  std::cout << std::endl;
  std::cout << "You scratch an X into the wall with the rusty nail."
            << std::endl;
  printTTTBoard(state.tttBoard);

  // Check player win
  if (checkTTTWin(state.tttBoard, 1)) {
    state.tttPlayerWon = true;
    std::cout << std::endl;
    std::cout << "\"That was easy.\"" << std::endl;
  } else {
    std::cout << std::endl;
    std::cout << "\"Let's see if someone continues the game...\"" << std::endl;
  }
}