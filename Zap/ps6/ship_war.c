/**
 * sudo apt update
 * sudo apt install build-essential  # Installs GCC, G++, Make, and other essential tools
**/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

/**
 * sudo apt install libncurses5-dev libncursesw5-dev
**/
#include <curses.h> 

/**
 * This is a POSIX library and is included in standard development environments on Unix-like systems. Installing the compiler usually provides this.
**/
#include <unistd.h>

#include "ship_war.h"

#define SHIP_1 '#'
#define HIT 'X'
#define MISS 'O'
#define CELL ' '

struct Ship {
    int size;
    int count;
};

void print_centered(WINDOW *win, int row, const char *text) {
    int col_width = getmaxx(win); 
    int start_col = (col_width - strlen(text)) / 2; 
    mvwprintw(win, row, start_col, "%s", text); 
}

bool check_adjacent_cells(const int width_of_see, const int length_of_see, char see_one[width_of_see][length_of_see], 
                         int row, int col, int size, int orientation) {
    if (orientation == 0) { 
        if (col + size > width_of_see) return 1; 
        for (int i = -1; i <= size; ++i) { 
            for (int j = -1; j <= 1; ++j) {
                int check_row = row + j;
                int check_col = col + i;
                if (check_row >= 0 && check_row < length_of_see && 
                    check_col >= 0 && check_col < width_of_see) {
                    if (see_one[check_row][check_col] != CELL) return 1; 
                }
            }
        }
    } else { 
        if (row + size > length_of_see) return 1; 
        for (int i = -1; i <= size; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int check_row = row + i;
                int check_col = col + j;
                if (check_row >= 0 && check_row < length_of_see && 
                    check_col >= 0 && check_col < width_of_see) {
                    if (see_one[check_row][check_col] != CELL) return 1; 
                }
            }
        }
    }
    return 0;
}


void place_ship(const int width_of_see, const int length_of_see, char see[width_of_see][length_of_see], int size, int orientation, int row, int col) {
    if (orientation == 0) { 
        for (int i = 0; i < size; ++i) {
            if (col + i >= width_of_see || see[row][col + i] != CELL) {
                return; 
            }
        }
        for (int i = 0; i < size; ++i) {
            see[row][col + i] = SHIP_1;
        }
    } else {
        for (int i = 0; i < size; ++i) {
            if (row + i >= length_of_see || see[row + i][col] != CELL) {
                return; 
            }
        }
        for (int i = 0; i < size; ++i) {
            see[row + i][col] = SHIP_1;
        }
    }
}

void initialize_see_for_players(const int width_of_see, const int length_of_see, char see_one[width_of_see][length_of_see], char see_two[width_of_see][length_of_see]){
    for(int row = 0; row < length_of_see; row++){
        for(int col = 0; col < width_of_see; col++){
            see_one[row][col] = CELL;
            see_two[row][col] = CELL;
        }
    }
}



