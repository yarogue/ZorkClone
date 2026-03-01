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

void LocationCommand(GameState& state) {

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
}

void LookCommand(GameState& state, const std::string& noun)
{
    Room& room = state.rooms[state.player.currentRoom];

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
                             " The red light indicator is blinking ." << std::endl;
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

void GoCommand(GameState& state, const std::string& noun)
{
    if (noun.empty()) {
        std::cout << "Go where?" << std::endl;
        return;
    }

    int pos = state.player.position;
    int row = pos / 3;    // 0=back, 1=middle, 2=front
    int col = pos % 3;    // 0=left, 1=center, 2=right
    int newPos = -1;

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