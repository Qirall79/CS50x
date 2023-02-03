// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];



// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    //getting the index from the hash function
    int index = hash(word);

    node *linkedList = table[index];

    if(linkedList == NULL)
    {
        return false;
    }

    node *cursor = linkedList;

    //looping through the linked list to which the word belongs and checking if the word is there
    while(cursor != NULL)
    {

        if(strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }
    return false;

}


// Hashes word to a number

unsigned int hash(const char *word)
{
    // Function should take a string and return an index
    // This hash function adds the ASCII values of all characters in     the word together
    long sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }
    return sum % N;
}

int count = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *f = fopen(dictionary, "r");

    //checking if the file is NULL
    if(f == NULL)
    {
        return false;
    }


    //allocating memory to the word
    char *word = malloc(LENGTH + 1);

    //reading each word of the dictionary until its end
    while(fscanf(f, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));

        if(n == NULL)
        {
            free(f);
            free(word);

            return false;
        }

        //getting the index of the linked list inside of the table from the hash function
        int index = hash(word);

        //copying the word into the node created above
        strcpy(n->word, word);

        //getting the linked list
        node *linkedList = table[index];

        //checking if there are some nodes in that linked list
        if(linkedList == NULL)
        {
            //if there are no nudes we gonna set the list to point to n and the next node of n to NULL since there are no more nodes
            n->next = NULL;

            table[index] = n;


        }

        else
        {
            n->next = linkedList;

            table[index] = n;
        }

        count++;

    }

    fclose(f);
    free(word);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    // TODO
    return count;

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    //looping through the table
    for(int i = 0; i < N; i++)
    {
        node *linkedList = table[i];

        node *cursor = linkedList;


        //looping through every linked list in the table until its end and freeing every node;
        while(cursor != NULL)
        {

            node *tmp = cursor;

            cursor = cursor->next;

            free(tmp);
        }
    }
    return true;
}


