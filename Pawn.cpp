#include "Pawn.h"

#include <memory>

Pawn::~Pawn() {}

int Pawn::validMove(int to_x, int to_y) {
    // check what's in the "to-go" square
    shared_ptr<ChessPiece> cp = this->board->getBoard().get(to_x, to_y);

    // check if Pawn can advance forward (not attack)
    if (this->x == to_x) {
        //check if go-to square is empty
        if (cp != nullptr) {
            return 0;
        }

        // Pawn cannot advance backwards
        if ((this->isWhite && this->y > to_y) ||
            (!this->isWhite && this->y < to_y)) {
            return 0;
        }

        // advance one square infront
        if ((this->isWhite && to_y == this->y + 1) ||
            (!this->isWhite && to_y == this->y - 1)) {
            return 1;
        }

        // advance two squares infront, only from starting positions
        // Check that direct front square is empty
        if ((this->isWhite && (this->y == 1) && (to_y == this->y + 2) && (this->board->getBoard().get(to_x, to_y - 1) == nullptr)) ||
            (!this->isWhite && (this->y == 6) && (to_y == this->y - 2) && (this->board->getBoard().get(to_x, to_y + 1) == nullptr))) {
            return 1;
        }
        // check if Pawn advance diagonally (attack)
    } else if (std::abs(this->y - to_y) == 1 && (std::abs(this->x - to_x) == 1)) {
        if (cp != nullptr) {
            // check if Pawn captures an enemy piece
            if (this->isWhite != cp->isWhite) {
                return 2;
            }
        }
    }
    // if there is a piece infront of Pawn when advances two squares or if capturing piece
    // is of the same color, then return 0 (invalid move)
    return 0;
}

string Pawn::utfRepresentation() {
    return this->isWhite ? "♙" : "♟︎";
}

char Pawn::latin1Representation() {
    return this->isWhite ? 'P' : 'p';
}