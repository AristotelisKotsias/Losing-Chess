#include <gtest/gtest.h>

#include <climits>
#include <memory>
#include <sstream>

#include "ChessBoard.h"
#include "ChessMove.h"
#include "ChessPiece.h"
#include "Queen.h"

using std::cout;
using std::endl;
using std::shared_ptr;
using std::stringstream;
using std::vector;

TEST(board1, test1) {
    ChessBoard chess;
    stringstream s;

    s << "Q..n...r" << endl;
    s << "........" << endl;
    s << "n.r....." << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s >> chess;

    vector<ChessMove> cm1 = chess.capturingMoves(true);
    vector<ChessMove> cm2 = chess.capturingMoves(false);
    shared_ptr<ChessPiece> cp = chess.getBoard().get(0, 0);
    vector<ChessMove> ncm1 = chess.nonCapturingMoves(true);
    vector<ChessMove> ncm2 = chess.nonCapturingMoves(false);
    int move1 = cp->validMove(3, 1);
    int move2 = cp->validMove(1, 0);
    int move3 = cp->validMove(3, 0);

    ASSERT_EQ(cm1.size(), 3);
    ASSERT_EQ(cm2.size(), 0);
    ASSERT_EQ(move1, 0);
    ASSERT_EQ(move2, 1);
    ASSERT_EQ(move3, 2);
    ASSERT_EQ(ncm1.size(), 4);
    ASSERT_EQ(ncm2.size(), 30);
}

TEST(board2, test2) {
    ChessBoard chess;
    stringstream s;

    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << ".r......" << endl;
    s << ".p......" << endl;
    s << "...P...n" << endl;
    s << "......P." << endl;
    s << ".N...B.." << endl;
    s >> chess;

    vector<ChessMove> cm1 = chess.capturingMoves(true);
    vector<ChessMove> cm2 = chess.capturingMoves(false);
    shared_ptr<ChessPiece> cp = chess.getBoard().get(1, 7);
    int move1 = cp->validMove(2, 5);
    int move2 = cp->validMove(0, 5);
    int move3 = cp->validMove(3, 6);

    ASSERT_EQ(cm1.size(), 1);
    ASSERT_EQ(cm2.size(), 0);
    ASSERT_EQ(move1, 1);
    ASSERT_EQ(move2, 1);
    ASSERT_EQ(move3, 1);
}

TEST(board3, test3) {
    ChessBoard chess;
    stringstream s;

    s << "q......." << endl;
    s << "....p..." << endl;
    s << "....Q..." << endl;
    s << ".r......" << endl;
    s << ".p..B..." << endl;
    s << "...P...n" << endl;
    s << "......P." << endl;
    s << "RN...B.." << endl;
    s >> chess;

    vector<ChessMove> cm1 = chess.capturingMoves(true);
    vector<ChessMove> cm2 = chess.capturingMoves(false);
    shared_ptr<ChessPiece> cp = chess.getBoard().get(6, 6);
    shared_ptr<ChessPiece> cp1 = chess.getBoard().get(0, 7);
    shared_ptr<ChessPiece> cp2 = chess.getBoard().get(0, 0);

    int move1 = cp->validMove(7, 5);
    int move2 = cp->validMove(0, 0);
    int move3 = cp->validMove(6, 5);
    int move4 = cp1->validMove(7, 7);
    int move5 = cp1->validMove(0, 6);
    int move6 = cp1->validMove(0, 0);
    int move7 = cp2->validMove(3, 2);
    int move8 = cp2->validMove(1, 1);
    int move9 = cp2->validMove(4, 4);

    ASSERT_EQ(cm1.size(), 5);
    ASSERT_EQ(cm2.size(), 2);
    ASSERT_EQ(move1, 2);
    ASSERT_EQ(move2, 0);
    ASSERT_EQ(move3, 0);
    ASSERT_EQ(move4, 0);
    ASSERT_EQ(move5, 1);
    ASSERT_EQ(move6, 2);
    ASSERT_EQ(move7, 0);
    ASSERT_EQ(move8, 1);
    ASSERT_EQ(move9, 2);
}

