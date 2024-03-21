/*
* This code may not be that proper for general learning but it helped me a lot 
* This program only supports a-z and not capital letter
* Just a simple trie implementation with which contains no data
* Memory leak is checked with valgrind and there was nothing captured as leak: 19 allocs, 19 frees, 4,912 bytes allocated
* You can follow this link for original implementation: https://www.geeksforgeeks.org/trie-delete/ but here we will free all nodes too
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0]) // return size of an array by a simple formula
#define ALPHABET_SIZE (26) // size of children of tries
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') // returns 0-25 index based on alphabets from a-z and not capitals

// A pretty usual and simple struct for trie
typedef struct TrieNode //
{
        struct TrieNode *children[ALPHABET_SIZE];
        bool isEndOfWord;
}
node;

// Function for returning a pointer to a node of trie with all NULL pointer
node *getNode(void)
{
        node *n = NULL; // initializing a pointer to NULL
        n = malloc(sizeof(node)); // giving it some space
        
        if (n) // if it is not NULL
        {
                int i;
                n->isEndOfWord = false;
                for (i = 0; i < ALPHABET_SIZE; i++)
                n->children[i] = NULL; // deleting all GARBAGE VALUES and setting childrens to NULL
        }
        return n; // returning a fresh and new trie
}

// Function for inserting a key into trie data structure
bool insert (node *root, const char *key)
{
        if (!root) return false;
        int level;
        int length = strlen(key);
        int index;
        node *n = root;
        for (level = 0; level < length; level++) // walking throughout the word
        {
                index = CHAR_TO_INDEX(key[level]);
                if (!n->children[index]) // if NULL
                        n->children[index] = getNode(); // Giving it a fresh node
                n = n->children[index]; // going to the next level
        }
        n -> isEndOfWord = true; // At the end assign true to isEndOfWord to indicate that word ends here and this is it 
        return true;
}


// Funtion for searching a key in tries
bool search(node *root, const char *key)
{
        int level; // used for looping over the chars of the string in the bellow loop
        int length = strlen(key); // 
        int index;
        node *n = root;
        for (level=0; level<length; level++) // walking throughout the word
        {
                index = CHAR_TO_INDEX(key[level]);

                if (!n->children[index])
                        return false;
                n = n->children[index];
        }
        return (n->isEndOfWord);
}

// At the end we would have to free all malloced valued in order to have a pretty memory management
bool free_all(node *root)
{
        node *n = root;
        if (!n) return false;// if the coming pointer contains NULL then close the function by returning false
        // if block is not pointing to NULL
        for (int i=0; i < ALPHABET_SIZE; i++)
        {
                free_all(n->children[i]); // recursively freeing all the i'th children's nodes     
        }
        free(n);
        return true; // after all return true which is a sign of success
}


int main()
{       
        // Pay attention to keys NO CAPITAL LETTER
        char keys[][8] = {"the", "a", "there", "answer", "any", 
                     "by", "bye", "their"};
        char output[][32] = {"Not present in trie", "Present in trie"}; // Used for result of searching

        node *root = getNode();
        int i;
        for (i=0; i < ARRAY_SIZE(keys); i++)
                insert(root, keys[i]);

        /* Examples of searching*/
        printf("%s ---- %s \n", "the", output[search(root, "the")]);
        printf("%s ---- %s \n", "the", output[search(root, "USA")]);

        free_all(root); // Freeing all nodes
        return 0;
}