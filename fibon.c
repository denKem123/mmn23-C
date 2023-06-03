#include <stdio.h>
#include <stdlib.h>
#include "fibon.h"
#include "files.h"

int main(int argc, char *argv[])
{
    ptr hptr = NULL;
    int num;

    if (argc == 1)
    {
        printf("\nPlease provide a path file for the fibonacci value\n");
        exit(0);
    }

    printf("\nPlease enter the amount of fibonacci numbers:\n");
    if (scanf("%d", &num) == 1 && num >= 0)
    {
        createfibonlist(&hptr, num);
        printfibonlist(hptr);
        savefibonlist(hptr);
        freefibonlist(&hptr);
        printf("\nXxx\n");
    }
    else
    {
        printf("A positive integer is required\n");
        exit(0);
    }

    return 0;
}

ptr createfibonlist(ptr *hptr, int num)
{
    ptr p;
    if (num == 0)
    {
        p = createfibon(NULL, 1);
        p->next = p;
        *hptr = p;
        return p;
    }
    else
    {
        p = createfibonlist(hptr, num - 1);
        if (num == 1)
        {
            p->next = createfibon(*hptr, 1);
            return *hptr;
        }
        else
        {
            p->next->next = createfibon(*hptr, p->num + p->next->num);
        }
    }
    return p->next;
}

ptr createfibon(ptr hptr, int num)
{
    ptr fib;

    fib = (ptr)malloc(sizeof(fibnum));
    if (!fib)
    {
        printf("Not enough Memory\n");
        exit(0);
    }
    fib->num = num;
    fib->next = hptr;
    return fib;
}

void printfibonlist(ptr hptr)
{
    ptr current;
    current = hptr;
    printf("\n");
    do
    {
        printf("%d %s ", current->num, current->next != hptr ? "-> " : "");
        current = current->next;
    } while (current != hptr);
    printf("\n");
}

void savefibonlist(ptr hptr)
{
}

void freefibonlist(ptr *hptr)
{
    ptr p;
    while (*hptr)
    {
        p = (*hptr)->next;
        if (p == *hptr)
            *hptr = NULL;
        else
            (*hptr)->next = (*hptr)->next->next;
        free(p);
    }
}