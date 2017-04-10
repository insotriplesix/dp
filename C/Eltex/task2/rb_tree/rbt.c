#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

/* Red-Black Tree node entity */
struct t_rbt_node {
	int color;
	int key;

	struct t_rbt_node *parent;
	struct t_rbt_node *left;
	struct t_rbt_node *right;
};

/* Node creation */
struct t_rbt_node *rbt_create(struct t_rbt_node *p, int k)
{
	struct t_rbt_node *node =
		(struct t_rbt_node *)malloc(sizeof(struct t_rbt_node));

	// If p = null then this node will be a root, root always black
	if (p) node->color = RED;
	else node->color = BLACK;

	node->key = k;
	node->parent = p;
	node->left = node->right = NULL;

	return node;
}

/* Destroy the tree */
void rbt_destroy(struct t_rbt_node *node)
{
	if (node) {
		rbt_destroy(node->left);
		free(node);
		rbt_destroy(node->right);
	}
}

/* Print tree */
void rbt_print(struct t_rbt_node *tree, int padding)
{
	int i;

	if (!tree) {
		for (i = 0; i < padding; i++) putchar('\t');
		puts("\033[1;30mnil\033[0m");
	} else {
		rbt_print(tree->right, padding + 1);

		for (i = 0; i < padding; i++) putchar('\t');
		if (tree->color == RED)
			printf("\033[1;31m(%2d)\033[0m\n", tree->key);
		else
			printf("\033[1;30m(%2d)\n\033[0m", tree->key);

		rbt_print(tree->left, padding + 1);
	}
}

/* Search func */
struct t_rbt_node *rbt_search(struct t_rbt_node *node, int k)
{
	while (node && k != node->key) {
		if (k < node->key)
			node = node->left;
		else
			node = node->right;
	}

	return node;
}

/* Find min key in the tree */
struct t_rbt_node *rbt_min(struct t_rbt_node *node)
{
	while (node && node->left)
		node = node->left;

	return node;
}

/* Find min key in the tree */
struct t_rbt_node *rbt_max(struct t_rbt_node *node)
{
	while (node && node->right)
		node = node->right;

	return node;
}

/* Tree left rotation */
struct t_rbt_node *rbt_left_rotate(struct t_rbt_node *root, struct t_rbt_node *p)
{
	// Set child node
	struct t_rbt_node *c = p->right;

	// Turn child's left subtree into its parent's right subtree
	p->right = c->left;

	// Bridge the child's left sublink
	if (c->left)
		c->left->parent = p;

	// Link p's parent to the child
	c->parent = p->parent;

	if (!p->parent)
		root = c;
	// Bridge p's old parent's left/right child
	else if (p->key == p->parent->left->key)
		p->parent->left = c;
	else
		p->parent->right = c;

	// Put p on child's left
	c->left = p;

	// Now p's parent is c
	p->parent = c;

	return root;
}

/* Tree right rotation */
struct t_rbt_node *rbt_right_rotate(struct t_rbt_node *root, struct t_rbt_node *p)
{
	// Set child node
	struct t_rbt_node *c = p->left;

	// Turn child's right subtree into its parent's left subtree
	p->left = c->right;

	// Bridge the child's right sublink
	if (c->right)
		c->right->parent = p;

	// Link p's parent to the child
	c->parent = p->parent;

	if (!p->parent)
		root = c;
	// Bridge p's old parent's left/right child
	else if (p->key == p->parent->left->key)
		p->parent->left = c;
	else
		p->parent->right = c;

	// Put p on child's right
	c->right = p;

	// Now p's parent is c
	p->parent = c;

	return root;
}

/* Insertion fixup */
struct t_rbt_node *rbt_insert_fixup(struct t_rbt_node *root, struct t_rbt_node *n)
{
	struct t_rbt_node *u;

	// Current node is red
	while (n->parent->color == RED) {
		// If true then the node is in the left side of the grandparent
		if (n->parent == n->parent->parent->left) {
			// Set the uncle node
			u = n->parent->parent->right;	// >>>>>> ERROR IS HERE

			// Case 1: Uncle is red
			if (u->color == RED) {
				n->parent->color = BLACK;
				u->color = BLACK;
				n->parent->parent->color = RED;
				n = n->parent->parent;
			}
			// Case 2: Uncle is black (wusup nigga)
			else if (n == n->parent->right) {
				n = n->parent;
				root = rbt_left_rotate(root, n);
			}
			// Case 3: Uncle is black
			n->parent->color = BLACK;
			n->parent->parent->color = RED;
			root = rbt_right_rotate(root, n->parent->parent);
		}
		// Otherwise - the node is on the right
		else {
			// Set the uncle node
			u = n->parent->parent->left;	// >>>>>> ERROR IS HERE

			// Case 4: Uncle is red
			if (u->color == RED) {
				n->parent->color = BLACK;
				u->color = BLACK;
				n->parent->parent->color = RED;
				n = n->parent->parent;
			}
			// Case 5: Uncle is black
			else if (n == n->parent->left) {
				n = n->parent;
				root = rbt_right_rotate(root, n);
			}
			// Case 6: Uncle is black
			n->parent->color = BLACK;
			n->parent->parent->color = RED;
			root = rbt_left_rotate(root, n->parent->parent);
		}
	}

	// Root is always black
	root->color = BLACK;

	return root;
}

/* Insertion func */
struct t_rbt_node *rbt_insert(struct t_rbt_node *root, int k)
{
	struct t_rbt_node *parent, *node = root;

	// New node is the root
	if (!root)
		return rbt_create(root, k);

	while (node) {
		// Next node is a parent node
		parent = node;

		// Look for a place to insert the node
		if (k < node->key)
			node = node->left;
		else if (k > node->key)
			node = node->right;
		// That node already exists, nothing todo
		else
			return root;
	}

	// Create the node
	node = rbt_create(parent, k);

	// Create the link between parent and his new child
	if (parent) {
		if (k < parent->key)
			parent->left = node;
		else
			parent->right = node;
	}

//	return rbt_insert_fixup(root, node);
	return root;
}

/* Deletion func */
