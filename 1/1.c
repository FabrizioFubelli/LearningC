#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void declarations(), test1(), test2();

int main(int argc, char* argv[]) {
    //getchar();  // Wait enter
    printf("\n");
    if (argc < 2) {
        printf("Usage: %s <test_number>\n\n", argv[0]);
        return 1;
    }
    if (strcmp(argv[1], "1") == 0) {
        test1();
    } else if (strcmp(argv[1], "2") == 0) {
        test2();
    } else {
        printf("Usage: %s <test_number>\n", argv[0]);
        printf("          Available tests: 1, 2\n\n");
        return 2;
    }
    printf("\n");
    return 0;
}

void test1() {
    const unsigned charSize = sizeof(char);
    const unsigned charSize4 = 4*sizeof(char);
    char* str = (char*) malloc(charSize4);

    printf("\n\nStart loop\n\n");
    const unsigned initial_length = strlen(str);
    unsigned i = 0;
    while(i < 132479) { // Segmentation fault with 132480
        printf("\n\nMem. addr  str[%d] = %d\n", i, &str[i]);
        printf("\n(BEFORE) str[%d] = %d\n", i, str[i]);
        str[i] = 'A';
        printf("(AFTER)  str[%d] = %c\n", i, str[i]);
        i++;
    }
    const unsigned final_length = strlen(str);
    printf("\n\nEnd loop\n\n");

    printf("sizeof(char) = %d\n", charSize);
    printf("sizeof(char)*4 = %d\n", charSize4);
    printf("sizeof(str) = %d\n", sizeof(str));    // sizeof pointer
    printf("\n(BEFORE LOOP) strlen(str) = %d\n", initial_length);
    printf("(AFTER LOOP)  strlen(str) = %d\n\n", final_length);
}

void test2() {
    #define N 3
    int a[N][N] = {1,2,3,4,5,6,7,8,9};
    printf("a = %d\n", a);
    int el5 = **(a+1*N+1);
    printf("**(a+1*N+1) = %d\n", el5);
}

void declarations() {
    int x;
    int a, b, c, d;
    char letter;
    float the_float;
}
