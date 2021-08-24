#ifndef CHESSMOVE_H
#define CHESSMOVE_H

#include <memory>

#include "ChessPiece.h"

struct ChessMove {
    int from_x;
    int from_y;
    int to_x;
    int to_y;

    std::shared_ptr<ChessPiece> piece;  // you can change the position of the chess piece with this pointer.
};

#endif