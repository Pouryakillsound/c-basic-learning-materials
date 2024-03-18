/*
* An appendable linked list.  
* written based by cs50 harvard course
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 4 // length of the linked list
/*
* struct for a single linked list given a name node
*/
typedef struct node
{
    char *data; // it contains a string
    struct node *next; // and a pointer to the next item
}
node;

// At the end we would always be freeing all the malloced variables to OS
bool free_list(node *root)
{       
        if (!root) return false;
        if (root)
        {
                free_list(root->next); // Recursive call to free all the nodes following 
                free(root);
                return true;
        }
}


int main()
{       

        char *datas[N] = {"data1", "data2", "data3", "data4"}; // example data
        node *list = NULL; // initializing the list to NULL so we are going to expand it
        node *tmp = NULL; // A temporary value for keeping the address of beginning of the linked list
        for (int i = 0; i < N; i++)
        {
                char *c = datas[i];
                node *n = malloc(sizeof(node));
                if (!list) // if it is NULL: it happens only at the first cycle of the loop
                {
                        list = n; // set the list = n because there is only one element
                        list->data = datas[i]; // setting its data
                        tmp = list; // Giving the address to the tmp (this is the beginning of the list)
                }
                list->next = n; // Assigning n to the next item and the end of the list
                list = list->next; // Moving list variable to the last element of the list
                list->data = datas[i]; // Setting the data
                list->next = NULL; // Setting the next value to NULL: in the last cycle this will terminate the linked list
        }
        list = tmp; // Moving cursor to the beginning of the list

        /*
        * this part is so crucial : 1: we could instead have a iterator i and get into the loop but
        * we have a more brilliant implementaion for printing data of 
        * -------------------------------------------------------------------------------------------
        * 2: the line 38 in the code where we set the next pointer to NULL 
        * so we are sure that there is no garbage value randomly pointing to some direction
        * therefore we rely on that and walk through it until the NULL terminator 
        */
        for (node *ptr = list; ptr; ptr = ptr->next)
        {
                printf("%s\n", ptr->data); // In the output we expect to see them in order (not sorted only from first to last) because we are appending
        }
        free_list(list); // Frees all variables
        return 0;
}



// Now think about this: Why did I use a pionter for variables list, n and tmp?
