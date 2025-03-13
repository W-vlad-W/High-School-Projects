#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hangman.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int get_word(char secret[]){
    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    // get the filesize first
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;
    do{
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF )
            break;
    }while(1);

    fclose(fp);

    return 0;
}

int is_word_guessed(const char secret[], const char letters_guessed[]){    
    int length_secret = strlen(secret);
    int length_letters_guessed = strlen(letters_guessed);
    
    for(int i = 0; i < length_secret; i++){
        bool found = false;
        for(int j = 0; j < length_letters_guessed; j++){
            if(secret[i] == letters_guessed[j]){
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}



void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]){
    for (int i = 0; i < strlen(secret); i++){
        if(strchr(letters_guessed, secret[i]) == NULL){guessed_word[i] = '_';}
        else{guessed_word[i] = secret[i];} 
    }
    guessed_word[strlen(secret)] = '\0';
}


void get_available_letters(const char letters_guessed[], char available_letters[]) {
    strcpy(available_letters, "abcdefghijklmnopqrstuvwxyz");

    int index = 0;
    for (char letter = 'a'; letter <= 'z'; letter++) {
        bool is_guessed = false;

        for (int j = 0; j < strlen(letters_guessed); j++) {
            if (letter == letters_guessed[j]) {
                is_guessed = true;
                break;
            }
        }
        if (!is_guessed) {
            available_letters[index++] = letter;
        }
    }
    available_letters[index] = '\0';
}



void hangman(const char secret[]){

    char available_letters[] = "abcdefghijklmnopqrstuvwxyz";
    char letters_guessed[30] = ""; 
    char guessed_word[30] = "";

    int length_secret = strlen(secret);
    

    printf("Welcome to the game, Hangman!\n");
    printf("I am thinking of a word that is %d letters long.\n", length_secret);
    
    int guesses = 8;
    while(guesses){
        int pos = 0;

        printf("%s\n", "-------------");
        printf("You have %d guesses left.\n", guesses);
        printf("%s", "Available letters: ");
        get_available_letters(letters_guessed, available_letters);
        for (int i = 0; available_letters[i] != '\0'; i++) {
            printf("%c", available_letters[i]);
        }
        printf("\n");
        char guess[30];
        printf("%s", "Please guess a letter: ");
        scanf("%s", guess);

        guess[0] = tolower(guess[0]);

        if (strlen(guess) > 1) {
            if (strcmp(guess, secret) == 0) {
                printf("Congratulations, you won!\n");
                return;
            } else {
                printf("Sorry, bad guess. The word was: %s\n", secret);
                return;
            }
        }

        if (!isalpha(guess[0])) {
            printf("Oops! '%c' is not a valid letter: ", guess[0]);
            get_guessed_word(secret, letters_guessed, guessed_word);
            for (int i = 0; guessed_word[i + 1] != '\0'; ++i) {
                printf("%c ", guessed_word[i]);
                pos = i;
            }
            printf("%c", guessed_word[++pos]);
            printf("\n");
            continue;
        }

        bool already_guessed = false;
        for (int i = 0; i < strlen(letters_guessed); i++) {
            if (letters_guessed[i] == guess[0]) {
                already_guessed = true;
                break;
            }
        }
        if (already_guessed){
            printf("Oops! You've already guessed that letter: ");
            get_guessed_word(secret, letters_guessed, guessed_word);
            for (int i = 0; guessed_word[i + 1] != '\0'; ++i) {
                printf("%c ", guessed_word[i]);
                pos = i;
            }
            printf("%c", guessed_word[++pos]);
            printf("\n");
            continue;
        }
        else{
            int len = strlen(letters_guessed);
            letters_guessed[len] = guess[0];
            letters_guessed[len + 1] = '\0'; 
        }
        
        if (strchr(secret, guess[0]) != NULL) {
            printf("Good guess: ");
        } else {
            printf("Oops! That letter is not in my word: ");
            guesses--;
        }
        get_guessed_word(secret, letters_guessed, guessed_word);
        for (int i = 0; guessed_word[i+1] != '\0'; ++i) {
            printf("%c ", guessed_word[i]);
            pos = i;
        }
        printf("%c", guessed_word[++pos]);
        printf("\n");

        if(is_word_guessed(secret, letters_guessed)){
            printf("-------------\n");
            printf("%s\n", "Congratulations, you won!");
            return;
        }
        if(guesses <= 0){
            printf("-------------\n");
            printf("Sorry, you ran out of guesses. The word was %s.", secret);
            break;
        }
    }
    printf("\n");
}
