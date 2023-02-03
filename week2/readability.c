#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    string text = get_string("Text: ");

    int letters = 0;
    int words = 0;
    int sentences = 0;

    for(int i = 0; i < strlen(text); i++)
    {
        if(isalpha(text[i]))
        {
            letters++;
        }
        if(isspace(text[i]))
        {
            words++;
        }
        if( text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    words += 1;

    float L = ((float) letters / (float) words) * 100; // 382,142
    float S = ((float) sentences / (float) words) * 100; // 7.14
    int grade = round((0.0588 * L) - (0.296 * S) - 15.8);

    if(grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if(grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);

    }


}