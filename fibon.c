#include <stdio.h>
#include <stdlib.h>
#include "fibon.h"
#include "files.h"

int main(int argc, char *argv[])
{
    ptr *hptr = NULL;
    char *path;
    int num;

    if (argc == 1)
    {
        printf("\n Please provide a path file for the fibonacci value\n");
        exit(0);
    }
    path = argv[1];

    if (scanf("%d", &num) == 1 && num >= 0)
    {
        createfibonlist(hptr, num);
        printfibonlist(hptr);
        savefibonlist(hptr);
        freefibonlist(hptr);
    }
    else
    {
        printf("\nA positive integer is required\n");
        exit(0);
    }

    return 0;
}

ptr createfibonlist(ptr *hptr, int num)
{
    ptr p;
    if (num == 0)
    {
        *hptr = createfibon(p, 1);
        p = *hptr;
        p->next = p;
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
        printf("\nNot enough Memory\n");
        exit(0);
    }
    fib->num = num;
    fib->next = hptr;
    return fib;
}

void printfibonlist(ptr *hptr)
{
    ptr current;
    if (hptr == NULL)
    {
        printf("\ncan't print empty list!!!\n");
        return;
    }
    current = *hptr;
    printf("\n");
    do
    {
        printf("%d ->", current->num);
        current = current->next;
    } while (current != hptr);
    printf("*\n");
}

void savefibonlist(ptr *hptr)
{
    ptr *current;
    if (hptr == NULL)
    {
        printf("\ncan't save empty list!!!\n");
        return;
    }
}
void freefibonlist(ptr *hptr)
{
    ptr p;
    if (hptr == NULL)
    {
        printf("\ncan't free empty list!!!\n");
        return;
    }

    while (*hptr)
    {
        p = *hptr;
        *hptr = (*hptr)->next;
        free(p);
    }
}