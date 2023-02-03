#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

#define MAX 9

typedef struct
{
    string name;
    int votes;
}
candidate;

candidate candidates[MAX];

int candidate_count;

bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    candidate_count = argc - 1;

    if(candidate_count <= MAX)
    {
        for(int i = 0; i < candidate_count; i++)
        {
            candidates[i].name = argv[i + 1];
            candidates[i].votes = 0;
        }
    }

    int voters_number = get_int("Number of Voters: ");

    for(int i = 0; i < voters_number; i++)
    {
        string name = get_string("Vote: ");

        // voting
        if(!vote(name))
        {
            printf("Invalid vote.\n");
        }
        else
        {
            vote(name);
        }
    }

    print_winner();




}

bool vote(string name)
{
    for(int i = 0; i < candidate_count; i++)
    {
        if(strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }

    return false;
}

void print_winner(void)
{

    int max_votes = 0;

    for(int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    }

    for(int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes == max_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}

