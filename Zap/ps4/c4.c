#include <stdio.h>
#include <stdbool.h>
#include <curses.h>
#include "c4.h"

#define PLAYER_1 'X'
#define PLAYER_2 'O'

void initialize_board(int rows, int cols, char board[rows][cols]){
    for(int row = 0; row < rows; row++){
        for(int col = 0; col < cols; col++){
            board[row][col] = '.';
        }
    }
}

void print_board(int rows, int cols, const char board[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            attron(COLOR_PAIR(2));
            printw("| ");
            if(board[i][j] == PLAYER_1) attron(COLOR_PAIR(3));
            else if(board[i][j] == PLAYER_2) attron(COLOR_PAIR(7));
            else if(board[i][j] == '.') attron(COLOR_PAIR(1));
            printw("%c ", board[i][j]);
        }
        attron(COLOR_PAIR(2));
        printw("|\n");
    }
    for (int j = 0; j < cols; j++) {
        attron(COLOR_PAIR(2));
        printw("+---");
    }
    attron(COLOR_PAIR(2));
    printw("+\n"); // Лінія під рядком
    refresh(); // Оновлює екран
}


int is_valid_move(int rows, int cols, const char board[rows][cols], int col){
    if (!(col > 0 && col <= cols)) {
        return 0; 
    }
    return board[0][col - 1 ] == '.';
}


int drop_piece(int rows, int cols, char board[rows][cols], int col, char player_piece){
    col--;
    rows--;
    for (int i = rows; i >= 0; i--){
        if (board[i][col] == '.') {
            board[i][col] = player_piece;
            return i;
        }
    }
    return 0;
}

int check_win(int rows, int cols, const char board[rows][cols], int row, int col, char player_piece) {
    const int ways[4][2] = {
        {1, 0},   // Vertikálne (smer dolu)
        {0, 1},   // Horizontálne (smer doprava)
        {1, -1},  // Diagonála ↙
        {1, 1}    // Diagonála ↘
    };
    int win_count = 0;
    while(win_count < 4) {
        int delta_row = ways[win_count][0];
        int delta_col = ways[win_count][1];
        for (int offset = -3; offset <= 0; offset++) {
            int count = 0;
            for (int k = 0; k < 4; k++) {
                int r = row + (offset + k) * delta_row;
                int c = col + (offset + k) * delta_col;
                if (r >= 0 && r < rows && c >= 0 && c < cols && board[r][c] == player_piece) count++;
                else break;
            }
            if (count == 4) return 1; 
        }
        win_count++;
    }
    return 0; 
}


int is_board_full(int rows, int cols, const char board[rows][cols]) {
    for (int col = 0; col < cols; col++) {
        if (board[0][col] == '.') return 0;
    }
    return 1;
}

void run_c(){
    const int rows = 4, cols = 5;
    char board[rows][cols];
    initialize_board(rows, cols, board);

    print_board(rows, cols, board);
    refresh();

    int move_col;
    char player = PLAYER_1;
    while(true) {
        attron(COLOR_PAIR(4));
        printw("\nPlayer ");
        printw("%c", player);
        attron(COLOR_PAIR(4));
        printw(", enter your move (1-5): ");
        refresh();

        scanw("%d", &move_col);

        printw("\n");

        if(!is_valid_move(rows, cols, board, move_col)) {
            attron(COLOR_PAIR(7));
            printw("Invalid move!\n");
            refresh();
            print_board(rows, cols, board);
            refresh();
            continue;
        }

        int row = drop_piece(rows, cols, board, move_col, player);
        if(row < 0) {
            attron(COLOR_PAIR(7));
            printw("Failed to move!\n");
            refresh();
            print_board(rows, cols, board);
            refresh();
            continue;
        }

        print_board(rows, cols, board);
        refresh();

        if(check_win(rows, cols, board, row, move_col - 1, player)) {
            attron(COLOR_PAIR(3));
            printw("Player ");
            printw("%c", player);
            attron(COLOR_PAIR(3));
            printw(" wins!\n");
            break;
        }

        if(is_board_full(rows, cols, board)) {
            attron(COLOR_PAIR(7));
            printw("Draw!\n");
            break;
        }

        if (player == PLAYER_1) player = PLAYER_2;
        else player = PLAYER_1;
    }
}
