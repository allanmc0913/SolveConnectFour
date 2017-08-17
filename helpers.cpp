#include "ohhi.h"
#include <iostream>

using namespace std;


///////////////////////////////////////
// UTILITY FUNCTIONS //////////////////
///////////////////////////////////////

int opposite_color(int color) {
    if (color == RED) {
        return BLUE;
    } else if (color == BLUE) {
        return RED;
    }
    return UNKNOWN;
}

int count_unknown_squares(const int board[MAX_SIZE][MAX_SIZE], int size) {
    int result = 0;
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (board[row][col] == UNKNOWN) {
                result++;
            }
        }
    }
    return result;
}

void copy_board(const int board[MAX_SIZE][MAX_SIZE],
                int copy [MAX_SIZE][MAX_SIZE],
                int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            copy[row][col] = board[row][col];
        }
    }
}

bool line_is_valid(string line) {
    if (line.length() % 2 == 1) {
        cout << "ERROR: a board must have "
             << "an even number of squares to each side." << endl;
        return false;
    } else if (line.length() > MAX_SIZE) {
        cout << "ERROR: a board can be at most "
             << MAX_SIZE << " by " << MAX_SIZE << endl;
        return false;
    }
    for (int col = 0; col < line.length(); col++) {
        if (line[col] != 'R' && line[col] != 'B' && line[col] != '-') {
            cout << "ERROR: unknown symbol "
                 << "'" << line[col] << "'" << endl;
            return false;
        }
    }
    return true;
}

int convert_char_to_color(char symbol) {
    if (symbol == '-') {
        return UNKNOWN;
    } else if (symbol == 'R') {
        return RED;
    } else if (symbol == 'B') {
        return BLUE;
    }
    return 0;
}

bool read_board_from_string(int board[MAX_SIZE][MAX_SIZE],
                            string board_string[MAX_SIZE],
                            int size) {
    for (int row = 0; row < size; row++) {
        string line = board_string[row];

        if (!line_is_valid(line)) {
            return 0;
        }

        for (int col = 0; col < size; col++) {
            board[row][col] =  convert_char_to_color(line[col]);
        }
    }

    return size;
}


///////////////////////////////////////
// VALIDITY CHECKS ////////////////////
///////////////////////////////////////

bool row_is_balanced(const int board[MAX_SIZE][MAX_SIZE], int size, int row) {
    int red_count = 0;
    int blue_count = 0;

    // sum the contents of the row
    for (int col = 0; col < size; col++) {
        if (board[row][col] == RED) red_count++;
        else if (board[row][col] == BLUE) blue_count++;    
    }

    // check if it's possible to solve the row
    if (red_count > size / 2 || blue_count > size / 2) {
        return false;
    } else {
        return true;
    }
}

bool col_is_balanced(const int board[MAX_SIZE][MAX_SIZE], int size, int col) {
    int red_count = 0;
    int blue_count = 0;

    // sum the contents of the column
    for (int row = 0; row < size; row++) {
        if (board[row][col] == RED) red_count++;
        else if (board[row][col] == BLUE) blue_count++;    
    }

    // check if it's possible to solve the column
    if (red_count > size / 2 || blue_count > size / 2) {
        return false;
    } else {
        return true;
    }
}

bool board_is_balanced(const int board[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        // if any row or column cannot be balanced, the board is invalid
        if (!row_is_balanced(board, size, i) ||
                !col_is_balanced(board, size, i)) {
            return false;
        }
    }
    return true;
}

bool board_is_valid(const int board[MAX_SIZE][MAX_SIZE], int size) {
    return (board_is_balanced(board, size) && \
        board_has_no_threes(board, size) && \
        board_has_no_duplicates(board, size));
}


///////////////////////////////////////
// SOLVER DRIVER //////////////////////
///////////////////////////////////////

void mark_square_as(int board[MAX_SIZE][MAX_SIZE],
                    int size,
                    int row,
                    int col,
                    int color) {
    cout << "marking (" << row << ", " << col << ") as ";
    if (color == RED) {
        cout << "red";
    } else {
        cout << "blue";
    }
    cout << endl;
    board[row][col] = color;
}

