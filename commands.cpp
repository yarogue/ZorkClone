#include "commands.hpp"
#include <iostream>
#include <string>

void QuitCommand(GameState& state)
{
    state.running = false;
}

void HelpCommand()
{
    std::cout << std::endl;
    std::cout << "You are trapped in a room." << std::endl;
    std::cout << "Something is not right about this place." << std::endl;
    std::cout << "Use your senses. Observe carefully." << std::endl;
    std::cout << "Things may not be the same as they were before..." << std::endl;
    std::cout << "Find a way out." << std::endl;
    std::cout << "To see all commands type commands." <<std::endl;
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
    // ============================================================
    // TODO STEP G: Add these lines to the commands list
    //   std::cout << "  look <dir>      - look north/south/east/west/up/down" << std::endl;
    //   std::cout << "  look left/right - look relative to facing" << std::endl;
    //   std::cout << "  turn <dir>      - turn to face a direction" << std::endl;
    //   std::cout << "  turn left/right - turn relative to facing" << std::endl;
    // ============================================================
    std::cout << "  take <item>     - pick something up" << std::endl;
    std::cout << "  drop <item>     - put something down" << std::endl;
    std::cout << "  inventory       - check what you carry" << std::endl;
    std::cout << "  scream          - ...if you must" << std::endl;
    std::cout << "  log             - recent command history" << std::endl;
    std::cout << "  quit            - give up and leave" << std::endl;
    std::cout << std::endl;
}

void LogCommand(GameState& state)
{
    std::cout << "=== Command Log ===" << std::endl;
    for (int i = 0; i < state.logCount; i++) {
        std::cout << "[" << i << "] " << state.commandLog[i] << std::endl;
    }
}

//Helper to location command

std::string directionToString(const Direction direction)
{
    switch (direction) {
    case DIR_NORTH: return "North";
    case DIR_SOUTH: return "South";
    case DIR_EAST:  return "East";
    case DIR_WEST:  return "West";
    case DIR_UP:    return "Up";
    case DIR_DOWN:  return "Down";
    default:        return "Unknown";
    }
}

void LocationCommand(const GameState& state) {

    std::cout << " you are at [X]" << std::endl;
    std::string labels[9] = {
        "front-left", "  front   ", "front-right",
        "  left    ",  "   center ", "  right   ",
        "back-left ", "    back  ", "back-right"
    };

    labels[state.player.position] = "   [X]    ";
    std::cout << "+------------+------------+------------+" << std::endl;
    std::cout << "| " << labels[0] << " | " << labels[1] << " | " << labels[2] << " |" << std::endl;
    std::cout << "+------------+------------+------------+" << std::endl;
    std::cout << "| " << labels[3] << " | " << labels[4] << " | " << labels[5] << " |" << std::endl;
    std::cout << "+------------+------------+------------+" << std::endl;
    std::cout << "| " << labels[6] << " | " << labels[7] << " | " << labels[8] << " |" << std::endl;
    std::cout << "+------------+------------+------------+" << std::endl;

    //Direction output
    std::cout << "Facing: " << directionToString(state.player.direction) << std::endl;
}

void describeFacing(const GameState& state)
{
    Position pos  = state.player.position;
    Direction dir = state.player.direction;

    if (dir == DIR_UP) {
        if (pos == POS_FRONT_RIGHT) {
            std::cout << "You look up. You can see the CCTV camera in the corner." << std::endl;
        } else {
            std::cout << "You look up. A bare fluorescent light flickers." << std::endl;
        }
        return;
    }
    if (dir == DIR_DOWN) {
        std::cout << "You look down. Cold concrete floor with scattered dust." << std::endl;
        return;
    }
    if (dir == DIR_NORTH) {
        switch(pos){
        case POS_CENTER:
            std::cout << "You see the exit door ahead with a green EXIT sign." << std::endl;
            break;
        case POS_FRONT:
            std::cout << "The exit door is right in front of you." << std::endl;
            break;
        case POS_BACK:
            std::cout << "The exit door is far across the room. I can see  the camera on right top corner" << std::endl;
            break;
        default:
            std::cout << "Nothing to see here ..." << std::endl;
        }
    } else if (dir == DIR_SOUTH) {
        switch (pos)
        {
            case POS_CENTER:
            std::cout << "You see the back wall with door without any handlers" << std::endl;
            break;
            case POS_FRONT:
                std::cout << "You see the chair  in center of room and unaccessible door on back side of room." << std::endl;
            break;
        default:
            std::cout << "Nothing to see here ..." << std::endl;
        }

    } else if (dir == DIR_EAST) {
        std::cout << "You see the right wall." << std::endl;
    } else if (dir == DIR_WEST) {
        std::cout << "You see the left wall." << std::endl;
    }
}

