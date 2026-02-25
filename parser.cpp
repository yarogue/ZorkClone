#include "parser.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include "types.hpp"

std::string toLowerCase(const std::string& input)
{
    std::string s = input;
    for (char & i : s)
        i = tolower(i);
    return s;
}

// ============================================================
// TODO 1: hasNumbers
// Check if a string contains any digit characters.
// Return true if any character is between '0' and '9'.
//
// bool hasNumbers(const std::string& s)
// {
//     for each character in s:
//         if character >= '0' AND character <= '9':
//             return true;
//     return false;
// }
// ============================================================


// ============================================================
// TODO 2: isStopWord
// Check if a word is a filler word we should ignore.
//
// HINT: Your current version has a bug!
// The "return false" is INSIDE the loop, so it returns
// after checking only the FIRST stop word.
// The "return false" should be AFTER the loop ends,
// meaning "I checked ALL stop words and none matched."
//
// bool isStopWord(const std::string& word)
// {
//     stopWords array = {"at", "the", "a", "an", "in", "on", "to", "with", "into"};
//
//     for each stopWord in stopWords:
//         if word == stopWord:
//             return true;        // found a match!
//                                 // do NOT return false here!
//
//     return false;               // checked all, no match
// }
// ============================================================


// ============================================================
// TODO 3: cleanNoun
// Remove stop words from the noun string.
// Use std::stringstream to split noun into words,
// keep only words that are NOT stop words.
//
// std::string cleanNoun(const std::string& noun)
// {
//     std::stringstream ss(noun);
//     std::string word;
//     std::string result;
//
//     while (ss >> word):             // read one word at a time
//         if NOT isStopWord(word):
//             result = word;          // keep the last meaningful word
//
//     return result;
// }
// ============================================================


// ============================================================
// parseInput — split input into verb + noun, then clean it
// ============================================================


Command parseInput(const std::string& input)
{
    Command cmd;

    std::string lower = toLowerCase(input);
    size_t position = lower.find(' ');

    if (position == std::string::npos)
    {
        cmd.verb = lower;
        cmd.noun = "";
    }
    else
    {
        cmd.verb = lower.substr(0, position);
        cmd.noun = input.substr(position + 1);
    }

    // TODO 4: clean the noun (remove stop words)
    // cmd.noun = cleanNoun(cmd.noun);

    return cmd;
}