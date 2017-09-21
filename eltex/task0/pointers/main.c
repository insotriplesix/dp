#include <stdio.h>

void print_result(int v1, int v2, int *p1, int *p2);
void swap_pointers(int **a, int **b);
void swap_values(int *a, int *b);

int main(void)
{
    int v1 = 0x539;
    int v2 = 0x5D0;

    int *p1 = &v1;
    int *p2 = &v2;

    printf("\nInitial state:\n\n");
    print_result(v1, v2, p1, p2);

    swap_pointers(&p1, &p2);

    printf("\nAfter swapping pointers:\n\n");
    print_result(v1, v2, p1, p2);

    swap_values(p1, p2);

    printf("\nAfter swapping values:\n\n");
    print_result(v1, v2, p1, p2);

    printf("\n");

    return 0;
}

void swap_pointers(int **a, int **b)
{
    int *tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap_values(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void print_result(int v1, int v2, int *p1, int *p2)
{
    printf(" v1: %p [%d]\n", &v1, v1);
    printf(" v2: %p [%d]\n", &v2, v2);
    printf("---------------------------\n");
    printf(" p1: %p [%d]\n", p1, *p1);
    printf(" p2: %p [%d]\n", p2, *p2);
}
