#pragma once 

#include "BoardTypes.hpp"

namespace Board {

    class BoardEntity;

    namespace EntityInitializers {
        extern void initPiece(Board::BoardEntity & entity, PieceColor color, PieceType type); 
    };

};