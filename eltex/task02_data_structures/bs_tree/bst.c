#include <stdio.h>
#include <stdlib.h>

/* Binary Search Tree node entity */
struct t_bst_node {
	int key;
	char *value;

	struct t_bst_node *left;
	struct t_bst_node *right;
};

/* Node creation */
struct t_bst_node *bst_create(int k, char *v)
{
	struct t_bst_node *node =
		(struct t_bst_node *)malloc(sizeof(struct t_bst_node));

	if (node) {
		node->key = k;
		node->value = v;
		node->left = node->right = NULL;
	} else
		fprintf(stderr, "Allocation error in 'bst_create()'\n");

	return node;
}

/* Destroy the tree */
void bst_destroy(struct t_bst_node *node)
{
	if (node) {
		bst_destroy(node->left);
		free(node);
		bst_destroy(node->right);
	}
}

/* Print tree*/
void bst_print(struct t_bst_node *node, int padding)
{
	int i;

	if (!node) {
		for (i = 0; i < padding; i++) putchar('\t');
		puts("\n");
	} else {
		bst_print(node->right, padding + 1);

		for (i = 0; i < padding; i++) putchar('\t');
		printf("(%s)", node->value);

		bst_print(node->left, padding + 1);
	}
}

/* Search func */
struct t_bst_node *bst_search(struct t_bst_node *node, int k)
{
	while (node && k != node->key) {
		if (k < node->key)
			node = node->left;
		else
			node = node->right;
	}

	return node;
}

/* Find min value in the tree */
struct t_bst_node *bst_min(struct t_bst_node *node)
{
	while (node && node->left)
		node = node->left;

	return node;
}

/* Find max value in the tree */
struct t_bst_node *bst_max(struct t_bst_node *node)
{
	while (node && node->right)
		node = node->right;

	return node;
}

/* Insertion func */
void bst_insert(struct t_bst_node *root, int k, char *v)
{
	struct t_bst_node *parent, *node = root;

	// Nothing to insert
	if (!node || k == node->key)
		return;

	// Find a leaf where we place the new node
	while (node) {
		parent = node;
		if (k < node->key)
			node = node->left;
		else
			node = node->right;
	}

	// Create the node
	node = bst_create(k, v);

	// Link it to his parent
	if (k < parent->key)
		parent->left = node;
	else
		parent->right = node;

	return;
}

/* Deletion func */
struct t_bst_node *bst_delete(struct t_bst_node *root, int k)
{
	struct t_bst_node *parent = NULL, *node = root;

	// Find a leaf where we place the new node
	while (node) {
		if (k < node->key) {
			parent = node;
			node = node->left;
		} else if (k > node->key) {
			parent = node;
			node = node->right;
		} else break;
	}

	// Nothing to delete
	if (!node) return root;

	// Case 1: Node has only right subtree
	if (!node->left) {
		if (!parent)
			root = node->right;
		else if (parent->left == node)
			parent->left = node->right;
		else
			parent->right = node->right;

		free(node);
	}
	// Case 2: Node has only left subtree
	else if (!node->right) {
		if (!parent)
			root = node->left;
		else if (parent->left == node)
			parent->left = node->left;
		else
			parent->right = node->left;

		free(node);
	}
	// Case 3: Node has two subtrees
	else {
		// Case 3.1: Successor just straight in the right
		if ((bst_min(node->right)) == node->right) {

			struct t_bst_node *successor = node->right;
			successor->left = node->left;

			if (!parent)
				root = successor;
			else if (parent->left == node)
				parent->left = successor;
			else
				parent->right = successor;

			free(node);
		}
		// Case 3.2: Successor is somewhere else in the right subtree
		else {
			struct t_bst_node *succ_parent, *successor = node->right;

			// Find successor's parent
			while (successor->left) {
				succ_parent = successor;
				successor = successor->left;
			}

			if (!parent) {
				succ_parent->left = successor->right;
				successor->right = node->right;
				successor->left = node->left;
				root = successor;
			} else {
				succ_parent->left = successor->right;
				successor->right = node->right;
				successor->left = node->left;
			}

			free(node);
		}
	}

	return root;
}
