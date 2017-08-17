/***
 * ohhi.h
 *
 * EECS 183, Winter 2015
 * Project 4: 0h h1
 *
 * 0h h1 (http://www.0hh1.com/) is a sudoku-like logic puzzle.
 * This program checks the validity of a 0h h1 board.
 */

#ifndef __OHHI_H__
#define __OHHI_H__

#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>

using namespace std;

const int MAX_SIZE = 10;

const int UNKNOWN = 0;
const int RED = 1;
const int BLUE = 2;


///////////////////////////////////////
// PRINTING FUNCTIONS /////////////////
///////////////////////////////////////

/**
 * Requires: size < MAX_SIZE and size is a positive even integer.
 * Modifies: Nothing.
 * Effects : Prints a visual representation of the game board to cout. If a
 *           square is RED, 'R' should be printed; if a square is BLUE, 'B'
 *           should be printed; otherwise, a hyphen '-' should be printed.
 *           Each row of the printed board should be terminated with a
 *           newline character.
 * Used In : main()
 */
void print_board(const int board[MAX_SIZE][MAX_SIZE], int size);


///////////////////////////////////////
// VALIDITY CHECKS ////////////////////
///////////////////////////////////////

/**
 * Requires: size < MAX_SIZE and size is a positive even integer,
 *           0 <= row && row < size.
 * Modifies: Nothing.
 * Effects : Returns true if and only if the row at index row does not contain
 *           three or more consecutive tiles of the specified color.
 * Used In : board_has_no_threes()
 */
bool row_has_no_threes_of_color(const int board[MAX_SIZE][MAX_SIZE],
                                int size,
                                int row,
                                int color);

/**
 * Requires: size < MAX_SIZE and size is a positive even integer,
 *           0 <= col && col < size.
 * Modifies: Nothing.
 * Effects : Returns true if and only if the column at index col does not
 *           contain three or more consecutive tiles of the specified color.
 * Used In : board_has_no_threes()
 */
bool col_has_no_threes_of_color(const int board[MAX_SIZE][MAX_SIZE],
                                int size,
                                int col,
                                int color);

/**
 * Requires: size < MAX_SIZE and size is a positive even integer.
 * Modifies: Nothing.
 * Effects : Returns true if and only if no row or column of the board contains
 *           three or more consecutive red or blue squares.
 * Used In : board_is_valid()
 */
bool board_has_no_threes(const int board[MAX_SIZE][MAX_SIZE], int size);

/**
 * Requires: size < MAX_SIZE and size is a positive even integer,
 *           0 <= row1 && row1 < size, 0 <= row2 && row2 < size.
 * Modifies: Nothing.
 * Effects : Returns true if either
 *           * row1 or row2 contains an UNKNOWN, or
 *           * row1 and row2 have different squares.
 *
 *           Example: rows_are_different should return false for rows 0 and 1:
 *                    RBBR
 *                    RBBR
 *                    ----
 *                    ----
 *
 *           Example: rows_are_different should return true for rows 0 and 1:
 *                    RBBR
 *                    RRBB
 *                    ----
 *                    ----
 *
 *           Example: rows_are_different should return true for rows 0 and 1:
 *                    RB-R
 *                    RBBR
 *                    ----
 *                    ----
 *
 *           Example: rows_are_different should return true for rows 3 and 4:
 *                    RB-R
 *                    RBBR
 *                    ----
 *                    ----
 *
 * Used In : board_has_no_duplicates()
 */
bool rows_are_different(const int board[MAX_SIZE][MAX_SIZE],
                        int size,
                        int row1,
                        int row2);

/**
 * Requires: size < MAX_SIZE and size is a positive even integer,
 *           0 <= col1 && col1 < size, 0 <= col2 && col2 < size.
 * Modifies: Nothing.
 * Effects : Returns true if either
 *           * col1 or col2 contains an UNKNOWN, or
 *           * col1 and col2 have different squares.
 *
 *           Example: columns_are_different should return false for columns 0
 *                    and 1:
 *                    RR--
 *                    BB--
 *                    BB--
 *                    RR--
 *
 *           Example: columns_are_different should return true for columns 0
 *                    and 1:
 *                    RR--
 *                    BR--
 *                    BB--
 *                    RB--
 *
 *           Example: columns_are_different should return true for columns 0
 *                    and 1:
 *                    RR--
 *                    BB--
 *                    -B--
 *                    RR--
 *
 *           Example: columns_are_different should return true for columns 3
 *                    and 4:
 *                    RR--
 *                    BB--
 *                    -B--
 *                    RR--
 *
 * Used In : board_has_no_duplicates()
 */
