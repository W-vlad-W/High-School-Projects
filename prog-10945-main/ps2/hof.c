#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hof.h"


int load(struct player list[]) {
    FILE *file = fopen("score", "r");
    if (file == NULL) {
        return -1;  
    }
    
    int count = 0;
    while (count < 10 && fscanf(file, "%s %d", list[count].name, &list[count].score) == 2) {
        count++;
    }
    fclose(file);
    
    
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (list[j].score > list[i].score) {
                struct player temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
    return count;
}

bool save(const struct player list[], const int size){
    FILE *file = fopen("score.txt", "w");
    if (!file) return false;

    struct player *copy = malloc((size_t)size * sizeof(struct player));
    if (!copy) {
        fclose(file);
        return false;
    }
    memcpy(copy, list, (size_t)size * sizeof(struct player));

    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (copy[j].score >= copy[i].score) {
                struct player temp = copy[i];
                copy[i] = copy[j];
                copy[j] = temp;
            }
        }
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%s %d\n", copy[i].name, copy[i].score);
    }

    free(copy);
    fclose(file);
    return true;
}

bool add_player(struct player list[], int* size, const struct player player) {
    if (*size < 10) {
        list[*size] = player;
        (*size)++;
    } else if (player.score >= list[9].score) {
        list[9] = player;
    } else {
        return false; 
    }

    for (int i = *size - 1; i > 0 && list[i].score >= list[i - 1].score; i--) {
        struct player temp = list[i];
        list[i] = list[i - 1];
        list[i - 1] = temp;
    }

    return true;
}
