#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int higher_lower(void);
int heads_tails(void);

void _clrscr(void);
void _flush(void);
void print_menu(void);

int main(void)
{
    int choice;

    while (0x1) {

        print_menu();

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                higher_lower();
                break;
            case 2:
                heads_tails();
                break;
            case 3:
                exit(EXIT_SUCCESS);
            default:
                printf("Incorrect choice!\n");
                sleep(1);
                _flush();
        }
    }

    return 0;
}

int higher_lower(void)
{
    return 0;
}

int heads_tails(void)
{
    char coin[] = { '-', '\\', '|', '/' };

    while (0x1) {

        _clrscr();
        _flush();

        char choice;

        printf(" Heads or Tails? [h/t]: ");
        scanf("%c", &choice);

        if (choice != 'h' && choice != 't')
            choice = '\0';

        printf("\n ... ");

        for (int i = 0; i < 16; ++i) {
            printf("%c\b", coin[i % sizeof(coin)]);
            fflush(stdout);
            usleep(100000);
        }
        printf("%c", coin[0]);

        int r = rand() % 2;
        char result = (r == 0) ? 'h' : 't';

        printf(" (%c) \n", result);

        if (choice == result)
            printf("\n Yeah! ");
        else
            printf("\n Noob.. ");

        do {
            _flush();

            printf("Again? [y/n]: ");
            scanf("%c", &choice);

            if (choice == 'y')
                break;
            else if (choice == 'n')
                return 0;
            else {
                printf("Incorrect choice!\n");
                _flush();
            }

        } while (0x1);
    }

    return 0;
}

void _clrscr(void)
{
    printf("\033[H\033[2J");
}

void _flush(void)
{
    while (getchar() != '\n') {}
}

void print_menu(void)
{
    _clrscr();

    printf("\n ***\tMENU\t*** \n");
    printf("----------------------\n");
    printf(" 1. Higher/Lower game\n");
    printf(" 2. Heads/Tails game\n");
    printf(" 3. Quit\n\n");
    printf(" > ");
}

