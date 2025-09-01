#include <stdio.h>
#include <string.h>

int main() {
    char num[100];
    if (scanf("%99s", num) != 1) return 0;
    int sum = 0;
    for (int i = 0; num[i] != '\0'; i++) {
        sum += num[i] - '0';  
        if (sum >= 10) {
            sum = sum % 9;
            if (sum == 0) sum = 9;
        }
    }
    printf("%d\n", sum);

    return 0;
}
