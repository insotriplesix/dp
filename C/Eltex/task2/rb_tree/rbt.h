#ifndef RBT_H
#define RBT_H

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
struct t_rbt_node *rbt_create(struct t_rbt_node *p, int k);

/* Destroy the tree */
void rbt_destroy(struct t_rbt_node *node);

/* Print the tree */
void rbt_print(struct t_rbt_node *tree, int padding);

/* Search func */
struct t_rbt_node *rbt_search(struct t_rbt_node *node, int k);

/* Find min value in the tree */
struct t_rbt_node *rbt_min(struct t_rbt_node *node);

/* Find max value in the tree */
struct t_rbt_node *rbt_max(struct t_rbt_node *node);

/* Transplant the node */
struct t_rbt_node *rbt_transplant(struct t_rbt_node *root, struct t_rbt_node *n1,
	struct t_rbt_node *n2);

/* Tree left rotation */
struct t_rbt_node *rbt_left_rotate(struct t_rbt_node *root, struct t_rbt_node *p);

/* Tree right rotation */
struct t_rbt_node *rbt_right_rotate(struct t_rbt_node *root, struct t_rbt_node *p);

/* Insertion fixup func */
struct t_rbt_node *rbt_insert_fixup(struct t_rbt_node *root, struct t_rbt_node *n);

/* Insertion func */
struct t_rbt_node *rbt_insert(struct t_rbt_node *root, int k);

/* Deletion fixup func */
struct t_rbt_node *rbt_delete_fixup(struct t_rbt_node *root, struct t_rbt_node *n);

/* Deletion func */
struct t_rbt_node *rbt_delete(struct t_rbt_node *root, int k);


#endif
