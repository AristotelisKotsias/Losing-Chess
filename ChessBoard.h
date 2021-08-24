#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <memory>
#include <vector>

#include "Matris.h"

struct ChessMove;
class ChessPiece;

using std::istream;
using std::shared_ptr;
using std::string;
using std::vector;
class ChessBoard {
   private:
    Matris<shared_ptr<ChessPiece>> chessboard;

   public:
    void initBoard(Matris<shared_ptr<ChessPiece>>);
    void move_piece(ChessMove chessMove);
    void prettyPrint();
    /**
        -If there are no capturing moves, this AI will perform a non capturing at random.-
        -If there are several capturing moves, the AI will perform one of them at random.-
        -If there is a pawn promotion, a random piece will be selected.-
        */
    void naiveAI(bool isWhite);

    /** 
    -If there are no capturing moves-
        *Check if any non-capturing move will force a capturing move for the opponent.
        *If not, play a random move.
    
    -If there are several capturing moves-
        *Check if any capturing move will force a capturing move for the opponent
        *If not, play a random capturing move.
    
    -If there is a pawn promotion-
        *If possible, pick a piece that can not capture on its next move.
        *If not possible, promote to a random piece.
    */
    void smartAI(bool isWhite);
    void undoMove(ChessMove move, shared_ptr<ChessPiece> cp);
    void printInfo(ChessMove move, bool isWhite);
    bool isCaptureForEnemy(ChessMove move, bool isWhite);
    bool gameOver(bool isWhite);

    Matris<shared_ptr<ChessPiece>> getBoard();

    vector<ChessMove> capturingMoves(bool isWhite);
    vector<ChessMove> nonCapturingMoves(bool isWhite);

    shared_ptr<ChessPiece> makePiece(int x, int y, bool isWhite, string name, ChessBoard* board);
    shared_ptr<ChessPiece> promotion(int x, int y, bool isWhite, string name, ChessBoard* board);
    shared_ptr<ChessPiece> notRandomPromotion(int x, int y, bool isWhite, string name, ChessBoard* board, int i);
};

ChessBoard& operator>>(istream&, ChessBoard&);
int randomInt(int num);

#endif