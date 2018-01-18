#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VSIZE 6
#define CSIZE 20

char vowels[VSIZE] = {
    'a', 'e', 'i', 'o', 'u', 'y'
};

char consonants[CSIZE] = {
    'b', 'c', 'd', 'f', 'g',
    'h', 'j', 'k', 'l', 'm',
    'n', 'p', 'q', 'r', 's',
    't', 'v', 'w', 'x', 'z'
};

void generator(void);

int main(void)
{
    generator();

    return 0;
}

void generator(void)
{
    srand((unsigned)time(NULL));

    int counter = 0;
    int len = 3 + rand() % 6; // range: [3..8]

    char *name = malloc(sizeof(char) * len);

    if (rand() % 2) {
        name[0] = toupper(consonants[rand() % (CSIZE - 1)]);
        counter++;
    } else {
        name[0] = toupper(vowels[rand() % (VSIZE - 1)]);
        counter--;
    }

    for (int i = 1; i < len; ++i) {
        double isConsonant = rand() % 2;

        if (isConsonant && counter < 1) {
            name[i] = consonants[rand() % (CSIZE - 1)];
            counter++;
        } else if (isConsonant && counter >= 1) {
            name[i] = vowels[rand() % (VSIZE - 1)];
            counter--;
        } else if (!isConsonant && counter > -1) {
            name[i] = vowels[rand() % (VSIZE - 1)];
            counter--;
        } else {
            name[i] = consonants[rand() % (CSIZE - 1)];
            counter++;
        }
    }

    name[len] = '\0';

    fprintf(stdout, "\n Generated name ~> %s\n\n", name);

    free(name);
}
