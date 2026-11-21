#pragma once

#include <SpellChess/Board.h>
#include <cstdint>


inline uint64_t freezeArea(SpellChessLib::SquareIndex freezeCenter) {

    if (freezeCenter == SpellChessLib::NoSquare)   
        return 0ull;

    uint64_t result = 1ull << freezeCenter;
    if (freezeCenter % 8 != 0)
        result |= result >> 1;
    if (freezeCenter % 8 != 7)
        result |= result << 1;

    result |= (result << 8) | (result >> 8);
    return result;
};