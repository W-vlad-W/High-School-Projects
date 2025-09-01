#define _GNU_SOURCE 
#include "command.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



struct command* create_command(char* name, char* description, char* pattern, size_t nmatch){
    if (name == NULL || description == NULL) {
        return NULL;
    }

    struct command* cmd = malloc(sizeof(struct command));

    cmd->name = strdup(name);
    cmd->description = strdup(description);
  
    if (pattern != NULL) {
        int ret = regcomp(&cmd->preg, pattern, REG_EXTENDED);
        if (ret != 0) {
            char error_msg[100];
            regerror(ret, &cmd->preg, error_msg, sizeof(error_msg));
            fprintf(stderr, "Regex compilation failed: %s\n", error_msg);
            free(cmd->description);
            free(cmd->name);
            free(cmd);
            return NULL;
        }
        cmd->nmatch = nmatch;
    } else {
        cmd->nmatch = 0;
    }

    cmd->groups = NULL;
    if (nmatch > 0) {
        cmd->groups = calloc(nmatch, sizeof(char*));
        if (cmd->groups == NULL) {
            if (pattern != NULL) {
                regfree(&cmd->preg);
            }
            free(cmd->description);
            free(cmd->name);
            free(cmd);
            return NULL;
        }
    }

    return cmd;
}

struct command* destroy_command(struct command* command){
    if (command == NULL) {
        return NULL;
    }

    free(command->name);
    free(command->description);

    if (command->nmatch > 0) {
        regfree(&command->preg);
    }

    if (command->groups != NULL) {
        for (size_t i = 0; i < command->nmatch; i++) {
            if (command->groups[i] != NULL) {
                free(command->groups[i]);
            }
        }
        free(command->groups);
    }

    free(command);

    return NULL;
}