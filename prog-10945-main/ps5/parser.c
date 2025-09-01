#define _GNU_SOURCE 
#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

static char* trim_whitespace(char* str) {
    if (str == NULL) return NULL;

    while (isspace((unsigned char)*str)) str++;

    if (*str == '\0') return str;

    char* end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    *(end + 1) = '\0';

    return str;
}

static void to_uppercase(char* str) {
    if (str == NULL) return;
    for (; *str; str++) *str = (char)toupper((unsigned char)*str);
    
}

static bool should_add_to_history(const char* command_name) {
    if (command_name == NULL) return false;
    
    const char* excluded[] = {"ULOZ", "SAVE", "NAHRAJ", "LOAD"};
    size_t excluded_count = sizeof(excluded) / sizeof(excluded[0]);
    
    for (size_t i = 0; i < excluded_count; i++) {
        if (strcmp(command_name, excluded[i]) == 0) {
            return false;
        }
    }
    return true;
}

struct parser* create_parser() {
    struct parser* parser = malloc(sizeof(struct parser));
    if (parser == NULL) {
        return NULL;
    }

    parser->history = NULL;
    parser->commands = NULL;

    return parser;
}

struct parser* destroy_parser(struct parser* parser) {
    if (parser == NULL) {
        return NULL;
    }

    if (parser->history != NULL) {
        parser->history = destroy_containers(parser->history);
    }

    if (parser->commands != NULL) {
        parser->commands = destroy_containers(parser->commands);
    }

    free(parser);

    return NULL;
}

struct command* parse_input(struct parser* parser, char* input) {
    if (parser == NULL || input == NULL) {
        return NULL;
    }

    char* trimmed_input = trim_whitespace(input);
    if (strlen(trimmed_input) == 0) {
        return NULL;
    }

    char* upper_input = strdup(trimmed_input);
    if (upper_input == NULL) {
        return NULL;
    }
    to_uppercase(upper_input);

    struct command* matched_command = NULL;
    struct container* current = parser->commands;

    while (current != NULL) {
        if (current->type == COMMAND) {
            struct command* cmd = (struct command*)current->command;
            
            regmatch_t matches[cmd->nmatch];
            if (regexec(&cmd->preg, upper_input, cmd->nmatch, matches, 0) == 0) {
                matched_command = cmd;
               
                if (cmd->nmatch > 1) {
                    for (size_t i = 1; i < cmd->nmatch; i++) {
                        if (matches[i].rm_so != -1) {
                            size_t len = (size_t)(matches[i].rm_eo - matches[i].rm_so);
                            cmd->groups[i] = malloc(len + 1);
                            if (cmd->groups[i] != NULL) {
                                strncpy(cmd->groups[i], upper_input + matches[i].rm_so, len);
                                cmd->groups[i][len] = '\0';
                            }
                        }
                    }
                }
                break;
            }
        }
        current = current->next;
    }

    free(upper_input);

    if (matched_command != NULL && should_add_to_history(matched_command->name)) {
        struct command* history_entry = create_command(
            matched_command->name, 
            matched_command->description, 
            NULL, 
            0
        );
        if (history_entry != NULL) {
            parser->history = create_container(parser->history, COMMAND, history_entry);
        }
    }

    return matched_command;
}