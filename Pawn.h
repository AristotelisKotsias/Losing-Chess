#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

class Pawn : public ChessPiece {
   protected:
    int validMove(int to_x, int to_y) override;
    string utfRepresentation() override;
    char latin1Representation() override;

   public:
    std::string name = "Pawn";
    using ChessPiece::ChessPiece;
    ~Pawn() override;
};

#endif