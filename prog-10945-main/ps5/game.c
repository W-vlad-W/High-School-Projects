#define _GNU_SOURCE 
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct game* create_game() {
    struct game* game = malloc(sizeof(struct game));
    if (game == NULL) {
        return NULL;
    }

    game->state = PLAYING;
    
    game->parser = create_parser();
    if (game->parser == NULL) {
        free(game);
        return NULL;
    }
    
    game->world = NULL;
    game->current_room = NULL;
    
    game->backpack = create_backpack(5);
    if (game->backpack == NULL) {
        destroy_parser(game->parser);
        free(game);
        return NULL;
    }
    
    return game;
}

struct game* destroy_game(struct game* game) {
    if (game == NULL) {
        return NULL;
    }

    if (game->parser != NULL) {
        game->parser = destroy_parser(game->parser);
    }

    if (game->world != NULL) {
        game->world = destroy_containers(game->world);
    }

    if (game->backpack != NULL) {
        game->backpack = destroy_backpack(game->backpack);
    }

    free(game);
    return NULL;
}

void play_game(struct game* game) {
    if (game == NULL) {
        return;
    }

    char input[INPUT_BUFFER_SIZE];

    printf("Vitajte v hre!\n");
    printf("Pre zoznam prikazov napiste 'POMOC'\n\n");

    if (game->current_room != NULL) {
        show_room(game->current_room);
    }

    while (game->state == PLAYING) {
        printf("\n> ");
        fgets(input, INPUT_BUFFER_SIZE, stdin);
        input[strcspn(input, "\n")] = '\0';

        struct command* cmd = parse_input(game->parser, input);
        if (cmd != NULL) {
            execute_command(game, cmd);
        } else {
            printf("Nerozumiem prikazu. Skuste 'POMOC' pre zoznam prikazov.\n");
        }
    }

    switch (game->state) {
        case GAMEOVER:
            printf("Hra skoncila. Dakujeme za hru!\n");
            break;
        case SOLVED:
            printf("Gratulujeme! Vyhrali ste hru!\n");
            break;
        case RESTART:
            printf("Hra sa restartuje...\n");
            break;
        default:
            break;
    }
}

void execute_command(struct game* game, struct command* command) {
    if (game == NULL || command == NULL) {
        return;
    }

    if (strcmp(command->name, "KONIEC") == 0) {
        game->state = GAMEOVER;
        printf("Ukoncujem hru...\n");
    }
    else if (strcmp(command->name, "POMOC") == 0) {
        printf("Dostupne prikazy:\n");
        struct container* current = game->parser->commands; 
        while (current != NULL) {
            if (current->type == COMMAND) {
                struct command* cmd = (struct command*)current->command;
                printf("  %s - %s\n", cmd->name, cmd->description);
            }
            current = current->next;
        }
    }
    else if (strcmp(command->name, "ROZHLIADNI SA") == 0) {
        if (game->current_room != NULL) {
            show_room(game->current_room);
        }
    }
    else if (strcmp(command->name, "SEVER") == 0) {
        if (game->current_room != NULL && game->current_room->north != NULL) {
            game->current_room = game->current_room->north;
            show_room(game->current_room);
        } else {
            printf("Nemozte ist na sever.\n");
        }
    }
    else if (strcmp(command->name, "JUH") == 0) {
        if (game->current_room != NULL && game->current_room->south != NULL) {
            game->current_room = game->current_room->south;
            show_room(game->current_room);
        } else {
            printf("Nemozte ist na juh.\n");
        }
    }
    else if (strcmp(command->name, "VYCHOD") == 0) {
        if (game->current_room != NULL && game->current_room->east != NULL) {
            game->current_room = game->current_room->east;
            show_room(game->current_room);
        } else {
            printf("Nemozte ist na vychod.\n");
        }
    }
    else if (strcmp(command->name, "ZAPAD") == 0) {
        if (game->current_room != NULL && game->current_room->west != NULL) {
            game->current_room = game->current_room->west;
            show_room(game->current_room);
        } else {
            printf("Nemozte ist na zapad.\n");
        }
    }
    else if (strcmp(command->name, "VEZMI") == 0) {
        if (command->nmatch > 1 && command->groups[1] != NULL) {
            struct item* item = get_item_from_room(game->current_room, command->groups[1]);
            if (item != NULL) {
                if (add_item_to_backpack(game->backpack, item)) {
                    delete_item_from_room(game->current_room, item);
                    printf("Vzal si predmet: %s\n", item->name);
                } else {
                    printf("Nemozno vziat predmet %s\n", item->name);
                }
            } else {
                printf("Predmet %s sa tu nenachadza.\n", command->groups[1]);
            }
        } else {
            printf("Neviem, co chcete vziat.\n");
        }
    }
    else if (strcmp(command->name, "POLOZ") == 0) {
        if (command->nmatch > 1 && command->groups[1] != NULL) {
            struct item* item = get_item_from_backpack(game->backpack, command->groups[1]);
            if (item != NULL) {
                add_item_to_room(game->current_room, item);
                delete_item_from_backpack(game->backpack, item);
                printf("Polozil si predmet: %s\n", item->name);
            } else {
                printf("Predmet %s nemas v batohu.\n", command->groups[1]);
            }
        } else {
            printf("Neviem, co chcete polozit.\n");
        }
    }
    else if (strcmp(command->name, "INVENTAR") == 0) {
        printf("Obsah batohu:\n");
        struct container* current = game->backpack->items;
        while (current != NULL) {
            if (current->type == ITEM) {
                struct item* item = (struct item*)current->item;
                printf(" - %s\n", item->name);
            }
            current = current->next;
        }
    }
    else if (strcmp(command->name, "POUZI") == 0) {
        printf("Prikaz 'POUZI' este nie je implementovany.\n");
    }
    else if (strcmp(command->name, "PRESKUMAJ") == 0) {
        if (command->nmatch > 1 && command->groups[1] != NULL) {
            struct item* item = get_item_from_room(game->current_room, command->groups[1]);
            if (item == NULL) {
                item = get_item_from_backpack(game->backpack, command->groups[1]);
            }
            if (item != NULL) {
                printf("%s: %s\n", item->name, item->description);
            } else {
                printf("Predmet %s sa tu nenachadza.\n", command->groups[1]);
            }
        } else {
            printf("Neviem, co chcete preskumat.\n");
        }
    }
    else if (strcmp(command->name, "RESTART") == 0) {
        game->state = RESTART;
    }
    else {
        printf("Neznamy prikaz: %s\n", command->name);
    }
}