#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "playfair.h"

int char_alpha_2(const char* text) {
    for (int i = 0; text[i] != '\0'; i++) {
        if ((!isalpha(((unsigned char)text[i])) && text[i] != ' ')) return 1;
    }
    return 0;
}


int is_W(const char* text) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == 'W') return 1;
        if (text[i] == 'w') return 1;
    }
    return 0;
}
void removeChar(char *str, char ch) {
    int i, j = 0;
    int len = strlen(str);
    
    for (i = 0; i < len; i++) {
        if (str[i] != ch) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

void replaceW(char *str) {
    int i = 0;
    int len = strlen(str);
    
    for (i = 0; i < len; i++) {
        if (str[i] == 'W') {
            str[i] = 'V';
        }
    }
}

void str_upper(char *str) {
    int j = 0;
    while (str[j] != '\0') {
        str[j] = toupper(str[j]);
        j++;
    }
}

void removeSpace(char *str) {
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

void removeDuplicates(char *str) {
    int len = strlen(str);
    char *str_copy = malloc(len + 1);
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        int found = 0;
        for (int k = 0; k < j; k++) {
            if (str[i] == str_copy[k]) {
                found = 1; 
                break;
            }
        }
        if (!found) {
            str_copy[j++] = str[i]; 
        }
    }
    str_copy[j] = '\0'; 
    strncpy(str, str_copy, len);
    free(str_copy);
}


char* prepareText(char *text) {
    removeSpace(text);
    int len = strlen(text);
    char *formatted = malloc((len * 2) * sizeof(char)); 

    if (!formatted) return NULL;

    int j = 0;
    for (int i = 0; i < len; i++) {
        char current = text[i];  
        if (current == 'W') {
            formatted[j++] = 'V';  
        } else {
            formatted[j++] = current;
        }

        if (j % 2 != 0 && i + 1 < len && text[i] == text[i + 1] && text[i] != 'X') {
            formatted[j++] = 'X';  
        }
    }

    if (j % 2 != 0) {
        formatted[j++] = 'X';  
    }

    formatted[j] = '\0';  
    return formatted;
}


char** createKeyTable(char *key) {
    char alphabet[] = ALPHA;   
    
    for (int i = 0; i < strlen(key); i++) {
        removeChar(alphabet, key[i]);
    }

    char *key_table = malloc(26 * sizeof(char));

    int k = 0;
    for (int i = 0; i < strlen(key); i++) {
        key_table[k++] = key[i];
    }
    for (int i = 0; i < strlen(alphabet); i++) {
        key_table[k++] = alphabet[i];
    }

    key_table[25] = '\0';

    char **key_table_2D = malloc(5 * sizeof(char *));
    
    for (int i = 0; i < 5; i++) {
        key_table_2D[i] = malloc(5 * sizeof(char));
    }

    k = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            key_table_2D[i][j] = key_table[k++];
        }
    }

    free(key_table);
    return key_table_2D;
}

