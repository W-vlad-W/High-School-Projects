#include <stdio.h>
#include <stdlib.h>
#include "playfair.h"
#include "bmp.h"


int main() {
    char *encrypted, *decrypted;

    // even length of string
    encrypted = playfair_encrypt("SeCReT", "Hello world");
    printf("%s\n", encrypted);
    // "Hello world" --> "HELXLOVORLDX"
    // IS JZ JQ XN TK JC
    decrypted = playfair_decrypt("SeCReT", encrypted);
    printf("%s\n", decrypted);
    // HELXLOVORLDX
    free(encrypted);
    free(decrypted);

    // odd length of string
    encrypted = playfair_encrypt("world", "Hello");
    printf("%s\n", encrypted);
    // "Hello" --> "HELXLO"
    // JB RY DR
    decrypted = playfair_decrypt("world", encrypted);
    printf("%s\n", decrypted);
    // HELXLO
    free(encrypted);
    free(decrypted);

    // letter 'X' in message
    encrypted = playfair_encrypt("Password", "Taxi please");
    printf("%s\n", encrypted);
    // "Taxi please" --> "TAXIPLEASE"
    // UP YH AK DO OB
    decrypted = playfair_decrypt("Password", encrypted);
    printf("%s\n", decrypted);
    // TAXIPLEASE
    free(encrypted);
    free(decrypted);

    // multi 'X's in message
    encrypted = playfair_encrypt("please", "Taxxxiii");
    printf("%s\n", encrypted);
    // "Taxxxiii" --> "TAXXXIIXIX"
    // RS EE VJ JV JV
    decrypted = playfair_decrypt("please", encrypted);
    printf("%s\n", decrypted);
    // TAXXXIIXIX
    free(encrypted);
    free(decrypted);    

    // BMP
    char* reversed = reverse("Hello world!");
    printf("%s\n", reversed);
    // "!DLROW OLLEH"
    free(reversed);

    char *encrypted_00, *decrypted_00;
    encrypted_00 = vigenere_encrypt("CoMPuTeR", "Hello world!");
    printf("%s\n", encrypted_00); 
    // "JSXAI PSINR!"
    decrypted_00 = vigenere_decrypt("CoMPuTeR", encrypted_00);
    printf("%s\n", decrypted_00);
    // "HELLO WORLD!"
    free(encrypted_00);
    free(decrypted_00);

    unsigned char *encrypted_01;
    char *decrypted_01;

    encrypted_01 = bit_encrypt("Hello world!");
    for(int i=0; i < 12;i++) {
        printf("%x ", encrypted_01[i]);
        //80 9c 95 95 96 11 bc 96 b9 95 9d 10
    }
    decrypted_01 = bit_decrypt(encrypted_01);
    printf("\n%s\n", decrypted_01);
    // "Hello world!"
    free(encrypted_01);
    free(decrypted_01);

    unsigned char *encrypted_02;
    char *decrypted_02;
    
    encrypted_02 = bmp_encrypt("CoMPuTeR", "Hello world!");
    for(int i=0; i < 12;i++) {
        printf("%x ", encrypted_02[i]);
        //80 9c 95 95 96 11 bc 96 b9 95 9d 10
    }
    decrypted_02 = bmp_decrypt("CoMPuTeR", encrypted_02);
    printf("\n%s\n", decrypted_02);
    free(encrypted_02);
    free(decrypted_02);
    return 0;
}