/**
 * ohhi.cpp
 *
 * EECS 183, Winter 2015
 * Project 4: 0h h1
 *
 * Allan Chen, Hsin-Chien Tsai
 * allanmc, thchien
 *
 * Contains all the function definitions used in main.cpp and declared in
 * helpers.h.  Ohhi.cpp also contains utility functions from helpers.cpp
 */

#include "ohhi.h"

void print_board(const int board[MAX_SIZE][MAX_SIZE], int size) {
    
    //for loop for row
    for (int i = 0; i < size; i++) {
        
        cout << endl;
        
        //for loop for column
        for (int j = 0; j < size; j++) {
            
            if (board[i][j] == RED) {
                
                cout << "R";
            }
            if (board[i][j] == BLUE) {
                
                cout << "B";
            }
            else if (board[i][j] == UNKNOWN) {
                
                cout << "-";
            }
        }
    }
}

bool row_has_no_threes_of_color(const int board[MAX_SIZE][MAX_SIZE],
                                int size,
                                int row,
                                int color) {
    
    //loop for column.  Size - 2 to avoid out of index error.
    for (int j = 0; j < size - 2; j++) {
        
        //if there are three consecutive colors in a row, return false.
        //else return true.
        if (board[row][j] == color && board[row][j + 1] == color &&
            board[row][j + 2] == color) {
            
            return false;
        }
    }
    return true;
}

bool col_has_no_threes_of_color(const int board[MAX_SIZE][MAX_SIZE],
                                int size,
                                int col,
                                int color) {
    
    //loop for row.  Size - 2 to avoid out of index error
    for (int i = 0; i < size - 2; i++) {
        
        //if there are three consecutive colors in a column, return false.
        //else return true.
        if (board[i][col] == color && board[i + 1][col] == color &&
            board[i + 2][col] == color) {
            
            return false;
        }
    }
    return true;
}

bool board_has_no_threes(const int board[MAX_SIZE][MAX_SIZE], int size) {
    
    //for loop for row.
    for (int row = 0; row < size; row++) {
        
        //if row_has_no_threes returns false for either RED or BLUE,return false
        if (!(row_has_no_threes_of_color(board, size, row, RED) &&
              row_has_no_threes_of_color(board, size, row, BLUE))) {
            
            return false;
        }
    }
    
    //for loop for column
    for (int col = 0; col < size; col++) {
        
        //if column_has_no_threes returns false for RED/BLUE, return false
        if (!(col_has_no_threes_of_color(board, size, col, RED) &&
              col_has_no_threes_of_color(board, size, col, BLUE))) {
            
            return false;
        }
    }
    return true;
}

bool rows_are_different(const int board[MAX_SIZE][MAX_SIZE],
                        int size,
                        int row1,
                        int row2) {
    
    //loop just for column
    for (int j = 0; j < size; j++) {
        
        //returns true if either row1 or row2 contains an UNKNOWN
        //OR row1 and row2 have different squares.  Else return false.
        if ((!(board[row1][j] == board[row2][j])) ||
            ((board[row1][j] == UNKNOWN || board[row2][j] == UNKNOWN))) {
            
            return true;
        }
    }
    return false;
}

bool cols_are_different(const int board[MAX_SIZE][MAX_SIZE],
                        int size,
                        int col1,
                        int col2) {
    
    //for loop just for row
    for (int i = 0; i < size; i++) {
        
        //returns true if either col1 or col2 contains an UNKNOWN
        //OR col1 and col2 have different squares.  Else return false.
        if ((!(board[i][col1] == board[i][col2])) ||
            ((board[i][col1] == UNKNOWN || board[i][col2] == UNKNOWN))) {
            
            return true;
        }
    }
    return false;
}

