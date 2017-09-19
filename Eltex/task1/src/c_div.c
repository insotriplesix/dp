/* Complex number entity */
typedef struct {
	float x;	// Re z
	float y;	// Im z
} complex;

/* Division */
complex c_div(complex a, complex b)
{
	complex c;
	c.x = (a.x * b.x + a.y * b.y) / (b.x * b.x + b.y * b.y);
	c.y = (b.x * a.y - a.x * b.y) / (b.x * b.x + b.y * b.y);
	return (c);
}
