#include "Queen.h"

#include "ChessBoard.h"
#include "ChessPiece.h"

// Diamond inheritance problem, in order to call grandparent's parametrized
// constructor then grandparent constructor has to be called
Queen::Queen(int x, int y, bool isWhite, string name, ChessBoard* board)
    : ChessPiece(x, y, isWhite, name, board), Bishop(x, y, isWhite, name, board), Rook(x, y, isWhite, name, board) {}

Queen::~Queen() {}

int Queen::validMove(int to_x, int to_y) {
    /*  shared_ptr<ChessPiece> cp = this->board->getBoard().get(to_x, to_y);
    if (cp != nullptr) cp->unnecessaryInt = 1;
    std::cout << cp->unnecessaryInt << std::endl; */

    int bishop = Bishop::validMove(to_x, to_y);
    int rook = Rook::validMove(to_x, to_y);
    return (bishop <= rook) ? rook : bishop;
}

string Queen::utfRepresentation() {
    return this->isWhite ? "♕" : "♛";
}

char Queen::latin1Representation() {
    return this->isWhite ? 'Q' : 'q';
}