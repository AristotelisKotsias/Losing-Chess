#ifndef QUEEN_H
#define QUEEN_H

#include "Bishop.h"
#include "ChessPiece.h"
#include "Rook.h"

class Queen : public Bishop, public Rook {
   protected:
    int validMove(int to_x, int to_y) override;
    string utfRepresentation() override;
    char latin1Representation() override;

   public:
    Queen(int x, int y, bool isWhite, string name, ChessBoard* board);
    ~Queen() override;
};

#endif