#include <stdio.h>

#define MAX_WORD_LENGTH 256

int is_start_word(const char *word, int length) {
    return length == 5 && word[0] == 'S' && word[1] == 'T' && word[2] == 'A' && word[3] == 'R' && word[4] == 'T';
}

int is_stop_word(const char *word, int length) {
    return length == 4 && word[0] == 'S' && word[1] == 'T' && word[2] == 'O' && word[3] == 'P';
}

void write_word(FILE *output, const char *word, int first_word) {
    if (!first_word) {
        fputc(' ', output); // Add a space before writing the word if it's not the first word
    }
    for (int i = 0; word[i] != '\0'; i++) {
        fputc(word[i], output);
    }
}

void process_file(FILE *input, FILE *output) {
    int in_word = 0, write_mode = 0, word_count = 0;
    char current_word[MAX_WORD_LENGTH];
    int index = 0;
    char ch;
    int first_word = 1; 

    while ((ch = fgetc(input)) != EOF) {
        if (ch == ' ' || ch == '\n') {
            if (in_word) {
                current_word[index] = '\0';
                in_word = 0;

                if (write_mode) {
                    if (word_count % 2 == 1 && !is_stop_word(current_word, index)) {
                        write_word(output, current_word, first_word);
                        first_word = 0; 
                    }
                    word_count++;
                }

                if (!write_mode && is_start_word(current_word, index)) {
                    write_mode = 1;
                    word_count = 0;
                }

                if (write_mode && is_stop_word(current_word, index)) {
                    write_mode = 0;
                }

                index = 0;
            }
        } else {
            if (!in_word) in_word = 1;
            if (index < MAX_WORD_LENGTH - 1) current_word[index++] = ch;
        }
    }

    if (in_word) {
        current_word[index] = '\0';
        if (write_mode && word_count % 2 == 1 && !is_stop_word(current_word, index)) {
            write_word(output, current_word, first_word);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;

    FILE *input = fopen(argv[1], "r");
    if (!input) return 1;

    FILE *output = fopen(argv[2], "w");
    if (!output) {
        fclose(input);
        return 1;
    }

    process_file(input, output);

    fclose(input);
    fclose(output);
    return 0;
}
