#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rb_tree.h"

int main(int argc, char **argv)
{
	srand((unsigned)time(NULL));

	int i;
	struct t_rb_node *tree = NULL;

	for (i = 0; i < 5; i++) {
		int r = 11 + rand() % 88;
		tree = insert(tree, r);
		printf("Node with key %d added\n", r);
	}

	_display(tree, 3);

	return 0;
}
