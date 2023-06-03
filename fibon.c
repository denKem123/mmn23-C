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
        create_fibonacci_list(&hptr, num);
        print_fibonacci_list(hptr);
        save_fibonacci_list(hptr);
        free_fibonacci_list(&hptr);
        printf("\nXxx\n");
    }
    else
    {
        printf("A positive integer is required\n");
        exit(0);
    }

    return 0;
}

ptr create_fibonacci_list(ptr *hptr, int num)
{
    ptr p;
    if (num == 0)
    {
        p = create_fibonacci(NULL, 1);
        p->next = p;
        *hptr = p;
        return p;
    }
    else
    {
        p = create_fibonacci_list(hptr, num - 1);
        if (num == 1)
        {
            p->next = create_fibonacci(*hptr, 1);
            return *hptr;
        }
        else
        {
            p->next->next = create_fibonacci(*hptr, p->num + p->next->num);
        }
    }
    return p->next;
}

ptr create_fibonacci(ptr hptr, int num)
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

void print_fibonacci_list(ptr hptr)
{
    printf("\n");
    print_fibonacci_list_recursive(hptr, hptr->next);
    printf("%d\n", hptr->num);
}

void print_fibonacci_list_recursive(ptr hptr, ptr current)
{
    if (current == hptr)
        return;
    print_fibonacci_list_recursive(hptr, current->next);
    printf("%d ->", current->num);
}

void save_fibonacci_list(ptr hptr)
{
}

void free_fibonacci_list(ptr *hptr)
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