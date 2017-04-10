#include <stdio.h>
#include <stdlib.h>

#include "inc/complex.h"

void helper();

int main(int argc, char **argv)
{
	char op;
	int detailed = 0;
	complex res, z1, z2;

	helper();

	while (1) {
		printf("\nInput operation: ");
		scanf(" %c", &op);

		if (op == '+' || op == '-' || op == '*' || op == '/') {
			puts("\n# COMPLEX NUMBER 1 #");
			printf(" Re > ");
			scanf("%f", &z1.x);
			printf(" + \n");
			printf(" Im > ");
			scanf("%f", &z1.y);

			puts("\n# COMPLEX NUMBER 2 #");
			printf(" Re > ");
			scanf("%f", &z2.x);
			printf(" + \n");
			printf(" Im > ");
			scanf("%f", &z2.y);
		}

		switch (op) {
			case '+':
				res = c_add(z1, z2);
				c_output(res, z1, z2, op, detailed);
				break;
			case '-':
				res = c_sub(z1, z2);
				c_output(res, z1, z2, op, detailed);
				break;
			case '*':
				res = c_mul(z1, z2);
				c_output(res, z1, z2, op, detailed);
				break;
			case '/':
				res = c_div(z1, z2);
				c_output(res, z1, z2, op, detailed);
				break;
			case 'd':
				detailed ^= 0x1;
				if (detailed)
					puts("On");
				else
					puts("Off");
				break;
			case 'h':
				helper();
				break;
			case 'q':
				exit(EXIT_SUCCESS);
			default:
				puts("Unknown command");
		}
	}

	return 0;
}

/* Helper */
void helper()
{
	puts("");
	puts("+----------------------------------------+");
	puts("|    Complex number calculator    | v1.0 |");
	puts("|----------------------------------------|");
	puts("| Press '+','-','*' or '/' for operation |");
	puts("| Press 'd' to on/off detailed output    |");
	puts("| Press 'h' to call this window again    |");
	puts("| Press 'q' for exit the program         |");
	puts("+----------------------------------------+");
}