bool cols_are_different(const int board[MAX_SIZE][MAX_SIZE],
                        int size,
                        int col1,
                        int col2);

/**
 * Requires: size < MAX_SIZE and size is a positive even integer.
 * Modifies: Nothing.
 * Effects : Returns true if and only if no two rows or columns of the board
 *           are identical.
 * Used In : board_is_valid()
 */
bool board_has_no_duplicates(const int board[MAX_SIZE][MAX_SIZE], int size);


///////////////////////////////////////
// SOLVING FUNCTIONS //////////////////
///////////////////////////////////////

/**
 * Requires: size < MAX_SIZE and size is a positive even integer,
 *           0 <= row && row < size. The board must be valid.
 * Modifies: board
 * Effects : There cannot be three consecutive BLUE or RED tiles. This function
 *           writes the opposite color:
 *           * on both ends of two consecutive tiles (example 1), and
 *           * in the middle between two tiles of the same color (example 2)
 *           You MUST use mark_square_as() to assign a color to a square.
 *
 *           Example:  ----              ----
 *                     RR--   becomes    RRB-
 *                     -RR-              BRRB
 *                     --R-              --R-
 *
 *           Example:  ----              ----
 *                     R-R-   becomes    RBR-
 *                     ----              ----
 *                     --R-              --R-
 * Used In : solve()
 */
void solve_three_in_a_row(int board[MAX_SIZE][MAX_SIZE], int size, int row);

/**
 * Requires: size < MAX_SIZE and size is a positive even integer,
 *           0 <= col && col < size. The board must be valid.
 * Modifies: board
 * Effects : There cannot be three consecutive BLUE or RED tiles. This function
 *           writes the opposite color:
 *           * on both ends of two consecutive tiles (example 1), and
 *           * in the middle between two tiles of the same color (example 2)
 *           You MUST use mark_square_as() to assign a color to a square.
 *
 *           Example:  ----              -B--
 *                     RR--   becomes    RRB-
 *                     -RR-              -RR-
 *                     --R-              -BR-
 *
 *           Example:  ----              ----
 *                     R-R-   becomes    R-R-
 *                     ----              --B-
 *                     --R-              --R-
 * Used In : solve()
 */
void solve_three_in_a_column(int board[MAX_SIZE][MAX_SIZE],
                             int size,
                             int col);

/**
 * Requires: size < MAX_SIZE and size is a positive even integer,
 *           0 <= row && row < size. The board must be valid.
 * Modifies: board
 * Effects : Since a valid board must contain equal numbers of BLUE and RED
 *           tiles, if either BLUE or RED tiles occupy exactly half the tiles
 *           of a row, this function will color all remaining tiles the
 *           opposite color. You MUST use mark_square_as() to assign a color
 *           to a square.
 *
 *           Example:  ----              ----
 *                     RR--   becomes    RRBB
 *                     -RR-              BRRB
 *                     --R-              --R-
 * Used In : solve()
 */
void solve_balance_row(int board[MAX_SIZE][MAX_SIZE], int size, int row);

/**
 * Requires: size < MAX_SIZE and size is a positive even integer,
 *           0 <= col && col < size. The board must be valid.
 * Modifies: board
 * Effects : Since a valid board must contain equal numbers of BLUE and RED
 *           tiles, if either BLUE or RED tiles occupy exactly half the tiles
 *           of a column, this function will color all remaining tiles the
 *           opposite color. You MUST use mark_square_as() to assign a color
 *           to a square.
 *
 *           Example:  ----              -BB-
 *                     RR--   becomes    RRB-
 *                     -RR-              -RR-
 *                     --R-              -BR-
 * Used In : solve()
 */
void solve_balance_column(int board[MAX_SIZE][MAX_SIZE], int size, int col);


