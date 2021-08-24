#include "Knight.h"

#include <cmath>
#include <memory>

using namespace std;

Knight::~Knight() {}

int Knight::validMove(int to_x, int to_y) {
    shared_ptr<ChessPiece> cp = this->board->getBoard().get(to_x, to_y);
    int dx = abs(to_x - this->x);
    int dy = abs(to_y - this->y);

    // check if "go-to" square contains friendly piece
    if (cp != nullptr && cp->isWhite == this->isWhite) return 0;

    if ((pow(dx, 2) + pow(dy, 2)) != 5) return 0;

    return (cp == nullptr) ? 1 : 2;
}

string Knight::utfRepresentation() {
    return this->isWhite ? "♘" : "♞";
}

char Knight::latin1Representation() {
    return this->isWhite ? 'N' : 'n';
}