void solve_duplicates_row(int board[MAX_SIZE][MAX_SIZE],
                          int size,
                          int full_row) {
    // check that the row has all of one color
    int num_red = 0;
    int num_blue = 0;
    for (int col = 0; col < size; col++) {
        if (board[full_row][col] == RED) {
            num_red++;
        } else if (board[full_row][col] == BLUE) {
            num_blue++;
        }
    }

    // if all of one color is present, that's the color we're looking for
    int color = UNKNOWN;
    if (num_red == size / 2) {
        color = RED;
    } else if (num_blue == size / 2) {
        color = BLUE;
    }

    // Find a row which has all but one of this color
    // and only has two UNKNOWN squares.
    // Since this function is called after solve_balance_row,
    // the two missing squares are guaranteed to be of different colors.
    int matching_squares = 0;
    if (color != UNKNOWN) {
        for (int other_row = 0; other_row < size; other_row++) {
            if (other_row == full_row) {
                continue;
            }
            matching_squares = 0;
            for (int col = 0; col < size; col++) {
                if (board[other_row][col] == board[full_row][col]) {
                    matching_squares += 2;
                } else {
                    matching_squares--;
                }
            }
            if (matching_squares == 2 * size - 6) {
                for (int col = 0; col < size; col++) {
                    if (board[other_row][col] == UNKNOWN) {
                        mark_square_as(board, size, other_row, col,
                                       opposite_color(board[full_row][col]));
                    }
                }
            }
        }
    }
}

void solve_duplicates_column(int board[MAX_SIZE][MAX_SIZE],
                             int size,
                             int full_col) {
    // check that the column has all of one color
    int num_red = 0;
    int num_blue = 0;
    for (int row = 0; row < size; row++) {
        if (board[row][full_col] == RED) {
            num_red++;
        } else if (board[row][full_col] == BLUE) {
            num_blue++;
        }
    }

    // if all of one color is present, that's the color we're looking for
    int color = UNKNOWN;
    if (num_red == size / 2) {
        color = RED;
    } else if (num_blue == size / 2) {
        color = BLUE;
    }

    // Find a column which has all but one of this color
    // and only has two UNKNOWN squares.
    // Since this function is called after solve_balance_column,
    // the two missing squares are guaranteed to be of different colors.
    int matching_squares = 0;
    if (color != UNKNOWN) {
        for (int other_col = 0; other_col < size; other_col++) {
            if (other_col == full_col) {
                continue;
            }
            matching_squares = 0;
            for (int row = 0; row < size; row++) {
                if (board[row][other_col] == board[row][full_col]) {
                    matching_squares += 2;
                } else {
                    matching_squares--;
                }
            }
            if (matching_squares == 2 * size - 6) {
                for (int row = 0; row < size; row++) {
                    if (board[row][other_col] == UNKNOWN) {
                        mark_square_as(board, size, row, other_col,
                                       opposite_color(board[row][full_col]));
                    }
                }
            }
        }
    }
}

int solve(int board[MAX_SIZE][MAX_SIZE], int size) {
    if (!board_is_valid(board, size)) {
        return -1;
    }

    int unknown_squares_now = count_unknown_squares(board, size);
    int unknown_squares_old = unknown_squares_now + 1;
    while (unknown_squares_now != 0 &&
            unknown_squares_old > unknown_squares_now) {
        unknown_squares_now = count_unknown_squares(board, size);
        unknown_squares_old = unknown_squares_now + 1;

        // keep blocking threes-in-a-row/column until there are
        // no more to block
        cout << "looking for threes-in-a-row/column..." << endl;
        while (unknown_squares_old > unknown_squares_now) {
            unknown_squares_old = unknown_squares_now;

            for (int row = 0; row < size; row++) {
                solve_three_in_a_row(board, size, row);
            }
            for (int col = 0; col < size; col++) {
                solve_three_in_a_column(board, size, col);
            }

            unknown_squares_now = count_unknown_squares(board, size);
        }

        // look for rows/columns with all of one color and fill in
        // the rest
        if (unknown_squares_now != 0 && unknown_squares_now != 0) {
            cout << "looking for rows/columns with half red/blue..." << endl;
            for (int row = 0; row < size; row++) {
                solve_balance_row(board, size, row);
            }
            for (int col = 0; col < size; col++) {
                solve_balance_column(board, size, col);
            }
            unknown_squares_now = count_unknown_squares(board, size);
        }

        // look for rows/columns that could be duplicates and avoid it
        if (unknown_squares_now != 0 &&
                unknown_squares_now == unknown_squares_old) {
            cout << "looking for potential duplicate rows/columns..." << endl;
            for (int row = 0; row < size; row++) {
                solve_duplicates_row(board, size, row);
            }
            for (int col = 0; col < size; col++) {
                solve_duplicates_column(board, size, col);
            }
            unknown_squares_now = count_unknown_squares(board, size);
        }

        // look for rows/columns where lookahead could apply
        // THIS IS ONLY NEEDED FOR S'MORE
        if (unknown_squares_now != 0 &&
                unknown_squares_now == unknown_squares_old) {
            cout << "looking for invalid assignments "
                 << "with look-ahead..." << endl;
            for (int row = 0; row < size; row++) {
                solve_lookahead_row(board, size, row);
            }
            for (int col = 0; col < size; col++) {
                solve_lookahead_column(board, size, col);
            }
            unknown_squares_now = count_unknown_squares(board, size);
        }
    }

    if (!board_is_valid(board, size)) {
        return -1;
    }

    return unknown_squares_now;
}