///////////////////////////////////////
// S'MORE FUNCTIONS ///////////////////
///////////////////////////////////////

/**
 * Requires: size < MAX_SIZE and size is a positive even integer,
 *           0 <= col && col < size. The board must be valid.
 * Modifies: board
 * Effects : Attempts to make progress on a row through proof-by-contradiction.
 *           If the row has (size / 2) - 1 of one color, this function tries to
 *           assign that color to each UNKNOWN square to see if rules will be
 *           violated. If so, that square MUST be the opposite color.
 * Used In : main()
 */
void solve_lookahead_row(int board[MAX_SIZE][MAX_SIZE], int size, int row);

/**
 * Requires: size < MAX_SIZE and size is a positive even integer,
 *           0 <= col && col < size. The board must be valid.
 * Modifies: board
 * Effects : Attempts to make progress on a row through proof-by-contradiction.
 *           If the column has (size / 2) - 1 of one color, this function tries
 *           to assign that color to each UNKNOWN square to see if rules will
 *           be violated. If so, that square MUST be the opposite color.
 * Used In : main()
 */
void solve_lookahead_column(int board[MAX_SIZE][MAX_SIZE], int size, int col);


///////////////////////////////////////
// UTILITY FUNCTIONS //////////////////
///////////////////////////////////////

/**
 * Requires: color be one of UNKNOWN, RED, or BLUE
 * Modifies: Nothing
 * Effects : Returns the opposite color (RED for BLUE, or BLUE for RED).
 *           If the input color is UNKNOWN, returns UNKNOWN.
 */
int opposite_color(int color);

/**
 * Requires: size < MAX_SIZE and size is a positive even integer.
 * Modifies: Nothing
 * Effects : Returns number of squares in board that are UNKNOWN.
 */
int count_unknown_squares(const int board[MAX_SIZE][MAX_SIZE], int size);

/**
 * Requires: size < MAX_SIZE and size is a positive even integer.
 * Modifies: copy
 * Effects : Modifies copy to have the same colors as board.
 * Used In : Nothing.
 */
void copy_board(const int board[MAX_SIZE][MAX_SIZE],
                int copy [MAX_SIZE][MAX_SIZE],
                int size);

/**
 * Requires: size < MAX_SIZE and size is a positive even integer,
 *           0 <= row && row < size && 0 <= col && col < size.
 * Modifies: board so (row, col) becomes color
 * Effects : prints the changed square and the new color in English
 * Used In : all solving functions
 */
void mark_square_as(int board[MAX_SIZE][MAX_SIZE],
                    int size,
                    int row,
                    int col,
                    int color);

/**
 * Requires: Each string in board_string is of length size.
 * Modifies: board is changed to reflect the input.
 * Effects : Returns true if the input is valid; returns false otherwise
 * Used In : main()
 */
bool read_board_from_string(int board[MAX_SIZE][MAX_SIZE],
                            string board_string[MAX_SIZE],
                            int size);


///////////////////////////////////////
// STAFF IMPLEMENTED FUNCTIONS ////////
///////////////////////////////////////

/**
 * Requires: size < MAX_SIZE and size is a positive even integer,
 *           0 <= row && row < size.
 * Modifies: Nothing.
 * Effects : Returns true if and only if the row at board[row] can still be
 *           balanced; meaning that neither blue nor red control more than
 *           half of the tiles.
 * Used In : board_is_balanced()
 */
bool row_is_balanced(const int board[MAX_SIZE][MAX_SIZE], int size, int row);

/**
 * Requires: size < MAX_SIZE and size is a positive even integer,
 *           0 <= col && col < size.
 * Modifies: Nothing.
 * Effects : Returns true if and only if the column at board[col] can still be
 *           balanced; meaning that neither blue nor red control more than
 *           half of the tiles.
 * Used In : board_is_balanced()
 */
bool col_is_balanced(const int board[MAX_SIZE][MAX_SIZE], int size, int col);

/**
 * Requires: size < MAX_SIZE and size is a positive even integer.
 * Modifies: Nothing.
 * Effects : Returns true if and only if every row and column of the board
 *           can still be balanced.
 * Used In : board_is_valid()
 */
