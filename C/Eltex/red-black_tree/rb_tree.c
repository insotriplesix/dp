#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

/* Red-black tree node entity */
struct t_rb_node {
	int color;
	int key;

	struct t_rb_node *parent;
	struct t_rb_node *left;
	struct t_rb_node *right;
};

/* Node creation */
struct t_rb_node *create(struct t_rb_node *p, int k)
{
	struct t_rb_node *node =
		(struct t_rb_node *)malloc(sizeof(struct t_rb_node));

	node->color = RED;
	node->key = k;
	node->parent = p;
	node->left = node->right = NULL;

	return node;
}

/* Insertion function */
struct t_rb_node *insert(struct t_rb_node *root, int k)
{
	if (root == NULL) return create(NULL, k);

	struct t_rb_node *node, *next, *parent;

	for (next = root; next != NULL; ) {
		// Next node is a parent node
		parent = next;

		// Look for a place to insert the node
		if (k < next->key)
			next = next->left;
		else if (k > next->key)
			next = next->right;
		else
			return root;
	}

	// Create the node
	node = create(parent, k);

	// Create the link between parent and his new child
	if (parent != NULL) {
		if (k < parent->key)
			parent->left = node;
		else
			parent->right = node;
	}

	return root;
}

void _padding(char c, int n)
{
	int i;
	for (i = 0; i < n; i++) putchar(c);
}

void _display(struct t_rb_node *tree, int depth)
{
	if (tree == NULL) {
		_padding('\t', depth);
		puts("\033[1;30mnil\033[0m");
	} else {
		_display(tree->right, depth + 1);
		_padding('\t', depth);
		if (tree->color == RED)
			printf("\033[1;31m(%2d)\033[0m\n", tree->key);
		else
			printf("\033[1;30m(%2d)\n\033[0m", tree->key);
		_display(tree->left, depth + 1);
	}
}
