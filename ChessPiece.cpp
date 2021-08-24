#include "ChessPiece.h"

#include <memory>
#include <vector>

#include "Bishop.h"
#include "ChessBoard.h"
#include "ChessMove.h"
#include "Knight.h"
#include "Queen.h"
#include "Rook.h"

using namespace std;

ChessPiece::ChessPiece(int x, int y, bool isWhite, string name, ChessBoard* board)
    : x(x), y(y), isWhite(isWhite), name(name), board(board) {
}

ChessPiece::~ChessPiece() {}

bool ChessPiece::capturingMove(int to_x, int to_y) {
    return (this->validMove(to_x, to_y) == 2) ? true : false;
}

bool ChessPiece::nonCapturingMove(int to_x, int to_y) {
    return (this->validMove(to_x, to_y) == 1) ? true : false;
}

vector<ChessMove> ChessPiece::capturingMoves() {
    vector<ChessMove> cm;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (this->capturingMove(x, y)) {
                ChessMove move = {
                    this->x,
                    this->y,
                    x,
                    y,
                    this->board->getBoard().get(this->x, this->y)};
                cm.push_back(move);
            }
        }
    }
    return cm;
}

vector<ChessMove> ChessPiece::nonCapturingMoves() {
    vector<ChessMove> cm;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (this->nonCapturingMove(x, y)) {
                ChessMove move = {
                    this->x,
                    this->y,
                    x,
                    y,
                    this->board->getBoard().get(this->x, this->y)};
                cm.push_back(move);
            }
        }
    }
    return cm;
}
