#ifndef BST_H
#define BST_H

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
struct t_bst_node *bst_create(int k, char *v);

/* Destroy the tree*/
void bst_destroy(struct t_bst_node *node);

/* Print tree */
void bst_print(struct t_bst_node *node, int padding);

/* Search func */
struct t_bst_node *bst_search(struct t_bst_node *node, int k);

/* Find min value in the tree */
struct t_bst_node *bst_min(struct t_bst_node *node);

/* Find max value in the tree */
struct t_bst_node *bst_max(struct t_bst_node *node);

/* Insertion func */
void bst_insert(struct t_bst_node *root, int k, char *v);

/* Deletion func */
struct t_bst_node *bst_delete(struct t_bst_node *root, int k);

#endif
