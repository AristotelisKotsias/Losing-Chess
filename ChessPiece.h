#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include <gtest/gtest_prod.h>

#include "ChessBoard.h"

class ChessPiece {
    // friend classes have access to the protected members of ChessPiece
    FRIEND_TEST(board1, test1);
    FRIEND_TEST(board2, test2);
    FRIEND_TEST(board3, test3);
    FRIEND_TEST(board4, test4);
    FRIEND_TEST(board5, test5);
    FRIEND_TEST(board6, test6);
    FRIEND_TEST(board7, test7);
    FRIEND_TEST(board8, test8);
    FRIEND_TEST(board9, test9);
    FRIEND_TEST(board10, test10);
    FRIEND_TEST(board11, test11);
    FRIEND_TEST(board12, test12);
    FRIEND_TEST(board13, test13);
    friend void ChessBoard::move_piece(ChessMove p);
    friend class King;
    friend class Knight;
    friend class Pawn;
    friend class Bishop;
    friend class Rook;
    friend class Queen;
    friend class ChessBoard;

   protected:  // protected will cause problems
    int x, y;
    bool isWhite;
    string name;
    ChessBoard* board;
    /**
         * Returns 0 if target square is unreachable.
         * Returns 1 if target square is reachable and empty.
         * Returns 2 if move captures a piece.
         */
    virtual int validMove(int to_x, int to_y) = 0;
    virtual string utfRepresentation() = 0;  // may be implemented as string
    virtual char latin1Representation() = 0;

   public:
    // Constructor
    ChessPiece(int x, int y, bool isWhite, string name, ChessBoard* board);

    // Destructor
    virtual ~ChessPiece();

    //Checks if this move is valid for this piece and captures
    //a piece of the opposite color.
    bool capturingMove(int to_x, int to_y);

    //Checks if this move is valid but does not capture a piece.
    bool nonCapturingMove(int to_x, int to_y);

    virtual vector<ChessMove> capturingMoves();
    virtual vector<ChessMove> nonCapturingMoves();

    // For testing multiple inheritance
    int unnecessaryInt;
};

#endif