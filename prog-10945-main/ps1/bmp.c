#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "bmp.h"


int char_alpha(const char* text) {
    if (!text) return 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (!isalpha((unsigned char)text[i])) return 0;
    }
    return 1;
}

unsigned char encrypt_char(unsigned char c) {
    unsigned char f_half = (c >> 4) & 0x0F; 
    unsigned char s_half = c & 0x0F;       
    
    unsigned char swap_first_half = ((f_half & 0x0A) >> 1) | ((f_half & 0x05) << 1);
    
    unsigned char new_second_half = swap_first_half ^ s_half;
    
    return (swap_first_half << 4) | new_second_half;
}

char decrypt_char(unsigned char c) {
    unsigned char f_half = (c >> 4) & 0x0F; 
    unsigned char s_half = c & 0x0F;       
    
    unsigned char original_s_half = f_half ^ s_half;
    
    unsigned char original_f_half = ((f_half & 0x0A) >> 1) | ((f_half & 0x05) << 1);
    
    return (original_f_half << 4) | original_s_half;
}

char* prepareKey(const char *key, int len) {
    char *formatted = calloc(len + 1, sizeof(char)); 

    if (!formatted) return NULL;

    int k = 0;
    for(int i = 0; i < len; i++){
        formatted[i] = toupper(key[k]);
        if(k == strlen(key) - 1){k = 0;}
        else{k++;}
    }

    formatted[len] = '\0';  
    return formatted;
}

char* reverse(const char* text){
    if(!text) return NULL;
    char* reversed = calloc(strlen(text) + 1, sizeof(char));
    for(int i = 0; i < strlen(text); i++){
        reversed[i] = text[strlen(text) - i - 1];
    }
    for(int i = 0; i < strlen(text); i++){
        reversed[i] = toupper(reversed[i]);
    }
    reversed[strlen(text)] = '\0';
    return reversed;
}

char* vigenere_encrypt(const char* key, const char* text){
    if(key == NULL) return NULL;
    if(text == NULL) return NULL;
    if(!char_alpha(key)) return NULL;

    int text_len = strlen(text);

    char *cipher_text = (char*)calloc(text_len + 1, sizeof(char));
    char *preparedkey = prepareKey(key, text_len);

    int key_index = 0;
    for(int i = 0; i < text_len; i++){
        char c = toupper(text[i]);
        if(c < 'A' || c > 'Z'){  
            cipher_text[i] = c;
            continue;
        }
        cipher_text[i] = ((c - 'A' + preparedkey[key_index] - 'A') % 26) + 'A';
        key_index++;
    }
    cipher_text[text_len] = '\0';
    free(preparedkey);
    return cipher_text;
}


char* vigenere_decrypt(const char* key, const char* text){
    if(key == NULL) return NULL;
    if(text == NULL) return NULL;
    if(!char_alpha(key)) return NULL;

    int text_len = strlen(text);

    char *decipher_text = (char*)calloc(text_len + 1, sizeof(char));
    char *preparedkey = prepareKey(key, text_len);
    
    int key_index = 0;
    for(int i = 0; i < text_len; i++){
        char c = text[i];
        if(c <  'A' || c > 'Z'){
            decipher_text[i] = c;
            continue;
        }
        decipher_text[i] = ((c - preparedkey[key_index] + 26) % 26) + 'A';
        key_index++;
    }
    decipher_text[text_len] = '\0';
    free(preparedkey);
    return decipher_text;
}



unsigned char* bit_encrypt(const char* text){
    if(!text) return NULL;

    int text_len = strlen((const char*)text);
    
    unsigned char *cipher_text = (unsigned char*)calloc(text_len + 1, sizeof(char));

    for (int i = 0; i < text_len; i++) {
        cipher_text[i] = encrypt_char(text[i]);
    }
    cipher_text[text_len] = '\0';

    return cipher_text;
}



char* bit_decrypt(const unsigned char* text){
    if(!text) return NULL;

    int text_len = strlen((const char*)text);
    
    char *decipher_text = (char*)calloc(text_len + 1, sizeof(char));

    for (int i = 0; i < text_len; i++) {
        decipher_text[i] = decrypt_char(text[i]);
    }
    decipher_text[text_len] = '\0';

    return decipher_text;
    free(decipher_text);
}



unsigned char* bmp_encrypt(const char* key, const char* text){
    if(key == NULL) return NULL;
    if(text == NULL) return NULL;
    if(!char_alpha(key)) return NULL;

    char *bmp_step_f = reverse(text);
    char *bmp_step_s = vigenere_encrypt(key, bmp_step_f);
    unsigned char *bmp_step_t = bit_encrypt(bmp_step_s);
    free(bmp_step_f);
    free(bmp_step_s);
    return bmp_step_t;
}



char* bmp_decrypt(const char* key, const unsigned char* text){
    if(key == NULL) return NULL;
    if(text == NULL) return NULL;
    if(!char_alpha(key)) return NULL;
    
    char *bmp_step_f = bit_decrypt(text);
    char *bmp_step_s = vigenere_decrypt(key, bmp_step_f);
    char *bmp_step_t = reverse(bmp_step_s);
    free(bmp_step_f);
    free(bmp_step_s);
    return bmp_step_t;
}
