#define _GNU_SOURCE 
#include "room.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



struct room* create_room(char *name, char *description) {
    if (!name || !description) return NULL;

    struct room* new_room = (struct room*)malloc(sizeof(struct room));
    if (!new_room) return NULL;

    new_room->name = strdup(name);
    new_room->description = strdup(description);
    new_room->north = NULL;
    new_room->south = NULL;
    new_room->east = NULL;
    new_room->west = NULL;
    new_room->items = NULL;

    if (!new_room->name || !new_room->description) {
        free(new_room->name);
        free(new_room->description);
        free(new_room);
        return NULL;
    }

    return new_room;
}

struct room* destroy_room(struct room* room) {
    if (!room) return NULL;

    free(room->name);
    free(room->description);
    destroy_containers(room->items);
    free(room);

    return NULL;
}

void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west) {
    if (!room) return;

    room->north = north;
    room->south = south;
    room->east = east;
    room->west = west;
}

void show_room(const struct room* room) {
    if (!room) return;

    printf("%s\n", room->description);
    printf("Mozne vychody z miesnosti:\n");
    
    if (room->north) printf("    sever\n");
    if (room->south) printf("    juh\n");
    if (room->east) printf("    vychod\n");
    if (room->west) printf("    zapad\n");

    printf("Vidíš:\n");
    struct container* current = room->items;
    while (current) {
        if (current->type == ITEM && current->item) {
            printf("    %s\n", current->item->name);
        }
        current = current->next;
    }
}

void add_item_to_room(struct room* room, struct item* item) {
    if (!room || !item) return;

    room->items = create_container(room->items, ITEM, item);
}

struct item* get_item_from_room(const struct room* room, const char* name) {
    if (!room || !name) return NULL;

    struct container* current = room->items;
    while (current) {
        if (current->type == ITEM && current->item && strcasecmp(current->item->name, name) == 0) {
            return current->item;
        }
        current = current->next;
    }
    return NULL;
}

void delete_item_from_room(struct room* room, struct item* item) {
    if (!room || !item) return;

    room->items = remove_container(room->items, item);
}