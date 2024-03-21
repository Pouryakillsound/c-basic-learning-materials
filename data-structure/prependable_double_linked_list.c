#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define N 2 // length of list

typedef struct node
{
        struct node *next, *prev; // two pointer one to the next elemenet and one to the previous element of the list
        int data;
}
node;


void printf_forward(node *list) // function for printing it from the first element to the last one
{
        for(node *ptr = list; ptr; ptr = ptr->next)
        {        
                printf("%i", ptr->data);
                if (ptr->next)
                        printf(" -> ");
        }
        printf("\n");

}

void printf_backward(node *list) // function for printing it from last one element to the the first in reversed direction
{
        node *ptr = list;
        /* This while loop will set the ptr to the last element */
        while (ptr->next)
                ptr = ptr->next;

        for (; ptr; ptr = ptr->prev) // Moving backwards
        {
                printf("%i", ptr->data);
                if (ptr->prev)
                printf(" <- ");
        }
        printf("\n");

}

bool free_all(node *list) // Function for free all malloced elements 
{
        if (!list) return false;
        node *ptr = list;
        free_all(ptr->next);
        free(ptr);

}

int main()
{
        node *list = NULL; // Initializing list pointer to NULL
        int data[N] = {2, 3}; // Example data
        /* This for loop is a typical prepending */
        for (int i=0; i < N; i++)
        {
                node *n = calloc(1, sizeof(node)); // using calloc because it sets all bytes to 0 so the pointers prev and next would be set to zero and we dont have to do it by hand
                n->data = data[i];
                if (!list) list = n;
                else
                {
                        n->next = list;
                        list->prev = n;
                        list = n;
                }
        }
        /* Printing them both ways to see the difference*/
        printf_backward(list); // This shows an appending format 
        printf("-------\n");
        printf_forward(list); // This shows a prepending format
        free_all(list); // Freeing memory
        return 0;
}