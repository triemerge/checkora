#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Board {
public:
    char squares[64];

    Board() {
        string startPos = 
            "rnbqkbnr"
            "pppppppp"
            "........"
            "........"
            "........"
            "........"
            "PPPPPPPP"
            "RNBQKBNR";
        
        for (int i = 0; i < 64; i++) {
            squares[i] = startPos[i];
        }
    }

    int toIndex(string square) {
        int col = square[0] - 'a';
        int row = 8 - (square[1] - '0');
        return row * 8 + col;
    }

    void makeMove(string move) {
        string fromStr = move.substr(0, 2);
        string toStr = move.substr(2, 2);

        int fromIdx = toIndex(fromStr);
        int toIdx = toIndex(toStr);

        squares[toIdx] = squares[fromIdx];
        squares[fromIdx] = '.';
    }

    void printBoard() {
        cerr << "Board State:" << endl;
        for (int i = 0; i < 64; i++) {
            cerr << squares[i] << " ";
            if ((i + 1) % 8 == 0) cerr << endl;
        }
    }
};

int main() {
    Board board;
    string move;

    if (cin >> move) {
        board.makeMove(move);
        board.printBoard();
        cout << "VALID " << move << endl;
    }
    return 0;
}