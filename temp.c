#include <stdio.h>

int main() {
    fprintf(stdout, "\x1b[34m");
    printf("hello world!!\n");
    fprintf(stdout, "\x1b[39m");
}