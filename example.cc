#include "treasure_hunt.h"
#include <cstdint>

int main() {
    Explorer<int> explorer;
    Adventurer<int, true> adventurer(17);
    Treasure<int, false> treasure1(5);
    Treasure<int, false> treasure2(6);
    SafeTreasure<int> safeTreasure(7);
    TrappedTreasure<int> trappedTreasure(10);

    Encounter<decltype(explorer), decltype(treasure1)> encounter1 = {explorer, treasure1};
    Encounter<decltype(treasure2), decltype(adventurer)> encounter2 = {treasure2, adventurer};
    Encounter<decltype(safeTreasure), decltype(explorer)> encounter3 = {safeTreasure, explorer};
    Encounter<decltype(adventurer), decltype(trappedTreasure)> encounter4 = {adventurer, trappedTreasure};
    
    expedition(encounter1, encounter2, encounter3, encounter4);
}