// ============================================================
// TODO STEP D: describeFacing() — what the player sees in their facing direction
//
// void describeFacing(GameState& state)
// {
//     Position pos  = state.player.position;
//     Direction dir = state.player.direction;
//
//     // UP and DOWN are the same from every position
//     if (dir == DIR_UP) {
//         std::cout << "You look up. A bare fluorescent light flickers." << std::endl;
//         return;
//     }
//     if (dir == DIR_DOWN) {
//         std::cout << "You look down. Cold concrete floor with scattered dust." << std::endl;
//         return;
//     }
//
//     // For horizontal directions, describe based on position + direction
//     // You can start simple and expand later:
//
//     if (dir == DIR_NORTH) {
//         // What's on the NORTH wall from this position?
//         switch(pos) {
//             case POS_CENTER:
//                 cout << "You see the exit door ahead with a green EXIT sign." << endl;
//                 break;
//             case POS_FRONT:
//                 cout << "The exit door is right in front of you." << endl;
//                 break;
//             case POS_BACK:
//                 cout << "The exit door is far across the room." << endl;
//                 break;
//             // ... add more positions
//             default:
//                 cout << "You see the front wall." << endl;
//                 break;
//         }
//     }
//     else if (dir == DIR_SOUTH) {
//         switch(pos) {
//             case POS_CENTER:
//                 cout << "Behind you, a second door with no handle." << endl;
//                 break;
//             case POS_BACK:
//                 cout << "The back door is right here. No handle, no way to open." << endl;
//                 break;
//             default:
//                 cout << "You see the back wall." << endl;
//                 break;
//         }
//     }
//     else if (dir == DIR_EAST) {
//         switch(pos) {
//             case POS_CENTER:
//                 cout << "The right wall. Bare concrete." << endl;
//                 break;
//             case POS_RIGHT:
//                 cout << "You're right at the east wall." << endl;
//                 break;
//             default:
//                 cout << "You see the right wall." << endl;
//                 break;
//         }
//     }
//     else if (dir == DIR_WEST) {
//         switch(pos) {
//             case POS_CENTER:
//                 cout << "The left wall. Some writings carved into it." << endl;
//                 break;
//             case POS_LEFT:
//                 cout << "You're right at the west wall. Carved writings are visible." << endl;
//                 break;
//             default:
//                 cout << "You see the left wall." << endl;
//                 break;
//         }
//     }
// }
// ============================================================

// Helper functions for LookCommand

bool isDirection(const std::string& noun)
{
    return (noun == "north" || noun == "south" ||
            noun == "east"  || noun == "west"  ||
            noun == "up"    || noun == "down");
}

Direction toDirection(const std::string& noun)
{
    if (noun == "north") return DIR_NORTH;
    if (noun == "south") return DIR_SOUTH;
    if (noun == "east")  return DIR_EAST;
    if (noun == "west")  return DIR_WEST;
    if (noun == "up")    return DIR_UP;
    if (noun == "down")  return DIR_DOWN;
    return DIR_NORTH;  // fallback
}

Direction rotateClockwise(Direction current)
{
    switch (current) {
    case DIR_NORTH: return DIR_EAST;
    case DIR_EAST:  return DIR_SOUTH;
    case DIR_SOUTH: return DIR_WEST;
    case DIR_WEST:  return DIR_NORTH;
    default:        return current;
    }
}
Direction rotateCounterClockwise(Direction current)
{
    switch (current) {
    case DIR_NORTH: return DIR_WEST;
    case DIR_WEST:  return DIR_SOUTH;
    case DIR_SOUTH: return DIR_EAST;
    case DIR_EAST:  return DIR_NORTH;
    default:        return current;
    }
}
Direction rotateOpposite(Direction current)
{
    switch (current) {
    case DIR_NORTH: return DIR_SOUTH;
    case DIR_SOUTH: return DIR_NORTH;
    case DIR_EAST:  return DIR_WEST;
    case DIR_WEST:  return DIR_EAST;
    default:        return current;
    }
}

