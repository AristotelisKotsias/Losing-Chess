#include "Bishop.h"

#include <cmath>
#include <memory>

#include "ChessBoard.h"

Bishop::~Bishop() {}

int Bishop::validMove(int to_x, int to_y) {
    shared_ptr<ChessPiece> cp = this->board->getBoard().get(to_x, to_y);
    int dx = abs(to_x - this->x);
    int dy = abs(to_y - this->y);

    // check if "go-to" square contains friendly piece
    if (cp != nullptr && cp->isWhite == this->isWhite) return 0;

    // Bishop can advance only diagonally
    if (dx == dy) {
        // check if there are pieces inbetween source and destination squares
        for (int i = 1; i < dx; i++) {
            // check right up direction
            if (this->x < to_x && this->y < to_y) {
                if (this->board->getBoard().get(this->x + i, this->y + i) != nullptr) return 0;
            }
            // check right down direction
            else if (this->x<to_x&& this->y> to_y) {
                if (this->board->getBoard().get(this->x + i, this->y - i) != nullptr) return 0;
            }
            // check left up direction
            else if (this->x > to_x && this->y < to_y) {
                if (this->board->getBoard().get(this->x - i, this->y + i) != nullptr) return 0;
            }
            // check left down direction
            else if (this->x > to_x && this->y > to_y) {
                if (this->board->getBoard().get(this->x - i, this->y - i) != nullptr) return 0;
            }
        }
    } else {
        return 0;
    }

    // if no blocking pieces or friendly piece at destination square,
    // return either 1 or 2
    return (cp == nullptr) ? 1 : 2;
}

string Bishop::utfRepresentation() {
    return this->isWhite ? "♗" : "♝";
}

char Bishop::latin1Representation() {
    return this->isWhite ? 'B' : 'b';
}