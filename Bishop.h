#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

class Bishop : virtual public ChessPiece {
   protected:
    int validMove(int to_x, int to_y) override;
    string utfRepresentation() override;
    char latin1Representation() override;

   public:
    using ChessPiece::ChessPiece;
    ~Bishop() override;
};

#endif