TEST(board4, test4) {
    ChessBoard chess;
    stringstream s;

    s << "........" << endl;
    s << ".......p" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "Q.P..pp." << endl;
    s << ".....PPP" << endl;
    s << "......NR" << endl;
    s >> chess;

    vector<ChessMove> cm1 = chess.capturingMoves(true);
    vector<ChessMove> cm2 = chess.capturingMoves(false);
    shared_ptr<ChessPiece> cp = chess.getBoard().get(6, 7);
    int move1 = cp->validMove(0, 0);
    int move2 = cp->validMove(7, 5);
    int move3 = cp->validMove(5, 5);

    ASSERT_EQ(cm1.size(), 4);
    ASSERT_EQ(cm2.size(), 3);
    ASSERT_EQ(move1, 0);
    ASSERT_EQ(move2, 1);
    ASSERT_EQ(move3, 2);
}

TEST(board5, test5) {
    ChessBoard chess;
    stringstream s;

    s << "........" << endl;
    s << "......p." << endl;
    s << ".......R" << endl;
    s << "..npn..." << endl;
    s << "...P...." << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s >> chess;

    vector<ChessMove> cm1 = chess.capturingMoves(true);
    vector<ChessMove> cm2 = chess.capturingMoves(false);
    vector<ChessMove> ncm1 = chess.nonCapturingMoves(true);
    vector<ChessMove> ncm2 = chess.nonCapturingMoves(false);

    ASSERT_EQ(cm1.size(), 2);
    ASSERT_EQ(cm2.size(), 1);
    ASSERT_EQ(ncm1.size(), 15);
    ASSERT_EQ(ncm2.size(), 18);
}

TEST(board6, test6) {
    ChessBoard chess;
    stringstream s;

    s << "RNBQKBNR" << endl;
    s << "PPPPPPPP" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "pppppppp" << endl;
    s << "rnbqkbnr" << endl;

    s >> chess;

    vector<ChessMove> cm1 = chess.capturingMoves(true);
    vector<ChessMove> cm2 = chess.capturingMoves(false);
    vector<ChessMove> ncm1 = chess.nonCapturingMoves(true);
    vector<ChessMove> ncm2 = chess.nonCapturingMoves(false);

    ASSERT_EQ(cm1.size(), 0);
    ASSERT_EQ(cm2.size(), 0);
    ASSERT_EQ(ncm1.size(), 20);
    ASSERT_EQ(ncm2.size(), 20);
}

TEST(board7, test7) {
    ChessBoard chess;
    stringstream s;
    s << "rnbqkbnr" << endl;
    s << "p.pppppp" << endl;
    s << "........" << endl;
    s << ".p......" << endl;
    s << "....P..." << endl;
    s << "........" << endl;
    s << "PPPP.PPP" << endl;
    s << "RNBQKBNR" << endl;

    s >> chess;

    vector<ChessMove> cm1 = chess.capturingMoves(true);
    vector<ChessMove> cm2 = chess.capturingMoves(false);

    shared_ptr<ChessPiece> cp = chess.getBoard().get(1, 0);

    int move1 = cp->validMove(0, 0);
    int move2 = cp->validMove(0, 2);
    int move3 = cp->validMove(2, 2);

    ASSERT_EQ(cm1.size(), 1);
    ASSERT_EQ(cm2.size(), 0);
    ASSERT_EQ(move1, 0);
    ASSERT_EQ(move2, 1);
    ASSERT_EQ(move3, 1);
}

TEST(board8, test8) {
    ChessBoard chess;
    stringstream s;
    s << "Kb......" << endl;
    s << "nn......" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;

    s >> chess;

    vector<ChessMove> cm1 = chess.capturingMoves(true);
    vector<ChessMove> cm2 = chess.capturingMoves(false);

    shared_ptr<ChessPiece> cp = chess.getBoard().get(0, 0);

    int move1 = cp->validMove(7, 7);
    int move2 = cp->validMove(1, 0);
    int move3 = cp->validMove(1, 1);

    ASSERT_EQ(cm1.size(), 3);
    ASSERT_EQ(cm2.size(), 0);
    ASSERT_EQ(move1, 0);
    ASSERT_EQ(move2, 2);
    ASSERT_EQ(move3, 2);
}

