#include <stdio.h>
#include <cs50.h>
#include <string.h>

#define MAX 9


//defining the initial arrays
string candidates[MAX];

int preferences[MAX][MAX];

bool locked[MAX][MAX];

//defining the struct
typedef struct
{
    int winner;
    int loser;
}
pair;

pair pairs[MAX*MAX];

//defining global variables
int pair_count;
int candidate_count;


//functions
bool vote(int rank, string name, int ranks[candidate_count]);

void record_preferences(int ranks[candidate_count]);

void add_pairs(void);

void sort_pairs(void);

bool detect_cycle(int start, int end);

void lock_pairs(void);

void print_winner(void);

//main function
int main(int argc, string argv[])
{
    candidate_count = argc - 1;

    for(int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    int voters_number = get_int("Number of voters: ");

    for(int i = 0; i < voters_number; i++)
    {
        int ranks[candidate_count];

        for(int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            //vote function
            vote(j, name, ranks);

        }

        //recording preferences
        record_preferences(ranks);

        printf("\n");
    }

    //adding pairs to the pairs array
    add_pairs();

    //sorting pairs
    sort_pairs();

    //locking pairs
    lock_pairs();

    //printing the winner
    print_winner();

}


bool vote(int rank, string name, int ranks[candidate_count])
{
    for(int i = 0; i < candidate_count; i++){

        if(strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;

            return true;
        }
    }

    return false;
}


void record_preferences(int ranks[candidate_count])
{
    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}


void add_pairs(void)
{
    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = i + 1; j < candidate_count; j++)
        {
            if(preferences[i][j] > preferences[j][i] || preferences[i][j] < preferences[j][i])
            {
                pair_count++;
            }

        }
    }

    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = i + 1; j < candidate_count; j++)
        {
            if(preferences[i][j] > preferences[j][i])
            {
                for(int k = 0; k < pair_count; k++)
                {
                    if(!pairs[k].winner && !pairs[k].loser)
                    {
                        pairs[k].winner = i;
                        pairs[k].loser = j;

                    }


                }
            }
            else if(preferences[i][j] < preferences[j][i])
            {
                 for(int k = 0; k < pair_count; k++)
                {

                    if(!pairs[k].winner && !pairs[k].loser)
                    {
                        pairs[k].winner = j;
                        pairs[k].loser = i;

                    }

                }
            }
        }
    }

}


void sort_pairs(void)
{
    for(int i = 0; i < pair_count; i++)
    {
        for(int j = 0; j < pair_count - i; j++)
        {
            int winDiff = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            int winDiffNext = preferences[pairs[j + 1].winner][pairs[j + 1].loser] - preferences[pairs[j + 1].loser][pairs[j + 1].winner];

            if( winDiff < winDiffNext)
            {
                int tempWin = pairs[j + 1].winner;
                int tempLose = pairs[j + 1].loser;

                pairs[j + 1].winner = pairs[j].winner;
                pairs[j + 1].loser = pairs[j].loser;

                pairs[j].winner = tempWin;
                pairs[j].loser = tempLose;
            }
        }
    }
}


void lock_pairs(void)
{
    // goes through every pair and check if there's no cycle, lock
    for(int i = 0; i < pair_count; i++)
    {
            if(!detect_cycle(pairs[i].winner, pairs[i].loser))
            {
                locked[pairs[i].winner][pairs[i].loser] = true;
            }

    }

}


bool detect_cycle(int start, int end)
{

    if(start == end)
    {
        //true means cycle detected
        return true;
    }

    //loops through every candidate to see if the end of arrow is locked with a candidate

    for(int k = 0; k < candidate_count; k++)
    {
        if(locked[end][k])
        {
            //checking if that candidate is the same as the start of the arrow
            if(k == start)
            {
                return true;
            }
            else
            {
               if(detect_cycle(start, k))
               {
                   return detect_cycle(start, k);
               }

            }
        }


    }
    //means that end is not locked to any candidate
    return false;
}

void print_winner(void)
{

    string winner;

    //loops through the candidates and see if there's a candidate who has no arrows pointing to him, aka source of the graph

    for(int i = 0; i < candidate_count; i++)
    {
        bool isSource = true;

        for(int j = 0; j < candidate_count; j++)
        {
            if(locked[j][i])
            {
                isSource = false;
            }
        }

        if(isSource)
        {
            winner = candidates[i];
        }
    }

    printf("%s\n", winner);
}


