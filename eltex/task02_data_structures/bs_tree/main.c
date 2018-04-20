#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

int main()
{
	struct t_bst_node *tree, *node;

	// Init the root
	tree = bst_create(666, "Satan");

	// Insert some stuff
	bst_insert(tree, 1337, "Leet");
	bst_insert(tree, 1488, "Adolf");
	bst_insert(tree, 228, "Nosik");

	// Print the tree
	bst_print(tree, 2);

	// Try to find something
	if ((node = bst_search(tree, 525)))
		printf("[%d] --- [%s]\n", node->key, node->value);
	else
		printf("Node not found.\n");

	if ((node = bst_search(tree, 666)))
		printf("[%d] --- [%s]\n", node->key, node->value);
	else
		printf("Node not found.\n");

	if ((node = bst_search(tree, 228)))
		printf("[%d] --- [%s]\n", node->key, node->value);
	else
		printf("Node not found.\n");

	// Delete nodes and check them for existence
	tree = bst_delete(tree, 999);
	tree = bst_delete(tree, 666);
//	tree = bst_delete(tree, 228);

	if ((node = bst_search(tree, 228)))
		printf("[%d] --- [%s]\n", node->key, node->value);
	else
		printf("Node not found.\n");

	if ((node = bst_search(tree, 666)))
		printf("[%d] --- [%s]\n", node->key, node->value);
	else
		printf("Node not found.\n");

	// Print the tree
	bst_print(tree, 2);

	// Destroy the tree :(
	bst_destroy(tree);

	return 0;
}
