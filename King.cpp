#include "King.h"

#include <cmath>
#include <memory>

#include "ChessBoard.h"
#include "ChessMove.h"
#include "ChessPiece.h"

using namespace std;

King::~King() {}

int King::validMove(int to_x, int to_y) {
    shared_ptr<ChessPiece> cp = this->board->getBoard().get(to_x, to_y);
    int dx = abs(to_x - this->x);
    int dy = abs(to_y - this->y);

    // check if "go-to" square contains friendly piece
    if (cp != nullptr && cp->isWhite == this->isWhite) return 0;

    if ((dx + dy != 1) && (dx * dy != 1)) {
        return 0;
    } else if (cp == nullptr) {
        return 1;
    } else {
        return 2;
    }
}

string King::utfRepresentation() {
    return this->isWhite ? "♔" : "♚";
}

char King::latin1Representation() {
    return this->isWhite ? 'K' : 'k';
}