void display_see(const int width_of_see, const int length_of_see, char see_one[width_of_see][length_of_see], char see_two[width_of_see][length_of_see]) {
    int term_width;
    term_width = getmaxx(stdscr);

    int middle_row = 0 ;
    if (middle_row < 0) middle_row = 0;

   
    int center_offset = (term_width - (length_of_see * 6 + 6)) / 2;
    if (center_offset < 0) center_offset = 0; 

    attron(COLOR_PAIR(1));
    mvprintw(middle_row, center_offset + 5, "~~X COMMANDOR REXS X~~");
    middle_row++;

    attron(COLOR_PAIR(7));
    move(middle_row++, center_offset);
    for (int i = 0; i < length_of_see; i++) {
        printw("    %d  ", i + 1);
    }
    middle_row++;

    attron(COLOR_PAIR(2));
    move(middle_row++, center_offset);
    for (int col = 0; col < length_of_see; col++) {
        printw("  +---+");
    }

    for (int row = 0; row < length_of_see; row++) {
        move(middle_row++, center_offset);
        attron(COLOR_PAIR(7));
        printw("%d", row + 1);

        for (int col = 0; col < width_of_see; col++) {
            attron(COLOR_PAIR(2));
            printw(" |");
            int x = 1;
            if (see_one[row][col] == SHIP_1)
                x = 1;
            else if (see_one[row][col] == HIT)
                x = 3;
            else if (see_one[row][col] == MISS)
                x = 4;

            attron(COLOR_PAIR(x));
            if (see_one[row][col] == SHIP_1)
                printw(" %c ", CELL);
            else
                printw(" %c ", see_one[row][col]);
            attron(COLOR_PAIR(2));
            printw("| ");
        }
        move(middle_row++, center_offset);
        for (int col = 0; col < length_of_see; col++) {
            printw("  +---+");
        }
    }

    attron(COLOR_PAIR(1));
    mvprintw(middle_row++, center_offset + 5, "VS(VERSUS)");
    attron(COLOR_PAIR(8));

    move(middle_row++, center_offset);
    for (int i = 0; i < length_of_see; i++) {
        printw("    %d  ", i + 1);
    }

    attron(COLOR_PAIR(6));
    move(middle_row++, center_offset);
    for (int col = 0; col < length_of_see; col++) {
        printw("  +---+");
    }

    for (int row = 0; row < length_of_see; row++) {
        move(middle_row++, center_offset);
        attron(COLOR_PAIR(8));
        printw("%d", row + 1);

        for (int col = 0; col < width_of_see; col++) {
            attron(COLOR_PAIR(6));
            printw(" |");
            int x = 1;
            if (see_two[row][col] == SHIP_1)
                x = 1;
            else if (see_two[row][col] == HIT)
                x = 3;
            else if (see_two[row][col] == MISS)
                x = 4;

            attron(COLOR_PAIR(x));
            printw(" %c ", see_two[row][col]);
            attron(COLOR_PAIR(6));
            printw("| ");
        }
        move(middle_row++, center_offset);
        attron(COLOR_PAIR(6));
        for (int col = 0; col < length_of_see; col++) {
            printw("  +---+");
        }
    }

    attron(COLOR_PAIR(1));
    mvprintw(middle_row++, center_offset + 5, "~~Y HAHAHAHA YOU Y~~\n");
}


void place_ships_for_PC(const int width_of_see, const int length_of_see, char see_one[width_of_see][length_of_see]) {
    struct Ship ships[] = {{4, 1}, {3, 2}, {2, 3}, {1, 4}};
    int num_ships = sizeof(ships) / sizeof(ships[0]);

    for (int i = 0; i < num_ships; ++i) {
        for (int j = 0; j < ships[i].count; ++j) {
            int row, col, orientation;

            int placed = 0; 
            while (!placed) {
                row = rand() % length_of_see;
                col = rand() % width_of_see;
                orientation = rand() % 2;
             
                if (!check_adjacent_cells(width_of_see, length_of_see, see_one, row, col, ships[i].size, orientation)) {
                    place_ship(width_of_see, length_of_see, see_one, ships[i].size, orientation, row, col);
                    placed = 1; 
                }
            }
        }
    }
}




void get_player_placement(const int width_of_see, const int length_of_see, char see_one[width_of_see][length_of_see], char see_two[width_of_see][length_of_see]) {
    struct Ship ships[] = {{4, 1}, {3, 2}, {2, 3}, {1, 4}};
    int num_ships = sizeof(ships) / sizeof(ships[0]);

    for (int i = 0; i < num_ships; i++) {
        for (int j = 0; j < ships[i].count; j++) {
            clear();
            display_see(width_of_see, length_of_see, see_one, see_two);
            int row, col, orientation;
            do {
                attron(COLOR_PAIR(1));
                printw("Enter the coordinates of the beginning of the ship(size %d)(row, column, orientation (0 - horizontal, 1 - vertical)): ", ships[i].size);
                char row_input = getch();
                if (!isdigit(row_input)) { 
                    attron(COLOR_PAIR(3));
                    printw("\nIs not valid. Try again.\n");
                    continue;
                }
                row = row_input - '0' - 1; 

                char col_input = getch();
                if (!isdigit(col_input)) { 
                    attron(COLOR_PAIR(3));
                    printw("\nIs not valid. Try again.\n");
                    continue;
                }
                col = col_input - '0' - 1;

                char orientation_input = getch();
                if(!isdigit(orientation_input)) {
                    attron(COLOR_PAIR(3));
                    printw("\nIs not valid try again.\n");
                    continue;
                }
                orientation = orientation_input  - '0' - 1;

                if(check_adjacent_cells(width_of_see, length_of_see, see_two, row, col, ships[i].size, orientation)){
                    attron(COLOR_PAIR(3));
                    printw("\nInvalid coordinates. Please try again.\n");
                }
            } while(check_adjacent_cells(width_of_see, length_of_see, see_two, row, col, ships[i].size, orientation));
            place_ship(width_of_see, length_of_see, see_two, ships[i].size, orientation, row, col);
        }
    }
}


