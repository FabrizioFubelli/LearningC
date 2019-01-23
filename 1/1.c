#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void test1(), test2(), test3(), test4(), test5(), test6(), test7();

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
    } else if (strcmp(argv[1], "4") == 0) {
        test4();
    } else if (strcmp(argv[1], "5") == 0) {
        test5();
    } else if (strcmp(argv[1], "6") == 0) {
        test6();
    } else if (strcmp(argv[1], "7") == 0) {
        test7();
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
    char* strcat(char* dest, const char* src) {
        char* cat = dest;
        while(*dest) dest++;
        //while(*dest++ = *src++);
        do {
            *dest++ = *src;
        } while(*++src);
        return cat;
    }
    char* dest = (char*) malloc(sizeof(char)*13);
    strcpy(dest, "INIZIO");
    char* src =  " FINE";
    char* concatenate = strcat(dest, src);
    printf("%s\n", concatenate);
}

void test4() {
    printf("sizeof(int) = %d\n",sizeof(int));                               // 4
    void* bar = malloc(320);                                                // 320 bytes
    void* baz = &((int*)bar)[5];                                            // pointer to &bar + 4*5
    printf("(char*)baz = %ld\n", (char*)baz);
    printf("(char*)bar = %ld\n", (char*)bar);
    printf("(char*)baz - (char*)bar) = %ld\n", (char*)baz - (char*)bar);    // 20
    free(bar);
}

void test5() {
    struct {
        char s1[3];
        char s2[5];
    } s;
    strcpy(s.s1, "ok");
    strcpy(s.s2, "flag");
    printf("sizeof(&s) = %d\n", sizeof(&s));                     // 8
    printf("&((char*) s)[3] = %s\n", &((char*) &s)[3]);
}

void test6() {
    void f(char* s) {
        do *s = *s > 'a' && *s < 'z' ? *s - 'a' + 'A' : *s;
        while (*s++);
    }
    char* b = (char*) malloc(sizeof(char)*6);
    strcpy(b, "guess");
    printf("\n(BEFORE) b = %s\n", b);
    f(b);
    printf("(AFTER)  b = %s\n", b);
}

void test7() {
    #define X 250
    int* f(int x) {
        unsigned char i = (unsigned char)x;
        printf("i = %u\n", i);
        printf("(char) i = %c\n", (char) i);
        printf("(int) i = %d\n", (int) i);
        int* v = (int*)malloc(100*sizeof(int));

        printf("i < 100 = %d\n", i < 100 );
        printf("(char) i < 100 = %d\n", (char) i < 100 );

        if (v != NULL && (char) i < 100) {  // Overflow if x not multiple of 4 and x >= 100
            v[i] = x;
            printf("written on vector: v[%u] = %d\n", i, v[i]);
        }
        return v;
    }
    /*printf("sizeof(int) = %d\n", sizeof(int));
    printf("sizeof(long) = %d\n", sizeof(long));
    printf("sizeof(unsigned char) = %d\n", sizeof(char));*/
    printf("f(%d)[%d] = %d\n", X, X, f(X)[X]);
    printf("\n");
}
