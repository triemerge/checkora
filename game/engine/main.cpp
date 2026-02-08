#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Board {
public:
    char squares[64];

    Board() {
        // Standard Chess Setup
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

    // Helper: Row aur Col nikalne ke liye
    int getRow(int index) { return index / 8; }
    int getCol(int index) { return index % 8; }

    bool isPawnMoveValid(int fromIdx, int toIdx, char piece) {
        int fromRow = getRow(fromIdx);
        int fromCol = getCol(fromIdx);
        int toRow = getRow(toIdx);
        int toCol = getCol(toIdx);

        int direction = (piece == 'P') ? -1 : 1; // White up (-1), Black down (+1)
        int startRow = (piece == 'P') ? 6 : 1;   // White starts row 6, Black row 1

        // 1. Sidha Chalna (Forward Move)
        if (fromCol == toCol) {
            // 1 Step Move
            if (toRow == fromRow + direction) {
                return squares[toIdx] == '.'; // Jagah khali honi chahiye
            }
            // 2 Step Move (Sirf start se)
            if (toRow == fromRow + 2 * direction && fromRow == startRow) {
                // Raste me koi nahi hona chahiye
                int midIdx = (fromIdx + toIdx) / 2; 
                return squares[toIdx] == '.' && squares[midIdx] == '.';
            }
        }
        
        // 2. Capture (Tircha Maarna) - Abhi simple rakhte hain
        if (abs(fromCol - toCol) == 1 && toRow == fromRow + direction) {
            // Target square khali nahi hona chahiye (Dushman hona chahiye)
            // Note: Abhi color check nahi kar rahe, bas piece hona chahiye
            if (squares[toIdx] != '.') return true;
        }

        return false;
    }

    bool isMoveValid(string move) {
        int fromIdx = toIndex(move.substr(0, 2));
        int toIdx = toIndex(move.substr(2, 2));
        char piece = squares[fromIdx];

        // Agar piece hi nahi hai wahan
        if (piece == '.') return false;

        // Logic routing based on piece type
        char type = tolower(piece);
        if (type == 'p') {
            return isPawnMoveValid(fromIdx, toIdx, piece);
        }

        // Baaki pieces (Rook, Knight etc.) abhi ke liye allowed hain
        return true; 
    }

    void makeMove(string move) {
        int fromIdx = toIndex(move.substr(0, 2));
        int toIdx = toIndex(move.substr(2, 2));
        squares[toIdx] = squares[fromIdx];
        squares[fromIdx] = '.';
    }

    void printBoard() {
        // Debugging board view
        cerr << "   a b c d e f g h" << endl;
        for (int i = 0; i < 8; i++) {
            cerr << (8 - i) << "  "; 
            for (int j = 0; j < 8; j++) {
                cerr << squares[i * 8 + j] << " ";
            }
            cerr << endl;
        }
    }
};

int main() {
    Board board;
    string move;

    if (cin >> move) {
        if (board.isMoveValid(move)) {
            board.makeMove(move);
            board.printBoard();
            cout << "VALID " << move << endl;
        } else {
            cout << "INVALID " << move << endl;
        }
    }
    return 0;
}