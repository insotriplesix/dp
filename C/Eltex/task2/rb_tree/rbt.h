#ifndef RB_TREE_H
#define RB_TREE_H

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
struct t_rb_node *create(struct t_rb_node *p, int k);

/* Insertion function */
struct t_rb_node *insert(struct t_rb_node *root, int k);

void _padding(char c, int n);
void _display(struct t_rb_node *tree, int depth);

#endif