void LookCommand(GameState& state, const std::string& noun)
{
    Room& room = state.rooms[state.player.currentRoom];

    if (isDirection(noun))
    {
        state.player.direction = toDirection(noun);
        std::cout << "You turn face to " << noun << "." << std::endl;
        describeFacing(state);
        return;
    }

    if (noun == "right") {
        state.player.direction = rotateClockwise(state.player.direction);
        std::cout << "You look to your right." << std::endl;
        describeFacing(state);
        return;
    }
    if (noun == "left") {
        state.player.direction = rotateCounterClockwise(state.player.direction);
        std::cout << "You look to your left." << std::endl;
        describeFacing(state);
        return;
    }
    if (noun == "forward" || noun == "straight"){
        std::cout << "You look ahead." << std::endl;
        describeFacing(state);
        return;
    }
    if (noun == "behind" || noun == "back") {
        state.player.direction = rotateOpposite(state.player.direction);
        std::cout << "You look behind you." << std::endl;
        describeFacing(state);
        return;
    }

    if (noun.empty() || noun == "around") {
        // General room description
        std::cout << "=== " << room.name << " ===" << std::endl;

        // Position-specific description
        switch (state.player.position) {
            case POS_CENTER:
                std::cout << "You stand in the middle of the room next to an old wooden chair." << std::endl;
                std::cout << "A door with an EXIT sign is ahead. Walls on all sides." << std::endl;
                break;
            case POS_FRONT:
                std::cout << "You stand in front of the door. The EXIT sign glows green above." << std::endl;
                std::cout << "A note is taped to the door frame." << std::endl;
                break;
            case POS_FRONT_LEFT:
                std::cout << "You stand in left front corner of the room. " << std::endl;
                std::cout << "There few sealed electric sockets at bottom.\n"
                             " All of them are damaged and some wires dangerously exposed" << std::endl;
                break;
            case POS_FRONT_RIGHT:
                std::cout << "You stand in right front corner of the room. \n" << std::endl;
                std::cout << "On top CCTV camera is observing the room. \n"
                             "The red light indicator is blinking ." << std::endl;
                break;
            case POS_BACK:
                std::cout << "You face the back wall.\n"
                             "There a same door like on opposite side of room.\n"
                             "How ever this door doesnt have any handler or way to open it.\n" << std::endl;
                break;
            case POS_LEFT:
                std::cout << "The left wall. Bare concrete,  cold to the touch. \n"
                             "There some writings curved on the wall." << std::endl;
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

void Turn(GameState& state, const std::string& noun)
{
    // ============================================================
    // TODO STEP E: Turn command — change facing WITHOUT describing
    //
    //   if (noun.empty()) {
    //       std::cout << "Turn where?" << std::endl;
    //       return;
    //   }
    //
    //   // Absolute directions: "turn north", "turn south", etc.
    //   if (isDirection(noun)) {
    //       state.player.direction = toDirection(noun);
    //       std::cout << "You turn to face " << directionToString(state.player.direction) << "." << std::endl;
    //       return;
    //   }
    //
    //   // Relative directions: "turn left", "turn right", "turn around"
    //   if (noun == "right") {
    //       state.player.direction = rotateClockwise(state.player.direction);
    //   } else if (noun == "left") {
    //       state.player.direction = rotateCounterClockwise(state.player.direction);
    //   } else if (noun == "around" || noun == "behind") {
    //       state.player.direction = rotateOpposite(state.player.direction);
    //   } else {
    //       std::cout << "Turn where?" << std::endl;
    //       return;
    //   }
    //
    //   std::cout << "You turn to face " << directionToString(state.player.direction) << "." << std::endl;
    // ============================================================
}

void GoCommand(GameState& state, const std::string& noun)
{
    if (noun.empty()) {
        std::cout << "Go where?" << std::endl;
        return;
    }

    int pos = state.player.position;
    int row = pos / 3;    // 0=front, 1=middle, 2=back
    int col = pos % 3;    // 0=left, 1=center, 2=right
    int newPos = -1;

    // ============================================================
    // TODO STEP F: Make movement RELATIVE to facing direction
    //
    // Currently "forward" always means row-1 (towards front wall).
    // After this change, "forward" means: move in the direction
    // the player is FACING.
    //
    // Write a helper: bool tryMove(int row, int col, Direction dir, int& outNewPos)
    //   DIR_NORTH: if row > 0 -> outNewPos = (row-1)*3 + col, return true
    //   DIR_SOUTH: if row < 2 -> outNewPos = (row+1)*3 + col, return true
    //   DIR_WEST:  if col > 0 -> outNewPos = row*3 + (col-1), return true
    //   DIR_EAST:  if col < 2 -> outNewPos = row*3 + (col+1), return true
    //   else return false (hit wall)
    //
    // Then replace the if/else chain below with:
    //
    //   Direction moveDir;
    //   if (noun == "forward" || noun == "ahead") {
    //       moveDir = state.player.direction;   // facing direction
    //   } else if (noun == "back" || noun == "backward") {
    //       moveDir = rotateOpposite(state.player.direction);
    //   } else if (noun == "left") {
    //       moveDir = rotateCounterClockwise(state.player.direction);
    //   } else if (noun == "right") {
    //       moveDir = rotateClockwise(state.player.direction);
    //   } else {
    //       std::cout << "You can't go there." << std::endl;
    //       return;
    //   }
    //
    //   if (!tryMove(row, col, moveDir, newPos)) {
    //       std::cout << "You can't go that way, there's a wall." << std::endl;
    //       return;
    //   }
    // ============================================================

    // --- CURRENT (non-relative) movement — replace with above ---
    // Forward = row - 1 (up on map)
    if (noun == "forward" || noun == "ahead") {
        if (row > 0) newPos = (row - 1) * 3 + col;
        else std::cout << "You're at the front wall." << std::endl;
    }
    // Back = row + 1 (down on map)
    else if (noun == "back" || noun == "backward") {
        if (row < 2) newPos = (row + 1) * 3 + col;
        else std::cout << "You're at the back wall." << std::endl;
    }
    // Left = col - 1
    else if (noun == "left") {
        if (col > 0) newPos = row * 3 + (col - 1);
        else std::cout << "You're at the left wall." << std::endl;
    }
    // Right = col + 1
    else if (noun == "right") {
        if (col < 2) newPos = row * 3 + (col + 1);
        else std::cout << "You're at the right wall." << std::endl;
    }
    else {
        std::cout << "You can't go there." << std::endl;
        return;
    }
    // --- END of current movement ---

    // Block certain positions (e.g., dumpsters at back-left)
    // if (newPos == POS_BACK_LEFT) {
    //     std::cout << "Two large dumpster crates block the way." << std::endl;
    //     return;
    // }

    if (newPos != -1) {
        state.player.position = (Position)newPos;
        state.actionCount++;
        std::cout << "You walk " << noun << "." << std::endl;
    }
}


void ExitDoorCommand(GameState& state, const std::string& noun) {
    // Check FIRST — are you at the door
    if (state.player.position != POS_FRONT) {
        std::cout << "Exit ? yes i need to find way to do that ..." << std::endl;
        return;
    }

    // Only increment AFTER check passes
    state.loopCount++;
    state.actionCount++;
    state.player.position = POS_BACK;   // enter next room from the back door
    state.player.direction = DIR_NORTH; // look at north when as default
    std::cout << std::endl;
    std::cout << "You exit trough door and it slaps loudly once you enter..." << std::endl;
    std::cout << std::endl;
    std::cout << "Once you exit you see the exact same room in front of you." << std::endl;
    // ... rest of the narrative
}

void SmellCommand(GameState& state, const std::string& noun)
{
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

void TouchCommand(GameState& state, const std::string& noun)
{
    // ============================================================
    // TODO 4: Touch an item
    // search for item matching noun in room or inventory
    // if found: print item.touch
    // else: "You can't touch that."
    // ============================================================
}

void ListenCommand(GameState& state, const std::string& noun)
{
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

void ScreamCommand(GameState& state, const std::string& noun)
{
    std::cout << "AAAAAAARGGHHh!!!" << std::endl;
}


void ReadCommand(GameState& state, const std::string& noun)
{
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

            // if (state.player.nearObject != "door" && state.player.nearObject != "note" && noun == "note") {
            //     std::cout << "The note is too far. You can barely make out some writing." << std::endl;
            //     return;
            // }
            // check if there's anything to read
            if (state.items[i].read.empty()) {
                std::cout << "There's nothing to read on the " << noun << "." << std::endl;
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


void InventoryCommand(GameState& state ,const std::string& noun)
{
    std::cout << "=== Inventory ===" << std::endl;
    std::cout << "You are carrying nothing..." << std::endl;
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