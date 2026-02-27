#include "log.hpp"
#include "types.hpp"

void addToLog(GameState& state, const std::string& input)
{
    if (state.logCount < MAX_LOG) {
        state.commandLog[state.logCount] = input;
        state.logCount++;
    }
    else {
        for (int i = 0; i < MAX_LOG - 1; i++) {
            state.commandLog[i] = state.commandLog[i + 1];
        }
        state.commandLog[MAX_LOG - 1] = input;
    }
}