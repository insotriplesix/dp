#ifndef COMPLEX_H
#define COMPLEX_H

/* Complex number entity */
typedef struct {
	float x;	// Re z
	float y;	// Im z
} complex;

/* Addition */
complex c_add(complex a, complex b);

/* Substraction */
complex c_sub(complex a, complex b);

/* Multiplication */
complex c_mul(complex a, complex b);

/* Division */
complex c_div(complex a, complex b);

/* Print result */
void c_output(complex z, complex a, complex b, char op, int d);

#endif
