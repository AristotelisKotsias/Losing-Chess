#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include <sstream>

#include "ChessBoard.h"
#include "ChessMove.h"

using std::cout;
using std::endl;
using std::stringstream;
using std::vector;

int playGame(string color, string ai) {
    ChessBoard chess;
    stringstream s;
    s << "RNBKQBNR" << endl;
    s << "PPPPPPPP" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "pppppppp" << endl;
    s << "rnbqkbnr" << endl;

    s >> chess;

    //true = white player
    if (color == "white" && ai == "naive") {
        int counter = 0;
        for (;;) {
            cout << "------------ROUND: " << counter + 1 << "-------------" << endl;
            chess.naiveAI(true);
            chess.prettyPrint();
            if (!chess.gameOver(false)) {
                cout << "White won\n"
                     << endl;
                return -1;
            }

            chess.smartAI(false);
            chess.prettyPrint();
            if (!chess.gameOver(true)) {
                cout << "Black won\n"
                     << endl;
                return -1;
            }
            counter++;
        }
    } else if (color == "white" && ai == "smart") {
        int counter = 0;
        for (;;) {
            cout << "------------ROUND: " << counter + 1 << "-------------" << endl;
            chess.smartAI(true);
            chess.prettyPrint();
            if (!chess.gameOver(false)) {
                cout << "White won\n"
                     << endl;
                return -1;
            }
            chess.naiveAI(false);
            chess.prettyPrint();
            if (!chess.gameOver(true)) {
                cout << "Black won\n"
                     << endl;
                return -1;
            }
            counter++;
        }
    } else if (color == "black" && ai == "naive") {
        int counter = 0;
        for (;;) {
            cout << "------------ROUND: " << counter + 1 << "-------------" << endl;
            chess.smartAI(true);
            chess.prettyPrint();
            if (!chess.gameOver(false)) {
                cout << "White won\n"
                     << endl;
                return -1;
            }
            chess.naiveAI(false);
            chess.prettyPrint();
            if (!chess.gameOver(true)) {
                cout << "Black won\n"
                     << endl;
                return -1;
            }
            counter++;
        }
    } else {
        int counter = 0;
        for (;;) {
            cout << "------------ROUND: " << counter + 1 << "-------------" << endl;
            chess.naiveAI(true);
            chess.prettyPrint();
            if (!chess.gameOver(false)) {
                cout << "White won\n"
                     << endl;
                return -1;
            }
            chess.smartAI(false);
            chess.prettyPrint();
            if (!chess.gameOver(true)) {
                cout << "Black won\n"
                     << endl;
                return -1;
            }
            counter++;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Incorrect number of arguments" << endl;
        return -1;
    }
    string color = argv[1];
    string ai = argv[2];
    playGame(color, ai);

    return 0;
}