char* playfair_encrypt(const char* key, const char* text){
    if (key == NULL || key[0] == '\0' || key[0] == ' ') return NULL; 
    if (text == NULL || text[0] == '\0' || text[0] == ' ') return NULL;

    if(char_alpha_2(key)) return NULL;
    if(char_alpha_2(text)) return NULL;

    char* key_upper = calloc(strlen(key) + 1, sizeof(char));
    strncpy(key_upper, key, strlen(key));
    key_upper[strlen(key)] = '\0';
    str_upper(key_upper);
    removeDuplicates(key_upper);
    replaceW(key_upper);
    removeSpace(key_upper); 

    char* text_upper = calloc(strlen(text) + 1, sizeof(char));
    strncpy(text_upper, text, strlen(text));
    text_upper[strlen(text)] = '\0';
    str_upper(text_upper);
    removeSpace(text_upper);

    char *splited_text = prepareText(text_upper);
    char **key_table = createKeyTable(key_upper);
    
    int len = strlen(splited_text);

    char *sifr = calloc(len + 1, sizeof(char));
    
    free(text_upper);
    free(key_upper);
    
    int idx = 0;
    while(splited_text[idx] != '\0'){
        int col_f = -1, col_s = -1, row_f = -1, row_s = -1;
        char f_b = splited_text[idx];
        char s_b = splited_text[idx + 1];
        if(f_b == 'X' && s_b == 'X'){ // if the XX
            for(int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    if(f_b == key_table[i][j]){
                        col_f = i;
                        row_f = j;
                        col_s = i;
                        row_s = j;
                    }
                }
            }
        }else{
            for(int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    if(f_b == key_table[i][j]){
                        col_f = i;
                        row_f = j;
                    }
                    if(s_b == key_table[i][j]){
                        col_s = i;
                        row_s = j;
                    }
                }
            }
        }
        if(col_f != -1 && col_s != -1 && row_f != -1 && row_s != -1){
            if(col_f == col_s && row_f == row_s){
                sifr[idx] = key_table[(col_f + 1) % 5][row_f];
                sifr[idx + 1] = key_table[(col_s + 1) % 5][row_s];
            }
            else if(col_f == col_s){
                sifr[idx] = key_table[col_f][(row_f + 1) % 5];
                sifr[idx + 1] = key_table[col_s][(row_s + 1) % 5];
            }
            else if(row_f == row_s){
                sifr[idx] = key_table[(col_f + 1) % 5][row_f];
                sifr[idx + 1] = key_table[(col_s + 1) % 5][row_s];
            }
            else {
                sifr[idx + 1] = key_table[col_s][row_f];
                sifr[idx] = key_table[col_f][row_s];
            }
        }

        idx += 2;
    }

    sifr[len] = '\0';
    free(splited_text);
    for (int i = 0; i < 5; i++) {
        free(key_table[i]);
    }
    free(key_table);

    char *sifr_with_spaces = calloc(len * 2, sizeof(char)); 
    int k = 0;
    for (int i = 0; i < len; i += 2) {
        sifr_with_spaces[k++] = sifr[i];
        sifr_with_spaces[k++] = sifr[i + 1];
        sifr_with_spaces[k++] = ' ';
    }
    sifr_with_spaces[k - 1] = '\0';

    free(sifr);
    return sifr_with_spaces;
}




char* playfair_decrypt(const char* key, const char* text){
    if (key == NULL || key[0] == '\0' || key[0] == ' ') return NULL; 
    if (text == NULL || text[0] == '\0' || text[0] == ' ') return NULL;

    if(char_alpha_2(key)) return NULL;
    if(char_alpha_2(text) || is_W(text)) return NULL;

    char* key_upper = calloc(strlen(key) + 1, sizeof(char));
    strncpy(key_upper, key, strlen(key));
    key_upper[strlen(key)] = '\0';
    str_upper(key_upper);
    removeDuplicates(key_upper);
    replaceW(key_upper);
    removeSpace(key_upper); 

    char* copieded_text = calloc(strlen(text) + 1, sizeof(char));
    strncpy(copieded_text, text, strlen(text));
    copieded_text[strlen(text)] = '\0';
    str_upper(copieded_text);
    removeSpace(copieded_text);

    char **key_table = createKeyTable(key_upper);
    int len = strlen(copieded_text);


    char *desifr = calloc(len + 1, sizeof(char));

    int idx = 0;
    while(copieded_text[idx] != '\0'){
        int col_f = -1, col_s = -1, row_f = -1, row_s = -1;
        char f_b = copieded_text[idx];
        char s_b = copieded_text[idx + 1];
        if(f_b == s_b){
            for(int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    if(f_b == key_table[i][j]){
                        col_f = i;
                        row_f = j;
                        col_s = i;
                        row_s = j;
                    }
                }
            }
        }else{
            for(int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    if(f_b == key_table[i][j]){
                        col_f = i;
                        row_f = j;
                    }
                    if(s_b == key_table[i][j]){
                        col_s = i;
                        row_s = j;
                    }
                }
            }
        }
        if(col_f != -1 && col_s != -1 && row_f != -1 && row_s != -1){
            if(col_f == col_s && row_f == row_s){
                desifr[idx] = key_table[(col_f + 4) % 5][row_f];
                desifr[idx + 1] = key_table[(col_s + 4) % 5][row_s];
            }
            else if(col_f == col_s){
                desifr[idx] = key_table[col_f][(row_f + 4) % 5];
                desifr[idx + 1] = key_table[col_s][(row_s + 4) % 5];
            }
            else if(row_f == row_s){
                desifr[idx] = key_table[(col_f + 4) % 5][row_f];
                desifr[idx + 1] = key_table[(col_s + 4) % 5][row_s];
            }
            else {
                desifr[idx + 1] = key_table[col_s][row_f];
                desifr[idx] = key_table[col_f][row_s];
            }
        }

        idx += 2;
    }
    
    free(copieded_text);
    free(key_upper);

    for (int i = 0; i < 5; i++) {
        free(key_table[i]);
    }
    free(key_table);
    return desifr;
}

