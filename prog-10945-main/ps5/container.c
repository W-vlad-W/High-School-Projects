#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "container.h"
#include <ctype.h>
// struct container {
//     enum container_type type;       /// type of container
//     union{
//         struct room*    room;       /// pointer to room
//         struct item*    item;       /// pointer to item
//         struct command* command;    /// pointer to command
//         char*           text;       /// pointer to text
//     };
//     struct container* next;         /// pointer to next data container in list
// };

struct container* create_container(struct container* first, enum container_type type, void* entry){
    if (!entry) return NULL;
    if (first && first->type != type) return NULL; 

    struct container* new_container = (struct container*)malloc(sizeof(struct container));
    new_container->type = type;
    switch (type) {
        case ROOM:    new_container->room = (struct room*)entry; break;
        case ITEM:    new_container->item = (struct item*)entry; break;
        case COMMAND: new_container->command = (struct command*)entry; break;
        case TEXT:    new_container->text = (char*)entry; break;
    }
    new_container->next = NULL;
    if (!first) return new_container; 

    struct container* current = first;
    while (current->next) {
        current = current->next;
    }
    current->next = new_container;

    return new_container;
}



struct container* destroy_containers(struct container* first){
    while (first) {
        struct container* next = first->next;
        switch (first->type) {
            case ROOM:    free(first->room); break;
            case ITEM:    free(first->item); break;
            case COMMAND: free(first->command); break;
            case TEXT:    free(first->text); break;
        }
            
        free(first);
        first = next;
    }
    return NULL;
}




void* get_from_container_by_name(struct container *first, const char *name){
    if (!first || !name) return NULL;

    struct container* current = first;
    while (current) {
        const char* current_name = NULL;
        
        switch (current->type) {
            case ROOM:    current_name = current->room->name; break;
            case ITEM:    current_name = current->item->name; break;
            case COMMAND: current_name = current->command->name; break;
            case TEXT:    current_name = current->text; break;
        }

        if (current_name && strcasecmp(current_name, name) == 0) {
            switch (current->type) {
                case ROOM:    return current->room;
                case ITEM:    return current->item;
                case COMMAND: return current->command;
                case TEXT:    return current->text;
            }
        }
        current = current->next;
    }
    return NULL;
}




struct container* remove_container(struct container *first, void *entry){
    if (!first || !entry) return first;

    struct container* current = first;
    struct container* prev = NULL;

    while (current) {
        void* current_entry = NULL;
        
        switch (current->type) {
            case ROOM:    current_entry = current->room; break;
            case ITEM:    current_entry = current->item; break;
            case COMMAND: current_entry = current->command; break;
            case TEXT:    current_entry = current->text; break;
        }

        if (current_entry == entry) {
            if (prev) {
                prev->next = current->next;
            } else {
                first = current->next;
            }
            free(current);
            return first;
        }
        prev = current;
        current = current->next;
    }
    return first;
}
