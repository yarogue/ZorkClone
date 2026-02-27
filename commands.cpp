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
    std::cout << "Find a way out. The fewer actions, the better." << std::endl;
    std::cout << std::endl;
    std::cout << "=== Commands ===" << std::endl;
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

void LookCommand(GameState& state, const std::string& noun)
{
    Room& room = state.rooms[state.player.currentRoom];

    if (noun.empty() || noun == "around") {
        // print room name
        std::cout << "=== " << room.name << " ===" << std::endl;
        // print room description
        std::cout << room.description << std::endl;
        // print exits
        std::cout << "Exits:";
        for (int i = 0; i < room.exitCount; i++) {
            std::cout << " " << room.exits[i].direction;
        }
        std::cout << std::endl;

        // ============================================================
        // TODO 1: List items visible in the room
        // Loop through state.items, if item.location == currentRoom:
        //     print "You see: " + item.name
        //
        // for (int i = 0; i < state.itemCount; i++) {
        //     if (state.items[i].location == state.player.currentRoom) {
        //         std::cout << "You see: " << state.items[i].name << std::endl;
        //     }
        // }
        // ============================================================
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
    // Already near this object?
    if (state.player.nearObject == noun) {
        std::cout << "You're already near the " << noun << "." << std::endl;
        return;
    }
    // Check if noun is a valid item in room
    for (int i = 0; i < state.itemCount; i++) {
        if (state.items[i].name == noun &&
            state.items[i].location == state.player.currentRoom) {
            state.player.nearObject = noun;
            state.actionCount++;
            std::cout << "You walk over to the " << noun << "." << std::endl;
            return;
            }
    }
    std::cout << "You can't go there." << std::endl;
}

void ExitDoorCommand(GameState& state, const std::string& noun) {
    if (state.player.nearObject != "door")
    {
        std::cout << "You are not near Exit" << std::endl;
        return;
    }
    state.loopCount ++;
    state.actionCount++;
    state.player.nearObject = "";
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


// ============================================================
// NEW COMMANDS:
// ============================================================


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

            if (state.player.nearObject != "door" && state.player.nearObject != "note" && noun == "note") {
                std::cout << "The note is too far. You can barely make out some writing." << std::endl;
                return;
            }
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