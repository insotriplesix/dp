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

/* Nil node */
struct t_rbt_node nil_node = { BLACK, 0, NULL, NULL, NULL };
struct t_rbt_node *nil = &nil_node;

/* Node creation */
struct t_rbt_node *rbt_create(struct t_rbt_node *p, int k)
{
	struct t_rbt_node *node =
		(struct t_rbt_node *)malloc(sizeof(struct t_rbt_node));

	node->color = RED;
	node->key = k;
	node->parent = p;
	node->left = node->right = nil;

	return node;
}

/* Destroy the tree */
void rbt_destroy(struct t_rbt_node *node)
{
	if (node == nil) return;

	if (node->left != nil)
		rbt_destroy(node->left);

	if (node->right != nil)
		rbt_destroy(node->right);

	free(node);
}

/* Print tree */
void rbt_print(struct t_rbt_node *tree, int padding)
{
	int i;

	if (tree == nil) {
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
	while (node && node != nil && k != node->key) {
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

/* Transplant the node */
struct t_rbt_node *rbt_transplant(struct t_rbt_node *root,
	struct t_rbt_node *n1, struct t_rbt_node *n2)
{
	if (n1->parent == nil)
		root = n2;
	else if (n1 == n1->parent->left)
		n1->parent->left = n2;
	else
		n1->parent->right = n2;

	n2->parent = n1->parent;

	return root;
}

/* Tree left rotation */
struct t_rbt_node *rbt_left_rotate(struct t_rbt_node *root,
	struct t_rbt_node *p)
{
	// Set child node
	struct t_rbt_node *c = p->right;

	// Turn child's left subtree into its parent's right subtree
	p->right = c->left;

	// Bridge the child's left sublink
	if (c->left != nil)
		c->left->parent = p;

	// Link p's parent to the child
	if (c != nil)
		c->parent = p->parent;

	if (p->parent != nil) {
		// Bridge p's old parent's left/right child
		if (p == p->parent->left)
			p->parent->left = c;
		else
			p->parent->right = c;
	} else
		root = c;

	// Put p on child's left
	c->left = p;

	// Now p's parent is c
	if (p != nil)
		p->parent = c;

	return root;
}

/* Tree right rotation */
struct t_rbt_node *rbt_right_rotate(struct t_rbt_node *root,
	struct t_rbt_node *p)
{
	// Set child node
	struct t_rbt_node *c = p->left;

	// Turn child's right subtree into its parent's left subtree
	p->left = c->right;

	// Bridge the child's right sublink
	if (c->right != nil)
		c->right->parent = p;

	// Link p's parent to the child
	if (c != nil)
		c->parent = p->parent;

	if (p->parent != nil) {
		// Bridge p's old parent's left/right child
		if (p == p->parent->left)
			p->parent->left = c;
		else
			p->parent->right = c;
	} else
		root = c;

	// Put p on child's right
	c->right = p;

	// Now p's parent is c
	if (p != nil)
		p->parent = c;

	return root;
}

/* Insertion fixup */
struct t_rbt_node *rbt_insert_fixup(struct t_rbt_node *root,
	struct t_rbt_node *n)
{
	// Uncle node
	struct t_rbt_node *u;

	// Current node is red
	while (n != root && n->parent->color == RED) {
		// If true then the node is in the left side of the grandpa
		if (n->parent == n->parent->parent->left) {
			// Set the uncle node
			u = n->parent->parent->right;

			// Case 1: Uncle is red
			if (u->color == RED) {
				n->parent->color = BLACK;
				u->color = BLACK;
				n->parent->parent->color = RED;
				n = n->parent->parent;
			}
			// Case 2: Uncle is black (wusup nigga)
			else {
				if (n == n->parent->right) {
					n = n->parent;
					root = rbt_left_rotate(root, n);
				}
				// Case 3: Uncle is black
				n->parent->color = BLACK;
				n->parent->parent->color = RED;
				root = rbt_right_rotate(root, n->parent->parent);
			}
		}
		// Otherwise - the node is on the right
		else {
			// Set the uncle node
			u = n->parent->parent->left;

			// Case 4: Uncle is red
			if (u->color == RED) {
				n->parent->color = BLACK;
				u->color = BLACK;
				n->parent->parent->color = RED;
				n = n->parent->parent;
			}
			// Case 5: Uncle is black
			else {
				if (n == n->parent->left) {
					n = n->parent;
					root = rbt_right_rotate(root, n);
				}
				// Case 6: Uncle is black
				n->parent->color = BLACK;
				n->parent->parent->color = RED;
				root = rbt_left_rotate(root, n->parent->parent);
			}
		}
	}

	// Root is always black
	root->color = BLACK;

	return root;
}

/* Insertion func */
struct t_rbt_node *rbt_insert(struct t_rbt_node *root, int k)
{
	struct t_rbt_node *parent = nil, *node = root;

	// Get down the tree
	while (node && node != nil) {
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
	if (parent && parent != nil) {
		if (k < parent->key)
			parent->left = node;
		else
			parent->right = node;
	} else
		root = node;

	// Fix properties
	return rbt_insert_fixup(root, node);
}

/* Deletion fixup */
struct t_rbt_node *rbt_delete_fixup(struct t_rbt_node *root,
	struct t_rbt_node *node)
{
	// Sibling node
	struct t_rbt_node *w;

	// Current node is black
	while ((node != root) && (node->color == BLACK)) {
		// The node is on the left
		if (node == node->parent->left) {

			// Set the sibling node
			w = node->parent->right;

			// Case 1: Sibling is red
			if (w->color == RED) {
				w->color = BLACK;
				node->parent->color = RED;
				root = rbt_left_rotate(root, node->parent);
				w = node->parent->right;
			}

			// Case 2: Sibling is black, and both of w's children are black
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				node = node->parent;
			}
			// Case 3: Sibling is black, left child is red, right - black
			else if (w->right->color == BLACK) {
				w->left->color = BLACK;
				w->color = RED;
				root = rbt_right_rotate(root, w);
				w = node->parent->right;
			}

			// Case 4: Sibling is black and its right child is red
			w->color = node->parent->color;
			node->parent->color = BLACK;
			w->right->color = BLACK;
			root = rbt_left_rotate(root, node->parent);
			node = root;
		}
		// Otherwise - the node is on the right
		else {
			// Set the sibling node
			w = node->parent->left;

			// Case 1: Sibling is red
			if (w->color == RED) {
				w->color = BLACK;
				node->parent->color = RED;
				root = rbt_right_rotate(root, node->parent);
				w = node->parent->left;
			}

			// Case 2: Sibling is black, and both of w's children are black
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				node = node->parent;
			}
			// Case 3: Sibling is black, right child is red, left - black
			else if (w->left->color == BLACK) {
				w->right->color = BLACK;
				w->color = RED;
				root = rbt_left_rotate(root, w);
				w = node->parent->left;
			}

			// Case 4: Sibling is black and its left child is red
			w->color = node->parent->color;
			node->parent->color = BLACK;
			w->left->color = BLACK;
			root = rbt_right_rotate(root, node->parent);
			node = root;
		}

		// Color the node as black
		node->color = BLACK;
	}

	return root;
}

/* Deletion func */
struct t_rbt_node *rbt_delete(struct t_rbt_node *root, int k)
{
	struct t_rbt_node *y, *x;
	struct t_rbt_node *node = rbt_search(root, k);

	// Tree is empty or node is not in the tree
	if ((root == nil) || (node == nil))
		return NULL;

	// Set y as the ptr to the node which we want to remove
	y = node;

	// Save the original color of that node
	int y_orig_color = y->color;

	// If node has only one child the we just transplant the node
	// with its child x
	if (node->left == nil) {
		x = node->right;
		root = rbt_transplant(root, node, node->right);
	} else if (node->right == nil) {
		x = node->left;
		root = rbt_transplant(root, node, node->left);
	}
	// Otherwise, node has two children
	else {
		// Set y to node's successor
		y = rbt_min(node->right);

		// The color of y now might changed, save that
		y_orig_color = y->color;

		// x is the child of y
		x = y->right;

		// Store the original position of node
		if (y->parent == node)
			x->parent = y;
		else {
printf("succ1\n");
			root = rbt_transplant(root, y, y->right);
			y->right = node->right;
			y->right->parent = y;
		}
printf("succ2\n");
		// Transplant the node
		root = rbt_transplant(root, node, y);
		y->left = node->left;
		y->left->parent = y;
		y->color = node->color;
	}

	// If original color of the node that we removed was black,
	// then it could cause violations of the properties
	if (y_orig_color == BLACK)
		root = rbt_delete_fixup(root, x);

	return node;
}
