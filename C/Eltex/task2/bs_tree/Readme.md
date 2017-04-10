# Binary Search Tree

### --- Descr --------------------------

A **binary search tree** (BST) is a **node based** binary tree data structure which has the following properties:
1. The left subtree of a node contains only nodes with keys less than the node’s key.
2. The right subtree of a node contains only nodes with keys greater than the node’s key.
3. Both the left and right subtrees must also be binary search trees.

### --- Func --------------------------

`bst_create()` - Creates a simple node and add it to the tree.

`bst_destroy()` - Deallocates the memory that was used by the tree.

`bst_print()` - Display the tree (root is the most left node of the print).

`bst_search()` - Search the node by a key.

`bst_min()` - Returns the node with minimum key.

`bst_max()` - Returns the node with maximum key.

`bst_insert()` - Insert the node into the tree.

`bst_delete()` - Remove the node from the tree.

### --- Refs --------------------------

[CLRS](http://ce.bonabu.ac.ir/uploads/30/CMS/user/file/115/EBook/Introduction.to.Algorithms.3rd.Edition.Sep.2010.pdf)