bool board_is_balanced(const int board[MAX_SIZE][MAX_SIZE], int size);

/**
 * Requires: size < MAX_SIZE and size is a positive even integer,
 * Modifies: nothing
 * Effects : This is the main driver for checking that a board is valid.
 *           It calls the three board-checking functions, then returns true if
 *           and only if all of those functions returns true; otherwise this
 *           function returns false
 * Used In : solve(), main()
 */
bool board_is_valid(const int board[MAX_SIZE][MAX_SIZE], int size);

/**
 * Requires: size < MAX_SIZE and size is a positive even integer,
 *           0 <= full_row && full_row < size. The board must be valid.
 * Modifies: board
 * Effects : Since a valid board cannot contain duplicate rows, if a row is
 *           almost a duplicate of another, this function will color it so the
 *           rows do not
 *           become duplicates.
 *           Example:  ----              ----
 *                     RRBB   becomes    RRBB
 *                     ----              ----
 *                     -RB-              BRBR
 * Used In : solve()
 */
void solve_duplicates_row(int board[MAX_SIZE][MAX_SIZE],
                          int size,
                          int full_row);

/**
 * Requires: size < MAX_SIZE and size is a positive even integer,
 *           0 <= full_col && full_col < size. The board must be valid.
 * Modifies: board
 * Effects : Since a valid board cannot contain duplicate columns, if a column
 *           is almost a duplicate of another, this function will color it so
 *           the rows do not become duplicates.
 *           Example:  --B-              R-B-
 *                     B-B-   becomes    B-B-
 *                     R-R-              R-R-
 *                     --R-              B-R-
 * Used In : solve()
 */
void solve_duplicates_column(int board[MAX_SIZE][MAX_SIZE],
                             int size,
                             int full_col);

/**
 * Requires: size < MAX_SIZE and size is a positive even integer,
 *           0 <= full_col && full_col < size.
 * Modifies: board
 * Effects : Since a valid board cannot contain duplicate columns, if a column
 *           is almost a duplicate of another, this function will color it so
 *           the rows do not become duplicates.
 *           Example:  --B-              R-B-
 *                     B-B-   becomes    B-B-
 *                     R-R-              R-R-
 *                     --R-              B-R-
 * Used In : solve()
 */
int solve(int board[MAX_SIZE][MAX_SIZE], int size);

/**
 * Requires: Nothing
 * Modifies: Nothing
 * Effects : Returns true if and only if the line has an even length that is
 *           less than or equal to MAX_SIZE, and only contains the
 *           characters 'R', 'B', and '-'.
 * Used In : read_board()
 */
bool line_is_valid(string line);

/**
 * Requires: symbol be either 'R', 'B', or '-'
 * Modifies: Nothing.
 * Effects : Returns the representation for RED, BLUE and UNKNOWN squares
 *           respectively.
 * Used In : read_board()
 */
int convert_char_to_color(char symbol);

/**
 * Requires: Nothing.
 * Modifies: board is changed to reflect the input.
 * Effects : Returns the size of the board if the input is valid; returns 0
 *           otherwise.
 * Used In : main()
 */
int read_board(int board[MAX_SIZE][MAX_SIZE]);

/**
 * Requires: size < MAX_SIZE and size is a positive even integer,
 *           0 <= col && col < size.
 * Modifies: Nothing.
 * Effects : Checks if the board violates any of the three rules, and prints
 *           messages accordingly. A summary message of whether the board is
 *           valid is also printed. Returns true if the board is valid, false
 *           otherwise.
 * Used In : main()
 */
bool check_and_print(const int board[MAX_SIZE][MAX_SIZE], int size);

/**
 * Requires: size < MAX_SIZE and size is a positive even integer,
 *           0 <= col && col < size.
 * Modifies: board, by filling in UNKNOWN squares through deduction by the
 *           three rules.
 * Effects : A message is printed to cout on whether the board is completely
 *           filled afterwards, or if the board is contradictory, or if the
 *           solver cannot find a solution. The final board is also printed.
 * Used In : main()
 */
void solve_and_print(int board[MAX_SIZE][MAX_SIZE], int size);

#endif
