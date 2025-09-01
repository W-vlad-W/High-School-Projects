#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "k.h"
#include "hof.h"
#include "ui.h"

int main() {
    struct game game = {
        .board = {
            {'A', 'B', 'C', 'D'},
            {'E', 'F', 'G', 'H'},
            {'I', 'J', 'K', 'A'},
            {'B', 'C', 'D', 'E'}
        },
        .score = 0
    };

    printf("is won: %d\n", is_game_won(game));

    // Použitie memcpy na zmenu obsahu štruktúry
    struct game new_game1 = {
        .board = {
            {'A', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', 'A'},
            {'B', ' ', ' ', ' '}
        },
        .score = 0
    };
    memcpy(&game, &new_game1, sizeof(struct game));
    add_random_tile(&game);
    printf("is won: %d\n", is_game_won(game));

    struct game new_game2 = {
        .board = {
            {'A', 'A', 'C', 'D'},
            {'A', 'F', 'G', 'H'},
            {'I', 'J', 'J', 'A'},
            {'B', 'C', 'D', 'E'}
        },
        .score = 0
    };
    memcpy(&game, &new_game2, sizeof(struct game));

    printf("is move possible: %d\n", is_move_possible(game));

    struct game new_game3 = {
        .board = {
            {'A', 'B', 'C', 'D'},
            {'E', 'F', 'G', 'H'},
            {'I', 'J', 'K', 'A'},
            {'B', 'C', 'D', 'E'}
        },
        .score = 0
    };
    memcpy(&game, &new_game3, sizeof(struct game));

    printf("is move possible: %d\n", is_move_possible(game));

    bool result = update(&game, 1, 1);
    printf("update: %d\n", result);

    struct game new_game4 = {
        .board = {
            {'A', ' ', ' ', ' '},
            {'B', ' ', ' ', 'B'},
            {'C', 'C', 'C', ' '},
            {'D', 'D', 'D', 'D'}
        },
        .score = 0
    };
    memcpy(&game, &new_game4, sizeof(struct game));

    result = update(&game, 0, 1);
    printf("update: %d\n", result);

    struct game new_game5 = {
        .board = {
            {'A', 'B', 'C', 'D'},
            {'A', 'B', 'C', 'D'},
            {'A', 'B', 'C', 'D'},
            {'A', 'B', 'C', 'D'}
        },
        .score = 1234
    };
    memcpy(&game, &new_game5, sizeof(struct game));

    result = update(&game, 0, -1);
    printf("update: %d\n", result);


    struct game new_game6 = {
        .board = {
            {'C', ' ', 'J', 'D'},
            {'D', 'D', ' ', ' '},
            {' ', 'H', 'J', 'D'},
            {' ', ' ', 'J', 'D'}
        },
        .score=6794,
    };
    memcpy(&game, &new_game6, sizeof(struct game));

    result = update(&game, 0, -1);
    printf("update: %d\n", result);
    render(game);

    /////////////////////////////////////////////////
 /* file: score
    manager 5000
    manager 4000
    manager 3000
    manager 2000
    manager 1000
    manager 500
    manager 400
    manager 300
    manager 200
    manager 100
    */

    struct player list3[10];
    struct player player3 = {
        .name = "john",
        .score = 400
    };
    int sizee = load(list3);
    bool res = add_player(list3, &sizee, player3);

    printf("result: %d, size: %d\n", res, sizee);

    printf("list:\n");
    for (int i = 0; i < sizee; i++) {
        printf("%s %d\n", list3[i].name, list3[i].score);
    }

    save(list3, sizee);

    /* result = true, size = 10
    list:
    manager 5000
    manager 4000
    manager 3000
    manager 2000
    manager 1000
    manager 500
    john 400
    manager 400
    manager 300
    manager 200
    */

    return 0;
}