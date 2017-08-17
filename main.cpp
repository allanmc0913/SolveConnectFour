#include "ohhi.h"
#include <iostream>

using namespace std;

int main() {
    int board[MAX_SIZE][MAX_SIZE];
    int size = 0;

    // read the board
    size = read_board(board);
    while (size == 0) {
        cout << "starting over..." << endl;
        cout << endl;
        size = read_board(board);
    }
    cout << endl;

    // print it
    cout << "Your board is:" << endl;
    print_board(board, size);
    cout << endl;

    // check it
    bool valid = check_and_print(board, size);

    // solve it
    if (valid) {
        solve_and_print(board, size);
    }

    // technologique
    // technologique

    return 0;
}

int read_board(int board[MAX_SIZE][MAX_SIZE]) {
    cout << "What board do you want to solve?" << endl;

    // initialize size so the loop will run, but so the size is invalid
    int size = 1;
    for (int row = 0; row < size; row++) {
        string line;
        cin >> line;

        if (!line_is_valid(line)) {
            return 0;
        }

        // if we don't know the size (it's still the initial value)
        // set the size to however long the line is
        // otherwise, make sure the size matches the line we're reading
        if (size == 1) {
            size = static_cast<int>(line.length());
        } else {
            if (static_cast<int>(line.length()) != size) {
                cout << "ERROR: every row must be the same size." << endl;
                return 0;
            }
        }

        // modify the board to what the line says
        for (int col = 0; col < size; col++) {
            board[row][col] =  convert_char_to_color(line[col]);
        }
    }

    return size;
}


bool check_and_print(const int board[MAX_SIZE][MAX_SIZE], int size) {
    // print individual checks
    if (board_is_balanced(board, size)) {
        cout << "This board is balanced." << endl;
    } else {
        cout << "This board is NOT balanced." << endl;
    }
    if (board_has_no_threes(board, size)) {
        cout << "This board does not contain threes-in-a-row/column." << endl;
    } else {
        cout << "This board DOES contain threes-in-a-row/column." << endl;
    }
    if (board_has_no_duplicates(board, size)) {
        cout << "This board does not contain duplicate rows/columns." << endl;
    } else {
        cout << "This board DOES contain duplicate rows/columns." << endl;
    }
    cout << endl;

    // and print an overall validity check
    if (board_is_valid(board, size)) {
        cout << "This board is valid; solving..." << endl;
        return true;
    } else {
        cout << "This board is INVALID; quitting..." << endl;
        return false;
    }
}

void solve_and_print(int board[MAX_SIZE][MAX_SIZE], int size) {
    int unknown_squares = solve(board, size);
    cout << endl;

    if (unknown_squares == -1) {
        cout << "There is no solution to this board." << endl;
    } else if (unknown_squares == 0) {
        cout << "Solved!" << endl;
    } else {
        cout << "There may be a unique solution, but I can't find it." << endl;
    }
    print_board(board, size);
}
