#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

class Knight : public ChessPiece {
   protected:
    int validMove(int to_x, int to_y) override;
    string utfRepresentation() override;
    char latin1Representation() override;

   public:
    using ChessPiece::ChessPiece;
    ~Knight() override;
};

#endif