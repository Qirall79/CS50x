#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char *word = "f'Oo";
    char *cursor = "F'oo";

    int cmp = strcasecmp(word, cursor);

    printf("%i\n", cmp);
}