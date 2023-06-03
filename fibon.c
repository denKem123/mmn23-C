#include <stdio.h>
#include <stdlib.h>
#include "fibon.h"

int main(int argc, char *argv[])
{
    ptr hptr = NULL;
    int num, scan;

    if (argc == 1)
    {
        printf("\nPlease provide a path file for the fibonacci value\n");
        exit(0);
    }

    printf("\nPlease enter the amount of fibonacci numbers:\n");
    if ((scan = scanf("%d", &num)) == 1 && num >= 0)
    {
        create_fibonacci_list(&hptr, num);
        print_fibonacci_list(hptr);
        save_fibonacci_list(argv[1], hptr, num);
        free_fibonacci_list(&hptr);
    }
    else if (scan == 1 && num > 89)
    {
        printf("the maximum fibonacci number that can be displayed as unsigned long is - 89\n");
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
    printf("%lu\n", hptr->num);
}

void print_fibonacci_list_recursive(ptr hptr, ptr current)
{
    if (current == hptr)
        return;
    print_fibonacci_list_recursive(hptr, current->next);
    printf("%lu -> ", current->num);
}

void save_fibonacci_list(char *path, ptr hptr, int num)
{
    printf("%s", path);
    FILE *file = fopen(path, "w");

    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        exit(0);
    }

    fprintf(file, "Your fibonacci numbers:\n");
    fprintf(file, "*for n = %d", num);
    fprintf(file, "\n");

    fclose(file);
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