bool is_ship_destroyed(const int width_of_see, const int length_of_see, char see[width_of_see][length_of_see], int row, int col) {
    if (see[row][col] != HIT) {
        return false;
    }

    int start_col = col, end_col = col;
    while (start_col > 0 && (see[row][start_col - 1] == HIT || see[row][start_col - 1] == SHIP_1)) {
        start_col--;
    }
    while (end_col < width_of_see - 1 && (see[row][end_col + 1] == HIT || see[row][end_col + 1] == SHIP_1)) {
        end_col++;
    }
    for (int c = start_col; c <= end_col; c++) {
        if (see[row][c] == SHIP_1) {
            return false;
        }
    }

    int start_row = row, end_row = row;
    while (start_row > 0 && (see[start_row - 1][col] == HIT || see[start_row - 1][col] == SHIP_1)) {
        start_row--;
    }
    while (end_row < length_of_see - 1 && (see[end_row + 1][col] == HIT || see[end_row + 1][col] == SHIP_1)) {
        end_row++;
    }
    for (int r = start_row; r <= end_row; r++) {
        if (see[r][col] == SHIP_1) {
            return false; 
        }
    }

    return true; 
}


void mark_surrounding_cells(const int width_of_see, const int length_of_see, char see[width_of_see][length_of_see], int row, int col) {
    int start_col = col, end_col = col;
    while (start_col > 0 && see[row][start_col - 1] == HIT) {
        start_col--;
    }
    while (end_col < width_of_see - 1 && see[row][end_col + 1] == HIT) {
        end_col++;
    }

    int start_row = row, end_row = row;
    while (start_row > 0 && see[start_row - 1][col] == HIT) {
        start_row--;
    }
    while (end_row < length_of_see - 1 && see[end_row + 1][col] == HIT) {
        end_row++;
    }

    for (int r = start_row - 1; r <= end_row + 1; r++) {
        for (int c = start_col - 1; c <= end_col + 1; c++) {
            if (r >= 0 && r < length_of_see && c >= 0 && c < width_of_see && see[r][c] == CELL) {
                see[r][c] = MISS;
            }
        }
    }
}


void take_turn(const int width_of_see, const int length_of_see, char see_one[width_of_see][length_of_see], char see_two[width_of_see][length_of_see], int *player) {
    int row, col;
    if (*player == 1) { 
        do {
            attron(COLOR_PAIR(1));
            printw("Enter the coordinates of the shot (row, column): ");
            refresh(); 
            char row_input = getch();
            if (!isdigit(row_input)) { 
                attron(COLOR_PAIR(3));
                printw("\nIs not valid. Try again.\n");
                refresh();
                continue;
            }
            row = row_input - '0' - 1; 

            char col_input = getch();
            if (!isdigit(col_input)) { 
                attron(COLOR_PAIR(3));
                printw("\nIs not valid. Try again.\n");
                refresh();
                continue;
            }
            col = col_input - '0' - 1;
            if (row < 0 || row >= length_of_see || col < 0 || col >= width_of_see) {
                attron(COLOR_PAIR(3));
                printw("\nCoordinates of the field boundaries. Try again.\n");
                refresh();
            } else if (see_one[row][col] == MISS || see_one[row][col] == HIT) { 
                attron(COLOR_PAIR(3));
                printw("\nYou have already shot at these coordinates. Try the other ones.\n");
                refresh();
            } else break;

        } while (1);

        if (see_one[row][col] == SHIP_1) {
            see_one[row][col] = HIT;
            if (is_ship_destroyed(width_of_see, length_of_see, see_one, row, col)) {
                mark_surrounding_cells(width_of_see, length_of_see, see_one, row, col);
                attron(COLOR_PAIR(3));
                printw("\nThe ship is completely destroyed!\n");
                refresh();
            }
            return;
        } else see_one[row][col] = MISS;
        *player = 0;
    } else if (*player == 0) {
        attron(COLOR_PAIR(3));
        printw("\nComputer is thinking...");
        refresh();
        sleep(2);

        do {
            row = rand() % length_of_see;
            col = rand() % width_of_see;
        } while (see_two[row][col] != CELL && see_two[row][col] != SHIP_1);

        if (see_two[row][col] == SHIP_1) {
            see_two[row][col] = HIT;
            if (is_ship_destroyed(width_of_see, length_of_see, see_two, row, col)) {
                mark_surrounding_cells(width_of_see, length_of_see, see_two, row, col);
                attron(COLOR_PAIR(3));
                printw("\nThe REXS has completely destroyed the ship!\n");
                refresh();
            }
            return;
        } else see_two[row][col] = MISS;
        *player = 1;
    }
}



