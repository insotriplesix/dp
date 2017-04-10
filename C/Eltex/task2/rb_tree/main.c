#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rbt.h"

int main(int argc, char **argv)
{
	srand((unsigned)time(NULL));

	int i;
	struct t_rbt_node *node, *tree = NULL;

	// Insert several random values
	for (i = 0; i < 5; i++) {
		int r = 11 + rand() % 88;
		tree = rbt_insert(tree, r);
		rbt_print(tree, 3);
		printf("Node with key %d added\n", r);
	}

	// Print the tree
	rbt_print(tree, 3);

	int k;
	printf("Let's search something! Input value: ");
	scanf("%d", &k);

	// Search some stuff
	if ((node = rbt_search(tree, k)))
		printf("The node (%2d) exists in the tree.\n", node->key);
	else
		printf("The node (%2d) doesn't exist in the tree!\n", k);

	// Destroy the tree :(
	rbt_destroy(tree);

	return 0;
}
