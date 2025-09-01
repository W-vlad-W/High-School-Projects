#define _GNU_SOURCE 
#include "backpack.h"
#include "item.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct backpack* create_backpack(const int capacity) {
    if (capacity <= 0) {
        return NULL;
    }

    struct backpack* bp = malloc(sizeof(struct backpack));
    if (bp == NULL) {
        return NULL;
    }

    bp->capacity = capacity;
    bp->size = 0;
    bp->items = NULL;

    return bp;
}

struct backpack* destroy_backpack(struct backpack* backpack) {
    if (backpack == NULL) {
        return NULL;
    }

    if (backpack->items != NULL) {
        backpack->items = destroy_containers(backpack->items);
    }

    free(backpack);

    return NULL;
}

bool add_item_to_backpack(struct backpack* backpack, struct item* item) {
    if (backpack == NULL || item == NULL) {
        return false;
    }

    if (!(item->properties & MOVABLE)) {
        return false;
    }

    if (backpack->size >= backpack->capacity) {
        return false;
    }

    struct container* new_item = create_container(NULL, ITEM, item);
    if (new_item == NULL) {
        return false;
    }

    new_item->next = backpack->items;
    backpack->items = new_item;
    backpack->size++;

    return true;
}

void delete_item_from_backpack(struct backpack* backpack, struct item* item) {
    if (backpack == NULL || item == NULL || backpack->items == NULL) {
        return;
    }

    struct container* current = backpack->items;
    struct container* prev = NULL;

    while (current != NULL) {
        if (current->type == ITEM && current->item == item) {
            if (prev == NULL) {
                backpack->items = current->next;
            } else {
                prev->next = current->next;
            }

            free(current);
            backpack->size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

struct item* get_item_from_backpack(const struct backpack* backpack, char* name) {
    if (backpack == NULL || name == NULL || backpack->items == NULL) {
        return NULL;
    }

    char* lower_name = strdup(name);
    if (lower_name == NULL) {
        return NULL;
    }
    
    for (char* p = lower_name; *p; p++) {
        *p = (char)tolower((unsigned char)*p);
    }

    struct container* current = backpack->items;
    while (current != NULL) {
        if (current->type == ITEM && current->item != NULL) {
            struct item* it = current->item;
            
            char* lower_item_name = strdup(it->name);
            if (lower_item_name != NULL) {
                for (char* p = lower_item_name; *p; p++) {
                    *p = (char)tolower((unsigned char)*p);
                }
                
                if (strcmp(lower_item_name, lower_name) == 0) {
                    free(lower_item_name);
                    free(lower_name);
                    return it;
                }
                free(lower_item_name);
            }
        }
        current = current->next;
    }

    free(lower_name);
    return NULL;
}