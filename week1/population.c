#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{

    int start;
    do
    {
      start = get_int("Start size: ");
    }
    while (start < 9);

    int end;
    do
    {
      end = get_int("End size: ");
    }
    while (end < start);

    int years = 0;

    int n = start;

    while(n < end)
    {
        int gains = floor(n/3);
        int loses = floor(n/4);

        n += gains - loses;

        years++;
    }

    printf("Years: %i\n", years);
}