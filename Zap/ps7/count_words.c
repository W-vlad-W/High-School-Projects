#include <stdio.h>

int digit_count(int count, char digits[]){
    int digits_count = 0;
    do {
        digits[digits_count++] = count % 10;
        count /= 10;
    } while (count > 0 && digits_count < 10);
    return digits_count;
}

void clear_file(FILE *fp, int count){
    char digits[10];
    int digits_count = digit_count(count, digits);
    int i = digits_count - 1;
    while(i >= 0) {
        if (fputc('0' + digits[i], fp) == EOF) break;
        --i;
    }
}

int count_ananas(FILE *fp){
    int count = 0;
    char ananas[] = "ananas";
    char ch;
    int i = 0;
    while ((ch = fgetc(fp)) != EOF) {
        char lower_ch = (ch >= 'A' && ch <= 'Z') ? ch + ('a' - 'A') : ch;

        if (lower_ch == ananas[i]) {
            i++;
            if (i == 6) {
                count++;
                i = 0;
            }
        } else {
            i = (lower_ch == 'a') ? 1 : 0; 
        }
    }
    return count;
}

void count_words(int argc, char *argv[]){
    if (argc < 2) return;
    FILE *fp = fopen(argv[1], "r+");
    if (!fp) return;
    int count = count_ananas(fp);
    fclose(fp);

    fp = fopen(argv[1], "w+");
    if (!fp) return;
    clear_file(fp, count);
    fclose(fp);
}



int main(int argc, char *argv[]) {
    count_words(argc, argv);
    return 0;
}