bool board_has_no_duplicates(const int board[MAX_SIZE][MAX_SIZE], int size) {
    
    //loop for row1 and col1.
    for (int i = 0; i < size; i++) {
        
        //loop for row2 and col2
        for (int j = 0; j < size; j++) {
            
            //if i and j are the same numbers, board_has_no_duplicates will stop
            //and always return false.  Must check when i and j aren't the same
            if (i != j) {
                
                //if two rows are the same, return false
                if (!rows_are_different(board, size, i, j)) {
                    
                    return false;
                }
                
                //if two cols are the same, return false
                if (!cols_are_different(board, size, i, j)) {
                    
                    return false;
                }
            }
        }
    }
    return true;
}

void solve_three_in_a_row(int board[MAX_SIZE][MAX_SIZE],
                          int size,
                          int row) {
    
    //size - 1 to avoid out of index error
    for (int j = 0; j < size - 1; j++) {
        
        
        //size - 3 to avoid out of index error
        if (j < size - 3) {
            
            //solve -RR-
            if (board[row][j] == UNKNOWN &&
                (board[row][j + 1] == board[row][j + 2]) &&
                (board[row][j + 1] != UNKNOWN) &&
                board[row][j + 3] == UNKNOWN) {
                
                //calls opposite_color function to figure out which color to use
                mark_square_as(board, size, row, j,
                               opposite_color(board[row][j + 1]));
                
                mark_square_as(board, size, row, j + 3,
                               opposite_color(board[row][j + 1]));
                
            }
        }
        
        //size - 2 to avoid out of index error
        if (j < size - 2) {
            
            //solve -R-R
            if (board[row][j] == board[row][j + 2] && board[row][j] != UNKNOWN
                && board[row][j + 1] == UNKNOWN) {
                
                mark_square_as(board, size, row, j + 1,
                               opposite_color(board[row][j]));
            }
        }
        
        //j + 2 to determine when to execute for --RR
        if (j + 2 == size) {
            
            //solve --RR
            if (board[row][j] == board[row][j + 1] &&
                board[row][j] != UNKNOWN &&
                board[row][j - 1] == UNKNOWN) {
                
                mark_square_as(board, size, row, j - 1,
                               opposite_color(board[row][j]));
                
            }
        }
        
        //size - 2 to avoid out of index error
        if (j < size - 2) {
            
            //solve RR--
            if (board[row][j] == board[row][j + 1] && board[row][j] != UNKNOWN
                && board[row][j + 2] == UNKNOWN) {
                
                mark_square_as(board, size, row, j + 2,
                               opposite_color(board[row][j]));
                
            }
        }
    }
}

void solve_three_in_a_column(int board[MAX_SIZE][MAX_SIZE],
                             int size,
                             int col) {
    
    //size - 3 to avoid out of index error
    for (int i = 0; i < size - 3; i++) {
        
        //solve -
        //      R
        //      R
        //      -
        if (board[i][col] == UNKNOWN && board[i + 1][col] ==
            board[i + 2][col] && board[i + 1][col] != UNKNOWN
            && board[i + 3][col] == UNKNOWN) {
            
            //cals opposite_color function to select which color to fill in
            mark_square_as(board, size, i, col,
                           opposite_color(board[i + 1][col]));
            
            mark_square_as(board, size, i + 3, col,
                           opposite_color(board[i + 1][col]));
            
        }
    }
    
    //size - 2 to avoid out of index error
    for (int i = 0; i < size - 2; i++) {
        
        //solve R
        //      R
        //      -
        //      -
        if (board[i][col] == board[i + 1][col] &&
            board[i][col] != UNKNOWN && board[i + 2][col] == UNKNOWN) {
            
            mark_square_as(board, size, i + 2, col,
                           opposite_color(board[i][col]));
            
        }
    }
    
    //size - 1 to avoid out of index error
    for (int i = 0; i < size - 1; i++) {
        
        //i + 2 to determine when to execute.
        if (i + 2 == size) {
            
            //solve -
            //      -
            //      R
            //      R
            if (board[i][col] == board[i + 1][col] && board[i][col] != UNKNOWN
                && board[i - 1][col] == UNKNOWN) {
                
                mark_square_as(board, size, i - 1, col,
                               opposite_color(board[i][col]));
            }
        }
    }
    
    //size - 2 to avoid out of index error
    for (int i = 0; i < size - 2; i++) {
        
        //solve -
        //      R
        //      -
        //      R
        if (board[i][col] == board[i + 2][col] && board[i][col] != UNKNOWN
            && board[i + 1][col] == UNKNOWN) {
            
            mark_square_as(board, size, i + 1, col,
                           opposite_color(board[i][col]));
            
        }
    }
}


