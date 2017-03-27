#include <dirent.h>
#include <dlfcn.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inc/complex.h"

#define MAXPLUGINS	5
#define BUFSIZE		128

void output(complex z, complex a, complex b, char op, int d);
void helper();

int main(int argc, char **argv)
{
	struct dirent *dir;
	DIR *dp;	// lol

	if ((dp = opendir("build/plugins")) == NULL) {
		fprintf(stderr, "Cannot open plugins folder");
		exit(EXIT_FAILURE);
	}

	int OPF = 0;
	char plugins[MAXPLUGINS][BUFSIZE];

	while ((dir = readdir(dp)) != NULL) {
		if (strstr(dir->d_name, ".so")) {
			printf("'%s' loaded\n", dir->d_name);
			if (strstr(dir->d_name, "add")) {
				OPF |= 0x1;
				strcpy(plugins[0], dir->d_name);
			} else if (strstr(dir->d_name, "sub")) {
				OPF |= 0x2;
				strcpy(plugins[1], dir->d_name);
			} else if (strstr(dir->d_name, "mul")) {
				OPF |= 0x4;
				strcpy(plugins[2], dir->d_name);
			} else if (strstr(dir->d_name, "div")) {
				OPF |= 0x8;
				strcpy(plugins[3], dir->d_name);
			}
		}
	}

	closedir(dp);

	helper();

	char op;
	int detailed = 0;
	complex res, z1, z2;

	while (1) {
		printf("\nInput operation: ");
		scanf(" %c", &op);

		if ((op == '+' && !(OPF & 0x1)) || (op == '-' && !(OPF & 0x2)) ||
			(op == '*' && !(OPF & 0x4)) || (op == '/' && !(OPF & 0x8))) {
			fprintf(stderr, "Operations is not supported (library not found)");
			continue;
		}

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

		char path[BUFSIZE] = "build/plugins/";
		char plugin_name[BUFSIZE];
		void *libhandler;
		complex (*mathfunc)(complex, complex);

		memset(plugin_name, '\0', sizeof(plugin_name));

		switch (op) {
			case '+':
				strcat(path, plugins[0]);
				if ((libhandler = dlopen(path, RTLD_LAZY)) == NULL) {
					fprintf(stderr, "Cannot open '%s'\n", plugins[0]);
					exit(EXIT_FAILURE);
				}
				strncpy(plugin_name, plugins[0], strlen(plugins[0]) - 3);
				mathfunc = dlsym(libhandler, plugin_name);
				res = mathfunc(z1, z2);
				dlclose(libhandler);
				output(res, z1, z2, op, detailed);
				break;
			case '-':
				strcat(path, plugins[1]);
				if ((libhandler = dlopen(path, RTLD_LAZY)) == NULL) {
					fprintf(stderr, "Cannot open '%s'\n", plugins[1]);
					exit(EXIT_FAILURE);
				}
				strncpy(plugin_name, plugins[1], strlen(plugins[1]) - 3);
				mathfunc = dlsym(libhandler, plugin_name);
				res = mathfunc(z1, z2);
				dlclose(libhandler);
				output(res, z1, z2, op, detailed);
				break;
			case '*':
				strcat(path, plugins[2]);
				if ((libhandler = dlopen(path, RTLD_LAZY)) == NULL) {
					fprintf(stderr, "Cannot open '%s'\n", plugins[2]);
					exit(EXIT_FAILURE);
				}
				strncpy(plugin_name, plugins[2], strlen(plugins[2]) - 3);
				mathfunc = dlsym(libhandler, plugin_name);
				res = mathfunc(z1, z2);
				dlclose(libhandler);
				output(res, z1, z2, op, detailed);
				break;
			case '/':
				strcat(path, plugins[3]);
				if ((libhandler = dlopen(path, RTLD_LAZY)) == NULL) {
					fprintf(stderr, "Cannot open '%s'\n", plugins[3]);
					exit(EXIT_FAILURE);
				}
				strncpy(plugin_name, plugins[3], strlen(plugins[3]) - 3);
				mathfunc = dlsym(libhandler, plugin_name);
				res = mathfunc(z1, z2);
				dlclose(libhandler);
				output(res, z1, z2, op, detailed);
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
				puts("Unknown input");
		}
	}

	return 0;
}

