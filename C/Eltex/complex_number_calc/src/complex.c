#include <stdio.h>
#include <math.h>

/* Complex number entity */
typedef struct {
	float x;	// Re z
	float y;	// Im z
} complex;

/* Addition */
complex c_add(complex a, complex b)
{
	complex c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return (c);
}

/* Substraction */
complex c_sub(complex a, complex b)
{
	complex c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return (c);
}

/* Multiplication */
complex c_mul(complex a, complex b)
{
	complex c;
	c.x = (a.x * b.x) - (a.y * b.y);
	c.y = (a.x * b.y) + (b.x * a.y);
	return (c);
}

/* Division */
complex c_div(complex a, complex b)
{
	complex c;
	c.x = (a.x * b.x + a.y * b.y) / (b.x * b.x + b.y * b.y);
	c.y = (b.x * a.y - a.x * b.y) / (b.x * b.x + b.y * b.y);
	return (c);
}

/*
 * z, a, b -> complex numbers
 * op      -> operation between them
 * d       -> detaied output
 */
void c_output(complex z, complex a, complex b, char op, int d)
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