void solve_balance_row(int board[MAX_SIZE][MAX_SIZE], int size, int row) {
    
    //variable that counts RED and BLUE squares in row
    int redcount = 0;
    int bluecount = 0;
    
    //bool variable that is changed depending on if row is half filled.
    bool halfrow = false;
    
    //checks if row is half filled with RED.  If it is, assign halfrow as true
    for (int j = 0; j < size; j++) {
        
        if (board[row][j] == RED) {
            
            redcount += 1;
        }
        
        if (redcount == size / 2) {
            
            halfrow = true;
        }
    }
    
    //if halfrow is true, new loop iterates and finds locations of empty spaces
    //then calls mark square function to fill in those empty squares with BLUE
    if (halfrow == true) {
        
        for (int j = 0; j < size; j++) {
            
            if (board[row][j] == UNKNOWN) {
                
                mark_square_as(board, size, row, j, BLUE);
            }
        }
    }
    
    //checks if row is half filled with BLUE.  If it is, assign halfrow as true
    for (int j = 0; j < size; j++) {
        
        if (board[row][j] == BLUE) {
            
            bluecount += 1;
        }
        
        if (bluecount == size / 2) {
            
            halfrow = true;
        }
    }
    
    //if halfrow is true for BLUE, find empty squares and fill with RED
    if (halfrow == true) {
        
        for (int j = 0; j < size; j++) {
            
            if (board[row][j] == UNKNOWN) {
                
                mark_square_as(board, size, row, j, RED);
            }
        }
    }
}



void solve_balance_column(int board[MAX_SIZE][MAX_SIZE], int size, int col) {
    
    //initialize count variables
    int redcount = 0;
    int bluecount = 0;
    
    //initialize bool variable
    bool halfcolumn = false;
    
    //checks to see if column is half filled with RED.
    for (int i = 0; i < size; i++) {
        
        if (board[i][col] == RED) {
            
            redcount += 1;
        }
        
        if (redcount == size / 2) {
            
            halfcolumn = true;
        }
    }
    
    //if halfcolumn is true, find empty spaces and fill in with BLUE
    if (halfcolumn == true) {
        
        for (int i = 0; i < size; i++) {
            
            if (board[i][col] == UNKNOWN) {
                
                mark_square_as(board, size, i, col, BLUE);
            }
        }
    }
    
    //check if column is half filled with BLUE.
    for (int i = 0; i < size; i++) {
        
        if (board[i][col] == BLUE) {
            
            bluecount += 1;
        }
        
        if (bluecount == size / 2) {
            
            halfcolumn = true;
        }
    }
    
    //if halfcolumn is true, find empty spaces and fill in with RED
    if (halfcolumn == true) {
        
        for (int i = 0; i < size; i++) {
            
            if (board[i][col] == UNKNOWN) {
                
                mark_square_as(board, size, i, col, RED);
            }
        }
    }
}


void solve_lookahead_row(int board[MAX_SIZE][MAX_SIZE],
                         int size,
                         int row) {
    // THIS IS ONLY NEEDED FOR S'MORE
    // your code here
}

void solve_lookahead_column(int board[MAX_SIZE][MAX_SIZE],
                            int size,
                            int col) {
    // THIS IS ONLY NEEDED FOR S'MORE
    // your code here
}
