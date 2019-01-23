#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void declarations(), test1(), test2(), test3(), test4();
char* strcat(char* dest, const char* src);

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
    } else if (strcmp(argv[1], "3") == 0) {
        test3();
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

    printf("sizeof(int) = %d\n", sizeof(int));  // 4
    printf("a = %d\n", a);                      // pointer
    printf("a+1 = %d\n", a+1);                  // pointer + 12 (12 = sizeof(int)*3)

    int sum = 1*N+1;                            // 4

    printf("1*N+1 = %d\n", sum);
    printf("a+1*N+1 = %d\n", a+sum);            // pointer + 48 (48 = (sizeof(int)*3)*4)
    printf("sizeof(a) = %d\n", sizeof(a));      // 36 == sizeof(int)*N*M
    printf("**a = %d\n", **a);

    int result = **(a+1*N+1);                   // a+1*N+1 + 32
    printf("**(a+1*N+1) = %d\n", result);

    printf("*(a+1) = %d\n", *(a+1));            // a+1
    int result2 = *(*(a+1)+1);                  // 5
    printf("*(*(a+1)+1) = %d\n", result2);

    printf("\n\nWhy these results:\n\n");
    printf("int a[%d][%d] = {1,2,3,4,5,6,7,8,9}\n\n", N, N);

    printf("**a   = %d\n", **a);                // 1
    printf("**a+1 = %d\n", **a+1);              // 2
    printf("**a+2 = %d\n", **a+2);              // 3
    printf("**a+3 = %d\n", **a+3);              // 4
    printf("**a+4 = %d\n", **a+4);              // 5
    printf("**a+8 = %d\n\n", **a+8);            // 9

    printf("**(a)   = %d\n", **(a));            // 1 == **a
    printf("**(a+1) = %d\n", **(a+1));          // 4 == **a+N*1 == **a+3
    printf("**(a+2) = %d\n", **(a+2));          // 7 == **a+N*2 == **a+6

    // printf("**(a+3) = %d\n", **(a+3));       // Overflow ( **a+N*3 == **a+9 )

}

void test3() {
    char* dest = (char*) malloc(sizeof(char)*11);
    strcpy(dest, "INIZIO");
    char* src =  " FINE";
    char* concatenate = strcat(dest, src);
    printf("%s\n", concatenate);
}

void test4() {
    void* bar = malloc(320);
    void* baz = &((long*)bar)[???];
    printf("%ld\n", (char*)baz - (char*)bar);
    free(bar);
}


void declarations() {
    int x;
    int a, b, c, d;
    char letter;
    float the_float;
}

char* strcat(char* dest, const char* src) {
    char* cat = dest;
    while(*dest) dest++;
    //while(*dest++ = *src++);
    do {
        *dest++ = *src;
    } while(*++src);
    return cat;
}
