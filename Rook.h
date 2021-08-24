#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"
class Rook : virtual public ChessPiece {
   protected:
    int validMove(int to_x, int to_y) override;
    string utfRepresentation() override;
    char latin1Representation() override;

   public:
    using ChessPiece::ChessPiece;
    ~Rook() override;
};

#endif