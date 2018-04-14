#include <stdio.h>
#include <unistd.h>

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

    char input[10];
    char output[10];

    while(read(0, input, 1) > 0) {
        if (arr[input[0]] > 0) {
            for (int i = 0; i < strlen(argv[1]); i++) {
                if (input[0] == argv[1][i]) {
                    output[0] = argv[2][i];
                    write(1, output, 1);
                    break;
                }
            }
        } else {
            write(1, input, 1);
        }
        
    }
}