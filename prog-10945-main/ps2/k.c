#include <stdlib.h>

#include "k.h"

void add_random_tile(struct game *game){
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}


bool is_game_won(const struct game game){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(game.board[i][j] == 'K'){
                return true;
            }
        }
    }
    return false;
}


bool is_move_possible(const struct game game) {
    bool flag = false;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (game.board[i][j] == ' ') {
                flag = true;  
            }

            if (i + 1 < SIZE && game.board[i][j] == game.board[i+1][j]) {
                flag = true;
            }
            if (j + 1 < SIZE && game.board[i][j] == game.board[i][j+1]) {
                flag = true;
            }
            if (i - 1 >= 0 && game.board[i][j] == game.board[i-1][j]) {
                flag = true;
            }
            if (j - 1 >= 0 && game.board[i][j] == game.board[i][j-1]) {
                flag = true;
            }
        }
    }
    return flag;
}


bool update(struct game *game, int dy, int dx) {
    if (dx < -1 || dx > 1 || dy < -1 || dy > 1) return false;
    if (dy != 0 && dx != 0) return false;
    if (dy == 0 && dx == 0) return false;

    bool moved = false;

    int start_i = (dy == 1) ? SIZE - 1 : 0;
    int end_i = (dy == 1) ? -1 : SIZE;
    int step_i = (dy == 1) ? -1 : 1;

    int start_j = (dx == 1) ? SIZE - 1 : 0;
    int end_j = (dx == 1) ? -1 : SIZE;
    int step_j = (dx == 1) ? -1 : 1;

    for (int i = start_i; i != end_i; i += step_i) {
        for (int j = start_j; j != end_j; j += step_j) {
            if (game->board[i][j] == ' ') continue;

            int row = i;
            int col = j;
            while (true) {
                int next_row = row + dy;
                int next_col = col + dx;

                if (next_row < 0 || next_row >= SIZE || next_col < 0 || next_col >= SIZE) break;
                if (game->board[next_row][next_col] == ' ') {
                    game->board[next_row][next_col] = game->board[row][col];
                    game->board[row][col] = ' ';
                    row = next_row;
                    col = next_col;
                    moved = true;
                } 
                else if (game->board[next_row][next_col] == game->board[row][col]) {
                    game->board[next_row][next_col]++;
                    game->score += (1 << (game->board[next_row][next_col] - 'A' + 1));
                    game->board[row][col] = ' ';
                    moved = true;
                    break;
                } 
                else {
                    break;
                }
            }
        }
    }

    return moved;
}