/*
 * z, a, b -> complex numbers
 * op      -> operation between them
 * d       -> detaied output
 */
void output(complex z, complex a, complex b, char op, int d)
{
	if (!d) {
		switch (op) {
		case '+':
			if (z.y > 0)
				printf("\n[z1 + z2] = %.2f + %.2fi\n", z.x, z.y);
			else
				printf("\n[z1 + z2] = %.2f - %.2fi\n", z.x, fabs(z.y));
			break;
		case '-':
			if (z.y > 0)
				printf("\n[z1 - z2] = %.2f + %.2fi\n", z.x, z.y);
			else
				printf("\n[z1 - z2] = %.2f - %.2fi\n", z.x, fabs(z.y));
			break;
		case '*':
			if (z.y > 0)
				printf("\n[z1 * z2] = %.2f + %.2fi\n", z.x, z.y);
			else
				printf("\n[z1 * z2] = %.2f - %.2fi\n", z.x, fabs(z.y));
			break;
		case '/':
			if (z.y > 0)
				printf("\n[z1 / z2] = %.2f + %.2fi\n", z.x, z.y);
			else
				printf("\n[z1 / z2] = %.2f - %.2fi\n", z.x, fabs(z.y));
			break;
		default:
			puts("Unknown operation");
		}
	}
	else {
		switch (op) {
		case '+':
			printf("\nz1 + z2 =>\n");
			printf("(%.2f + %.2fi) + (%.2f + %.2fi) =>\n", a.x, a.y, b.x, b.y);
			printf("(%.2f + %.2f) + (%.2f + %.2f)i =>\n", a.x, b.x, a.y, b.y);
			printf("%.2f + %.2fi\n", z.x, z.y);

			if (z.y > 0)
				printf("\n[z1 + z2] = %.2f + %.2fi\n", z.x, z.y);
			else
				printf("\n[z1 + z2] = %.2f - %.2fi\n", z.x, fabs(z.y));
			break;
		case '-':
			printf("\nz1 - z2 =>\n");
			printf("(%.2f + %.2fi) - (%.2f + %.2fi) =>\n", a.x, a.y, b.x, b.y);
			printf("(%.2f - %.2f) + (%.2f - %.2f)i =>\n", a.x, b.x, a.y, b.y);
			printf("%.2f + %.2fi\n", z.x, z.y);

			if (z.y > 0)
				printf("\n[z1 - z2] = %.2f + %.2fi\n", z.x, z.y);
			else
				printf("\n[z1 - z2] = %.2f - %.2fi\n", z.x, fabs(z.y));
			break;
		case '*':
			printf("\nz1 * z2 =>\n");
			printf("(%.2f + %.2fi) * (%.2f + %.2fi) =>\n", a.x, a.y, b.x, b.y);
			printf("(%.2f * %.2f - %.2f * %.2f) + (%.2f * %.2f + %.2f * %.2f)i =>\n",
				a.x, b.x, a.y, b.y, a.x, b.y, a.y, b.x);
			printf("%.2f + %.2fi\n", z.x, z.y);

			if (z.y > 0)
				printf("\n[z1 * z2] = %.2f + %.2fi\n", z.x, z.y);
			else
				printf("\n[z1 * z2] = %.2f - %.2fi\n", z.x, fabs(z.y));
			break;
		case '/':
			printf("\nz1 / z2 =>\n");
			printf("(%.2f + %.2fi) / (%.2f + %.2fi) =>\n", a.x, a.y, b.x, b.y);
			printf("(%.2f * %.2f + %.2f * %.2f) / (%.2f^2 + %.2f^2) +",
				a.x, b.x, a.y, b.y, b.x, b.y);
			printf("(%.2f * %.2f - %.2f * %.2f) / (%.2f^2 + %.2f^2)i =>\n",
				b.x, a.y, a.x, b.y, b.x, b.y);
			printf("%.2f + %.2fi\n", z.x, z.y);

			if (z.y > 0)
				printf("\n[z1 / z2] = %.2f + %.2fi\n", z.x, z.y);
			else
				printf("\n[z1 / z2] = %.2f - %.2fi\n", z.x, fabs(z.y));
			break;
		default:
			puts("Unknown operation");
		}
	}
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
