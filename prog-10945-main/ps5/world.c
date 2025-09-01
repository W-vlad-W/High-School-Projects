#define _GNU_SOURCE 
#include <strings.h>
#include "world.h"
#include "container.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool room_name_exists(struct container* world, const char* name) {
    if (name == NULL) return false;
    
    struct container* current = world;
    while (current != NULL) {
        if (current->type == ROOM) {
            struct room* r = (struct room*)current->room;
            if (strcasecmp(r->name, name) == 0) {
                return true;
            }
        }
        current = current->next;
    }
    return false;
}

struct container* create_world() {
    struct container* world = NULL;
    return world;
}

struct container* add_room_to_world(struct container* world, struct room* room) {
    if (room == NULL) {
        return NULL;
    }

    if (room_name_exists(world, room->name)) {
        return NULL;
    }

    struct container* new_container = create_container(world, ROOM, room);
    if (new_container == NULL) {
        return NULL;
    }

    if (world == NULL) {
        return new_container;
    }

    struct container* current = world;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_container;

    return world;
}

struct container* destroy_world(struct container* world) {
    return destroy_containers(world);
}

struct room* get_room(struct container* world, char* name) {
    if (world == NULL || name == NULL) {
        return NULL;
    }

    struct container* current = world;
    while (current != NULL) {
        if (current->type == ROOM) {
            struct room* r = (struct room*)current->room;
            if (strcasecmp(r->name, name) == 0) {
                return r;
            }
        }
        current = current->next;
    }

    return NULL;
}