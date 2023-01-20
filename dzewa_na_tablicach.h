#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wchar.h>

//dodac blanki bo na razie nie ma w wyswietlaniu wyniku
// globalna tablica punktacji aby nie musiec jej przenosic milion razy miedzy funkcjami

typedef struct tree {
    int ile;
    int ispapa;
    int value;
    struct tree *poprzednie;
    struct tree *rodzina[35];
} tree;
