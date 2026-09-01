#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // 1. Keyword test: 'class' and 'new' are reserved in C++, but just normal names in C
    int class = 10;
    int new = 20;

    // 2. Pointer conversion test: C allows implicit void* to int* conversion. C++ strictly forbids this.
    int *ptr = malloc(sizeof(int));
    *ptr = class + new;

    // 3. Character literal size test: C treats 'a' as an int (size 4), C++ treats it as a char (size 1)
    printf("sizeof('a') = %zu (Should be 4 in C)\n", sizeof('a'));

    // 4. Standard macro test: __STDC_VERSION__ is only defined in standard C
    #ifdef __STDC_VERSION__
        printf("C Standard Version: %ld\n", __STDC_VERSION__);
    #else
        printf("Not compiled as standard C!\n");
    #endif

    printf("Pointer value result: %d\n", *ptr);

    free(ptr);
    return 0;
}