bool check_win(const int width_of_see, const int length_of_see, char see[width_of_see][length_of_see]) {
    for (int i = 0; i < length_of_see; ++i) {
        for (int j = 0; j < width_of_see; ++j) {
            if (see[i][j] == SHIP_1) {
                return false; 
            }
        }
    }
    return true; 
}


int run_ship_war() {
    int size = 9;
    int player = 1;
    char see_one[size][size];
    char see_two[size][size];
    int win = 0;
    int middle_row = 0;
    initialize_see_for_players(size, size, see_one, see_two);
    attron(COLOR_PAIR(8));
    print_centered(stdscr, middle_row, "HeLLo ThIs PaRt oF GaMe GiVe YoU a cHoIcE:\n");
    attron(COLOR_PAIR(2));
    print_centered(stdscr, middle_row + 2, "A: RAnDoM PLaCeMeNt oF ShIpS(REcOmMeNdEd)\n");
    attron(COLOR_PAIR(9));
    print_centered(stdscr, middle_row + 3, "oR\n");
    attron(COLOR_PAIR(6));
    print_centered(stdscr, middle_row + 4, "B: YoU CaN PLaCe iT aS YoU WaNt(iT WoN't HeLp MuCh iN WiNnInG, ;) HE)\n");
    place_ships_for_PC(size, size, see_one);
    do{
        int input = getch();
        if (input != 'a' && input != 'b' && input != 'A' && input != 'B') {
        attron(COLOR_PAIR(3));
        printw("\nInvalid input. Try again.\n");
        continue;
        } else if(input == 'a' || input == 'A') {
            place_ships_for_PC(size, size, see_two);
            break;
        } else if(input == 'b' || input == 'B'){
            get_player_placement(size, size, see_one, see_two);
            break;
        }
    }while(1);

    while (1) {
        clear();
        display_see(size, size, see_one, see_two);
        refresh();
        take_turn(size, size, see_one, see_two, &player);       
        refresh();

        if (check_win(size, size, see_two)) {
            display_see(size, size, see_one, see_two);
            clear();
            win = 0;
            break;
        }
        if (check_win(size, size, see_one)) {
            display_see(size, size, see_one, see_two);
            clear();
            win = 1;
            break;
        }
    }
    if(win) print_centered(stdscr, middle_row, "Congratulations! You won!\n");
    else print_centered(stdscr, middle_row, "You Lose ahahahah!\n");
    print_centered(stdscr, middle_row + 1, "Press any button to return to menu.\n");
    getch();

    return win;
}

int main(){
    initscr();

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_RED);
    init_pair(4, COLOR_WHITE, COLOR_GREEN);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(8, COLOR_GREEN, COLOR_BLACK);
    init_pair(9, COLOR_RED, COLOR_BLACK);
    

    scrollok(stdscr, TRUE);
    srand(time(NULL));  
    run_ship_war();  


    endwin();
    return 0;
}