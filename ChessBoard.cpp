#include "ChessBoard.h"

#include <stdio.h>

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <random>
#include <vector>

#include "Bishop.h"
#include "ChessMove.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

using namespace std;

Matris<shared_ptr<ChessPiece>> ChessBoard::getBoard() {
    return this->chessboard;
}

void ChessBoard::initBoard(Matris<shared_ptr<ChessPiece>> m) {
    chessboard = m;
}

void ChessBoard::move_piece(ChessMove move) {
    move.piece->x = move.to_x;
    move.piece->y = move.to_y;

    // move the piece
    this->chessboard.set(0, move.to_x + 8 * move.to_y, move.piece);

    // empty the square
    this->chessboard.set(0, move.from_x + 8 * move.from_y, nullptr);
}

vector<ChessMove> ChessBoard::capturingMoves(bool isWhite) {
    vector<ChessMove> cm;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            shared_ptr<ChessPiece> cp = this->chessboard.get(x, y);
            if (cp != nullptr && cp->isWhite == isWhite) {
                for (auto i : cp->capturingMoves()) {
                    cm.push_back(i);
                }
            }
        }
    }
    return cm;
}

vector<ChessMove> ChessBoard::nonCapturingMoves(bool isWhite) {
    vector<ChessMove> cm;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            shared_ptr<ChessPiece> cp = this->chessboard.get(x, y);

            if (cp != nullptr && cp->isWhite == isWhite) {
                for (auto i : cp->nonCapturingMoves()) {
                    cm.push_back(i);
                }
            }
        }
    }

    return cm;
}

shared_ptr<ChessPiece> ChessBoard::promotion(int x, int y, bool isWhite, string name, ChessBoard* board) {
    string names[4] = {"bishop", "knight", "queen", "rook"};
    int rand_index = randomInt(4);
    string rand_name = names[rand_index];

    if ((name == "pawn" && isWhite && y == 7) ||
        (name == "pawn" && !isWhite && y == 0)) {
        shared_ptr<ChessPiece> cp = makePiece(x, y, isWhite, rand_name, board);
        return cp;
    } else
        return nullptr;
}

shared_ptr<ChessPiece> ChessBoard::notRandomPromotion(int x, int y, bool isWhite, string name, ChessBoard* board, int i) {
    string names[4] = {"bishop", "knight", "rook", "queen"};
    int rand_index = randomInt(4);
    string rand_name = names[rand_index];

    if ((name == "pawn" && isWhite && y == 7) ||
        (name == "pawn" && !isWhite && y == 0)) {
        shared_ptr<ChessPiece> cp = makePiece(x, y, isWhite, names[i], board);
        return cp;
    } else
        return nullptr;
}

shared_ptr<ChessPiece> ChessBoard::makePiece(int x, int y, bool isWhite, string name, ChessBoard* board) {
    shared_ptr<ChessPiece> cp;
    if (name == "bishop") {
        cp = make_shared<Bishop>(x, y, isWhite, name, board);
    } else if (name == "knight") {
        cp = make_shared<Knight>(x, y, isWhite, name, board);
    } else if (name == "rook") {
        cp = make_shared<Rook>(x, y, isWhite, name, board);
    } else {
        cp = make_shared<Queen>(x, y, isWhite, name, board);
    }
    return cp;
}

void ChessBoard::naiveAI(bool isWhite) {
    vector<ChessMove> cap_moves = capturingMoves(isWhite);
    vector<ChessMove> non_cap_moves = nonCapturingMoves(isWhite);
    ChessMove move{};

    // no capturing moves available but non_capturing moves available
    if (cap_moves.size() > 0) {
        auto x = randomInt(cap_moves.size());
        move = cap_moves.at(x);
        move_piece(move);
    }
    // no non_capturing moves available but capturing moves available
    else if (non_cap_moves.size() > 0) {
        auto x = randomInt(non_cap_moves.size());
        move = non_cap_moves.at(x);
        move_piece(move);
    } else
        cout << "no moves" << endl;

    printInfo(move, isWhite);

    // check if there's a promotion
    if (move.piece != nullptr) {
        shared_ptr<ChessPiece> cp = promotion(move.to_x, move.to_y, move.piece->isWhite, move.piece->name, move.piece->board);
        if (cp != nullptr)
            this->chessboard.set(0, move.to_x + 8 * move.to_y, cp);
    }
}

void ChessBoard::undoMove(ChessMove move, shared_ptr<ChessPiece> cp_deleted) {
    move.piece->x = move.from_x;
    move.piece->y = move.from_y;

    this->chessboard.set(0, move.from_x + 8 * move.from_y, move.piece);
    this->chessboard.set(0, move.to_x + 8 * move.to_y, cp_deleted);
}

bool ChessBoard::isCaptureForEnemy(ChessMove move, bool isWhite) {
    int x = move.to_x;
    int y = move.to_y;
    shared_ptr<ChessPiece> cp;

    for (int i = 0; i < 8; i++) {
        for (int z = 0; z < 8; z++) {
            cp = this->chessboard.get(i, z);
            if (cp != nullptr && cp->isWhite != isWhite && cp->validMove(x, y) == 2) {
                return true;
            }
        }
    }
    return false;
}

