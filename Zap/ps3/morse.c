#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "morse.h"


void text_to_morse(const char text[], char output[]){
    const char *morse_codes[] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
        "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
        "..-", "...-", ".--", "-..-", "-.--", "--.."
    };

    output[0] = '\0';

    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];
        if (ch >= 'A' && ch <= 'Z') {
            int index = ch - 'A';
            strcat(output, morse_codes[index]);
            strcat(output, " ");
        }
        else if (ch >= 'a' && ch <= 'z'){
            int index = ch - 'a';
            strcat(output, morse_codes[index]);
            strcat(output, " ");
        }
        else if (ch >= '0' && ch <= '9'){
            int index = ch + 26 - '0';
            strcat(output, morse_codes[index]);
            strcat(output, " ");
        }
    }

    int len = strlen(output);
    if (len > 0 && output[len - 1] == ' ') {
        output[len - 1] = '\0';
    }
}


void morse_to_text(const char morse[], char output[]){
    const char *morse_codes_alph[] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
        "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
        "..-", "...-", ".--", "-..-", "-.--", "--.."
    };

    const char *morse_codes_nums[] = {
         "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
    };

  
    const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char numbers[] = "0123456789";
    
    output[0] = '\0';

    char str_copy[100];
    strncpy(str_copy, morse, sizeof(str_copy) - 1);
    str_copy[sizeof(str_copy) - 1] = '\0';

    char *token = strtok(str_copy, " ");
    while (token != NULL) {
        bool found = false;
        
        // Check if alphabet Morse code
        for (int i = 0; i < 26; i++) {
            if (strcmp(token, morse_codes_alph[i]) == 0) {
                strncat(output, &letters[i], 1);
                found = true;
                break;
            }
        }

        // Check if number Morse code
        if (!found) {
            for (int i = 0; i < 10; i++) {
                if (strcmp(token, morse_codes_nums[i]) == 0) {
                    strncat(output, &numbers[i], 1);
                    break;
                }
            }
        }
        token = strtok(NULL, " ");
    }

}

int is_morse_code_valid(const char morse[]){
    const char *morse_codes[] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
        "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
        "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---", 
        "...--", "....-", ".....", "-....", "--...", "---..", "----."
    };

    char str_copy[100];
    strncpy(str_copy, morse, sizeof(str_copy) - 1);
    str_copy[sizeof(str_copy) - 1] = '\0';

    bool markers[150];
    int i = 0;
    char *token = strtok(str_copy, " ");
    while (token != NULL) {
        bool found = false;
        for (int i = 0; i < 36; i++) {
            if(strcmp(token, morse_codes[i]) == 0) {
                found = true;
                break;
            }
        }
        token = strtok(NULL, " ");
        markers[i] = found;
        i++;
    }
    for(int j = 0; j < i; j++){
        if(!markers[j]) return 0;
    }
    return 1; 
}