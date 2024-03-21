#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define N 2

typedef struct node
{
        struct node *next, *prev;
        int data;
}
node;


void printf_forward(node *list)
{
        for(node *ptr = list; ptr; ptr = ptr->next)
        {        
                printf("%i", ptr->data);
                if (ptr->next)
                        printf(" -> ");
        }
        printf("\n");

}

void printf_backward(node *list)
{
        node *ptr = list;
        while (ptr->next)
                ptr = ptr->next;
        for (; ptr; ptr = ptr->prev)
        {
                printf("%i", ptr->data);
                if (ptr->prev)
                printf(" <- ");
        }
        printf("\n");

}

bool free_all(node *list)
{
        if (!list) return false;
        node *ptr = list;
        free_all(ptr->next);
        free(ptr);

}

int main()
{
        node *list = NULL;
        int data[N] = {2, 3};
        for (int i=0; i < N; i++)
        {
                node *n = malloc(sizeof(node));
                n->data = data[i];
                n->next = NULL;
                n->prev = NULL;
                if (!list) list = n;
                else
                {
                        n->next = list;
                        list->prev = n;
                        list = n;
                }
        }
        
        printf_backward(list); // This shows an appending format 
        printf("-------\n");
        printf_forward(list); // This shows a prepending format
        free_all(list);
        return 0;
}