void ChessBoard::smartAI(bool isWhite) {
    vector<ChessMove> cap_moves = capturingMoves(isWhite);
    vector<ChessMove> cap_moves_enemy = capturingMoves(!isWhite);
    vector<ChessMove> non_cap_moves = nonCapturingMoves(isWhite);

    ChessMove move{};
    shared_ptr<ChessPiece> cp;
    bool noCap = true;
    bool isPromoted = false;

    if (cap_moves.size() > 0) {
        for (auto i : cap_moves) {
            cp = this->chessboard.get(i.to_x, i.to_y);
            move_piece(i);
            if (isCaptureForEnemy(i, isWhite)) {
                noCap = false;
                printInfo(i, isWhite);
                break;
            } else {
                undoMove(i, cp);
            }
        }

        if (noCap) {
            auto x = randomInt(cap_moves.size());
            move = cap_moves.at(x);
            move_piece(move);
            printInfo(move, isWhite);
        }
    } else if (non_cap_moves.size() > 0) {
        for (auto i : non_cap_moves) {
            cp = this->chessboard.get(i.to_x, i.to_y);
            move_piece(i);
            if (isCaptureForEnemy(i, isWhite)) {
                noCap = false;
                printInfo(i, isWhite);
                break;
            } else {
                undoMove(i, cp);
            }
        }

        if (noCap) {
            auto x = randomInt(non_cap_moves.size());
            move = non_cap_moves.at(x);
            move_piece(move);
            printInfo(move, isWhite);
        }
    }

    //printInfo(move, isWhite);

    // check if there's a promotion
    if (move.piece != nullptr) {
        shared_ptr<ChessPiece> cp;
        vector<ChessMove> cap_moves_after_promotion;
        for (int i = 0; i < 4; i++) {
            cp = notRandomPromotion(move.to_x, move.to_y, move.piece->isWhite, move.piece->name, move.piece->board, i);

            if (cp != nullptr) this->chessboard.set(0, move.to_x + 8 * move.to_y, cp);

            cap_moves_after_promotion = capturingMoves(isWhite);
            if (cap_moves_after_promotion.size() <= cap_moves.size()) {
                isPromoted = true;
                break;
            }
        }

        if (cp != nullptr && !isPromoted) {
            cp = promotion(move.to_x, move.to_y, move.piece->isWhite, move.piece->name, move.piece->board);
            this->chessboard.set(0, move.to_x + 8 * move.to_y, cp);
        }
    }
}

void ChessBoard::printInfo(ChessMove move, bool isWhite) {
    int from_x = move.from_x;
    int from_y = move.from_y;
    int to_x = move.to_x;
    int to_y = move.to_y;

    cout << "\n";

    if (isWhite) {
        cout << "Player: White" << endl;
        cout << "Chesspiece: " << move.piece->latin1Representation() << " ("
             << move.piece->utfRepresentation() << ")" << std::endl;
        cout << "From position: (" << from_x << "," << from_y << ")" << endl;
        cout << "To position: (" << to_x << "," << to_y << ")" << endl;
    } else {
        cout << "Player: Black" << endl;
        cout << "Chesspiece: " << move.piece->latin1Representation() << " ("
             << move.piece->utfRepresentation() << ")" << std::endl;
        cout << "From position: (" << from_x << "," << from_y << ")" << endl;
        cout << "To position: (" << to_x << "," << to_y << ")" << endl;
    }
}

bool ChessBoard::gameOver(bool isWhite) {
    bool king = false;
    shared_ptr<ChessPiece> cp;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cp = this->chessboard.get(i, j);
            if (cp != nullptr && cp->name == "king" && cp->isWhite == isWhite) {
                king = true;
            }
        }
    }
    return king;
}

ChessBoard& operator>>(istream& is, ChessBoard& board) {
    // Matris chessboard is private and operator>> has no access to it
    Matris<shared_ptr<ChessPiece>> m(8);
    char c;
    int counter = 0;
    c = is.get();
    while (is) {
        if (c == '\n') {
            c = is.get();
        } else {
            int x = counter % 8;
            int y = floor(counter / 8);
            switch (c) {
                case 'K':
                    m.set(0, counter, make_shared<King>(x, y, true, "king", &board));
                    break;
                case 'k':
                    m.set(0, counter, make_shared<King>(x, y, false, "king", &board));
                    break;
                case 'Q':
                    m.set(0, counter, make_shared<Queen>(x, y, true, "queen", &board));
                    break;
                case 'q':
                    m.set(0, counter, make_shared<Queen>(x, y, false, "queen", &board));
                    break;
                case 'N':
                    m.set(0, counter, make_shared<Knight>(x, y, true, "knight", &board));
                    break;
                case 'n':
                    m.set(0, counter, make_shared<Knight>(x, y, false, "knight", &board));
                    break;
                case 'P':
                    m.set(0, counter, make_shared<Pawn>(x, y, true, "pawn", &board));
                    break;
                case 'p':
                    m.set(0, counter, make_shared<Pawn>(x, y, false, "pawn", &board));
                    break;
                case 'B':
                    m.set(0, counter, make_shared<Bishop>(x, y, true, "bishop", &board));
                    break;
                case 'b':
                    m.set(0, counter, make_shared<Bishop>(x, y, false, "bishop", &board));
                    break;
                case 'R':
                    m.set(0, counter, make_shared<Rook>(x, y, true, "rook", &board));
                    break;
                case 'r':
                    m.set(0, counter, make_shared<Rook>(x, y, false, "rook", &board));
                    break;
                default:
                    m.set(0, counter, nullptr);
            }
            counter++;
            c = is.get();
        }
    }

    // Initialize the board§
    board.initBoard(m);
    return board;
}

void ChessBoard::prettyPrint() {
    int i, j;
    cout << " ---------------------------------\n";
    for (i = 0; i < 8; ++i) {
        cout << " | ";
        for (j = 0; j < 8; ++j) {
            if (!chessboard[i * 8 + j])
                cout << " "
                     << " | ";
            else {
                cout << chessboard[i * 8 + j]->utfRepresentation() << " | ";
            }
        }
        cout << "\n ---------------------------------\n";
    }
    cout << "\n";
}

int randomInt(int num) {
    srand(time(NULL));
    unsigned x = rand() % num;
    return x;
}