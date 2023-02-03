#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while(height < 1 || height > 8);

    for(int i = 0; i < height; i++)
    {
        for(int k = height - i - 1; k > 0; k--)
        {
            printf(" ");
        }

        for(int j = 0; j <= i; j++)
        {
            printf("#");
        }

        for(int l = 0; l < 2; l++)
        {
            printf(" ");
        }

        for(int m = 0; m <= i; m++){
            printf("#");
        }

        printf("\n");
    }


}