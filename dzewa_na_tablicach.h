#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wchar.h>

typedef struct tree {
    int ile;
    int ispapa;
    int value;
    struct tree *poprzednie;
    struct tree *rodzina[35];
} tree;
