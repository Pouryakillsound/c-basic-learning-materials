#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0]) 
#define ALPHABET_SIZE (26)
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// A pretty usual and simple struct for trie
typedef struct TrieNode
{
        struct TrieNode *children[ALPHABET_SIZE];
        bool isEndOfWord;
}
node;

// function for returning a pointer to a node of trie with all NULL pointer
node *getNode(void)
{
        node *n = NULL;
        n = malloc(sizeof(node));
        
        if (n)
        {
                int i;
                n->isEndOfWord = false;
                for (i = 0; i < ALPHABET_SIZE; i++)
                n->children[i] = NULL;
        }
        return n;
}

void insert (node *root, const char *key)
{
        int level;
        int length = strlen(key);
        int index;
        node *n = root;
        for (level = 0; level < length; level++)
        {
                index = CHAR_TO_INDEX(key[level]);
                if (!n->children[index])
                        n->children[index] = getNode();
                n = n->children[index];
        }
        n ->isEndOfWord = true;
}

bool search(node *root, const char *key)
{
        int level; // used for looping over the chars of the string in the bellow loop
        int length = strlen(key); // 
        int index;
        node *n = root;
        for (level=0; level<length; level++)
        {
                index = CHAR_TO_INDEX(key[level]);

                if (!n->children[index])
                        return false;
                n = n->children[index];
        }
        return (n->isEndOfWord);
}

bool free_all_tries(node *root)
{
        node *n = root;
        if (!n) // if the coming pointer contains NULL then close the function by returning false
                return false;
        else
        {
        for (int i = 0; i < ALPHABET_SIZE; i++) // looping over all the pointers of the n
                if (n->children[i]) // if block is not pointing to NULL
                {
                        free_all_tries(n->children[i]); // recursively freeing all the i'th children's nodes
                        free(n->children[i]); // free the i'th children itself
                }
        }
        return true; // after all return true which is a sign of success
}


int main()
{
        char keys[][8] = {"the", "a", "there", "answer", "any",
                     "by", "bye", "their"};
        char output[][32] = {"Not present in trie", "Present in trie"};

        node *root = getNode();
        int i;
        for (i=0; i < ARRAY_SIZE(keys); i++)
                insert(root, keys[i]);
        printf("%li\n", ARRAY_SIZE(keys));

        printf("%s ---- %s \n", "the", output[search(root, "the")]); // an example of searching
        free_all_tries(root); // freeing all nodes chained together
        free(root); // freeing the core root

}