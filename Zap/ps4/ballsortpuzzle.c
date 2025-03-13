#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h> 
#include "ballsortpuzzle.h"


int rand_index(const int avaliable_size, const bool avaliable[avaliable_size], const int excluded_count) {
    int random = rand() % (avaliable_size - excluded_count);

    int index = 0;
    for(int i = 0; i < avaliable_size; ++i) {
        if(!avaliable[i])
            continue;
        if(++index >= random)
            return i;
    }
    return 0;
}

void generator(const int rows, const int columns, char field[rows][columns]) {
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < columns; ++j)
            field[i][j] = BLANK;

    int symbols_size = (columns - 2) * rows;
    bool symbols_avaliable[symbols_size];
    for(int i = 0; i < symbols_size; ++i)
        symbols_avaliable[i] = true;
    
    int symbols_excluded_count = 0;

    int empty_cols[2];
    empty_cols[0] = rand() % columns;
    int r1 = rand() % (columns - 1);
    if (r1 < empty_cols[0]) empty_cols[1] = r1;
    else empty_cols[1] = r1 + 1;

    int j = 0;
    while (j < columns) {
        if (j == empty_cols[0] || j == empty_cols[1]) {
            j++;
            continue;
        }

        int i = 0;
        while (i < rows) {
            int index = rand_index(symbols_size, symbols_avaliable, symbols_excluded_count);
            symbols_avaliable[index] = false;
            symbols_excluded_count++;

            field[i][j] = '#' + index / rows;

            i++;
        }
        j++;
    }
}

void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y) {
    x--;
    y--;
    if (field[rows-1][x] == BLANK) {
        attron(COLOR_PAIR(3));
        printw("WRONG!\n");
        return;
    }
    if (field[0][y] != BLANK) {
        attron(COLOR_PAIR(3));
        printw("WRONG!\n");
        return;
    }
    if (x == y) {
        attron(COLOR_PAIR(3));
        printw("WRONG!\n");
        return;
    }

    char SOURCE_CHAR;
    int CounterOne = 0;
    for (; field[CounterOne][x] == BLANK; CounterOne++) {
        continue;
    }

    SOURCE_CHAR = field[CounterOne][x];

    if (field[rows-1][y] == BLANK) {
        field[rows-1][y] = SOURCE_CHAR;
        field[CounterOne][x] = BLANK;
        return;
    }

    int CounterTwo = 0;
    for (; field[CounterTwo][y] == BLANK; CounterTwo++) {
        continue;
    }
    if (field[CounterTwo][y] != SOURCE_CHAR) {
        attron(COLOR_PAIR(3));
        printw("WRONG!\n");
        return;
    }

    field[CounterOne][x] = BLANK;
    CounterTwo -= 1;
    field[CounterTwo][y] = SOURCE_CHAR;
}

bool check(const int rows, const int columns, char field[rows][columns]) {
    int x = 0;
    while (x < columns) {
        char y = field[0][x];
        int yy = 1;
        while (yy < rows) {
            if (field[yy][x] != y) {
                return 0;
            }
            yy++;
        }
        x++;
    }
    return 1;
}


void game_field(const int rows, const int columns, char field[rows][columns]) {
    for(int i = 0; i < rows; ++i) {
        attron(COLOR_PAIR(4));
        printw(" %d", i + 1);
        attron(COLOR_PAIR(7));
        printw(" |");

     for(int j = 0; j < columns; ++j) {
            int col = field[i][j] - '#';
            while(col >= 7) col -= 7;
            
            attron(COLOR_PAIR(3 + col));
            printw(" %c", field[i][j]);
            attron(COLOR_PAIR(7));
            printw(" |");
        }
        printw("\n");
    }

    attron(COLOR_PAIR(7));
    printw("   ");
    for(int j = 0; j < columns; ++j)
        printw("+---");
    printw("+\n");

    attron(COLOR_PAIR(4));
    printw("   ");
    for(int j = 0; j < columns; ++j)
        printw("  %d ", j + 1);
    printw("\n");
}




void ball_sort_puzzle() {
    const int rows = 5, columns = 7;
    char field[rows][columns];
    generator(rows, columns, field);
    game_field(rows, columns, field);
    refresh();

    int origin, destination;
    while(!check(rows, columns, field)) {
        attron(COLOR_PAIR(5));
        printw("Enter where to get: ");
        refresh();
        attron(COLOR_PAIR(1));
        scanw("%d", &origin);
        
        attron(COLOR_PAIR(6));
        printw("Enter where to put: ");
        refresh();
        attron(COLOR_PAIR(1));
        scanw("%d", &destination);

        down_possible(rows, columns, field, origin, destination);
        printw("\n");
        game_field(rows, columns, field);
        refresh();
    }

    attron(COLOR_PAIR(5));
    printw("\nCongratulations! You won!\n");
    refresh();
    getch();
}