TEST(board9, test9) {
    ChessBoard chess;
    stringstream s;
    s << ".....Q.." << endl;
    s << "...q...." << endl;
    s << "......Q." << endl;
    s << "q......." << endl;
    s << ".......Q" << endl;
    s << ".q......" << endl;
    s << "....Q..." << endl;
    s << "..q....." << endl;

    s >> chess;

    vector<ChessMove> cm1 = chess.capturingMoves(true);
    vector<ChessMove> cm2 = chess.capturingMoves(false);

    shared_ptr<ChessPiece> cp = chess.getBoard().get(5, 0);

    int move1 = cp->validMove(7, 7);
    int move2 = cp->validMove(7, 0);
    int move3 = cp->validMove(5, 1);

    ASSERT_EQ(cm1.size(), 0);
    ASSERT_EQ(cm2.size(), 0);
    ASSERT_EQ(move1, 0);
    ASSERT_EQ(move2, 1);
    ASSERT_EQ(move3, 1);
}

TEST(board10, test10) {
    ChessBoard chess;
    stringstream s;
    s << "R..n...." << endl;
    s << "bn......" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;

    s >> chess;

    vector<ChessMove> cm1 = chess.capturingMoves(true);
    vector<ChessMove> cm2 = chess.capturingMoves(false);

    shared_ptr<ChessPiece> cp = chess.getBoard().get(0, 0);

    int move1 = cp->validMove(7, 7);
    int move2 = cp->validMove(1, 0);
    int move3 = cp->validMove(3, 0);

    ASSERT_EQ(cm1.size(), 2);
    ASSERT_EQ(cm2.size(), 0);
    ASSERT_EQ(move1, 0);
    ASSERT_EQ(move2, 1);
    ASSERT_EQ(move3, 2);
}

TEST(board11, test11) {
    ChessBoard chess;
    stringstream s;
    s << "B..n...." << endl;
    s << "bn......" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;

    s >> chess;

    vector<ChessMove> cm1 = chess.capturingMoves(true);
    vector<ChessMove> cm2 = chess.capturingMoves(false);

    shared_ptr<ChessPiece> cp = chess.getBoard().get(0, 0);

    int move1 = cp->validMove(1, 0);
    int move2 = cp->validMove(7, 7);
    int move3 = cp->validMove(1, 1);

    ASSERT_EQ(cm1.size(), 1);
    ASSERT_EQ(cm2.size(), 0);
    ASSERT_EQ(move1, 0);
    ASSERT_EQ(move2, 0);
    ASSERT_EQ(move3, 2);
}

TEST(board12, test12) {
    ChessBoard chess;
    stringstream s;
    s << "RNBQKBNR" << endl;
    s << "PPPP.PPP" << endl;
    s << "........" << endl;
    s << "....P..." << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "pppppppp" << endl;
    s << "rnbqkbnr" << endl;

    s >> chess;

    vector<ChessMove> cm1 = chess.capturingMoves(true);
    vector<ChessMove> cm2 = chess.capturingMoves(false);

    shared_ptr<ChessPiece> cp = chess.getBoard().get(1, 7);

    int move1 = cp->validMove(1, 0);
    int move2 = cp->validMove(0, 5);
    int move3 = cp->validMove(2, 5);

    ASSERT_EQ(cm1.size(), 0);
    ASSERT_EQ(cm2.size(), 0);
    ASSERT_EQ(move1, 0);
    ASSERT_EQ(move2, 1);
    ASSERT_EQ(move3, 1);
}

TEST(board13, test13) {
    ChessBoard chess;
    stringstream s;
    s << "N..n...." << endl;
    s << "bnp....." << endl;
    s << ".p......" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;

    s >> chess;

    vector<ChessMove> cm1 = chess.capturingMoves(true);
    vector<ChessMove> cm2 = chess.capturingMoves(false);

    shared_ptr<ChessPiece> cp = chess.getBoard().get(0, 1);

    int move1 = cp->validMove(7, 7);
    int move2 = cp->validMove(1, 0);
    int move3 = cp->validMove(1, 2);

    ASSERT_EQ(cm1.size(), 2);
    ASSERT_EQ(cm2.size(), 0);
    ASSERT_EQ(move1, 0);
    ASSERT_EQ(move2, 1);
    ASSERT_EQ(move3, 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}