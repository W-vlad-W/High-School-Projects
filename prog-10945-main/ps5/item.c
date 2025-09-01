#define _GNU_SOURCE 
#include "item.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct item* create_item(char* name, char* description, unsigned int properties) {
    if (name == NULL || description == NULL) {
        return NULL;
    }

    struct item* new_item = malloc(sizeof(struct item));
    if (new_item == NULL) {
        return NULL;
    }

    new_item->name = strdup(name);
    if (new_item->name == NULL) {
        free(new_item);
        return NULL;
    }

    new_item->description = strdup(description);
    if (new_item->description == NULL) {
        free(new_item->name);
        free(new_item);
        return NULL;
    }

    new_item->properties = properties;

    return new_item;
}

struct item* destroy_item(struct item* item) {
    if (item == NULL) {
        return NULL;
    }

    if (item->name != NULL) {
        free(item->name);
    }

    if (item->description != NULL) {
        free(item->description);
    }

    free(item);

    return NULL;
}