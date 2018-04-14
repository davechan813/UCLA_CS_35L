#include <stdio.h>

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        printf("The operands number is %d and should be 2!\n", argc - 1);
        return -1;
    }

    if (strlen(argv[1]) != strlen(argv[2])) {
        printf("The lengths of two operands should be the same!\n");
        return -2;
    }
    
    int arr[256] = {0};
    for (int i = 0; i < strlen(argv[1]); i++) {
        arr[argv[1][i]]++;
        if (arr[argv[1][i]] > 1) {
            printf("The '%c' character is duplicate in the first operand.\n", argv[1][i]);
            return -3;
        }
    }
    
    int c;
    while((c = getchar()) != EOF) {
        if (arr[c] > 0) {
            for (int i = 0; i < strlen(argv[1]); i++) {
                if (c == argv[1][i]) {
                    putchar(argv[2][i]);
                    break;
                }
            }
        } else {
            putchar(c);
        }
    }
}