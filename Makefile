CC = g++
FLAGS = -std=c++11 -Wall -Wextra -pedantic -O3
OBJ = main.o ChessBoard.o ChessPiece.o King.o Knight.o Pawn.o Bishop.o Rook.o Queen.o 
TOBJ = ChessBoard.o ChessPiece.o King.o Knight.o Pawn.o Bishop.o Rook.o Queen.o 

all: exe tests

tests: googletest.cpp
	${CC} ${FLAGS} ${TOBJ} googletest.cpp -lgtest -lgtest_main -pthread -o tests

exe: ${OBJ}
	${CC} ${FLAGS} ${OBJ} -o exe

%.o: %.cpp %.h ChessPiece.h
	$(CC) ${FLAGS} -c $<

main.o: ChessBoard.h
ChessPiece.o: ChessBoard.h
King.o: King.h
Knight.o: Knight.h
Pawn.o: Pawn.h
Rook.o: Rook.h
Bishop.o: Bishop.h
Queen.o: Queen.h Bishop.h Rook.h

clean:
	rm -f exe tests *.o