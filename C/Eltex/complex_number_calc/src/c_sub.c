/* Complex number entity */
typedef struct {
	float x;	// Re z
	float y;	// Im z
} complex;

/* Substraction */
complex c_sub(complex a, complex b)
{
	complex c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return (c);
}
