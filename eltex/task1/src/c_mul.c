/* Complex number entity */
typedef struct {
	float x;	// Re z
	float y;	// Im z
} complex;

/* Multiplication */
complex c_mul(complex a, complex b)
{
	complex c;
	c.x = (a.x * b.x) - (a.y * b.y);
	c.y = (a.x * b.y) + (b.x * a.y);
	return (c);
}
