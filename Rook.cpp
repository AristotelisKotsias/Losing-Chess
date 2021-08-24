#include "Rook.h"

#include <cmath>
#include <memory>

using namespace std;

Rook::~Rook() {}

int Rook::validMove(int to_x, int to_y) {
    shared_ptr<ChessPiece> cp = this->board->getBoard().get(to_x, to_y);
    int dx = abs(to_x - this->x);
    int dy = abs(to_y - this->y);

    // check if "go-to" square contains friendly piece
    if (cp != nullptr && cp->isWhite == this->isWhite) return 0;

    // Rook can only move vertical or horizontal
    if ((this->x != to_x) && (this->y != to_y)) return 0;

    // check if there are pieces inbetween source and destination squares
    if (dx == 0) {
        for (int i = 1; i < dy; i++) {
            if (this->y < to_y) {
                if (this->board->getBoard().get(this->x, this->y + i) != nullptr) return 0;
            } else if (this->y > to_y) {
                if (this->board->getBoard().get(this->x, this->y - i) != nullptr) return 0;
            }
        }
    } else if (dy == 0) {
        for (int i = 1; i < dx; i++) {
            if (this->x < to_x) {
                if (this->board->getBoard().get(this->x + i, this->y) != nullptr) return 0;
            } else if (this->x > to_x) {
                if (this->board->getBoard().get(this->x - i, this->y) != nullptr) return 0;
            }
        }
    }

    return (cp == nullptr) ? 1 : 2;
}

string Rook::utfRepresentation() {
    return this->isWhite ? "♖" : "♜";
}

char Rook::latin1Representation() {
    return this->isWhite ? 'R' : 'r';
}