#include <stdio.h>

struct test {
    char a;
    int b;
};

struct test_p {
    char a;
    int b;
} __attribute__((packed));

int main(void)
{
    char str[10] = {
        'A', 0, 0, 0, 0,
        'B', 0, 0, 0, 0
    };

    struct test *ptr1 = (struct test *) str;

    printf("\nNon-packed version of the struct (size: %lu)\n",
        sizeof(struct test));

    for (int i = 0; i != 2; i++, ptr1++) {
        printf(" ptr{a} => %c\n", ptr1->a);
        printf(" ptr{b} => %d\n", ptr1->b);
    }

    struct test_p *ptr2 = (struct test_p *) str;

    printf("\nPacked version of the struct (size: %lu)\n",
        sizeof(struct test_p));

    for (int i = 0; i != 2; i++, ptr2++) {
        printf(" ptr{a} => %c\n", ptr2->a);
        printf(" ptr{b} => %d\n", ptr2->b);
    }

    puts("");

    return 0;
}
