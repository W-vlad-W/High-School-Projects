#include <stdio.h>
#include <string.h>
#include "hangman.h"
#include "hangman.c"
#include "morse.h"
#include "morse.c"

 
int main() {
    char output[150];
    text_to_morse("Hello", output);
    puts(output); 

    char output_2[150];
    morse_to_text(".... . .-.. .-.. ---", output_2);
    puts(output_2);

    if(is_morse_code_valid(".-- .... .- -.-- - .... ..-")) {
        printf("Code is valid! \n");
    } else {
        printf("Code is invalid! \n");
    }
    
    if(is_morse_code_valid(".... . .-.--. .-.. ---")) {
        printf("Code is valid! \n");
    } else {
        printf("Code is invalid! \n");
    }

    char secret[15];
    if(!get_word(secret)) hangman(secret);
    return 0;
}
