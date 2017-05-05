# Red-Black Tree

### --- Descr --------------------------

A **red-black tree** is a binary search tree with one extra bit of storage per node: its
**color**, which can be either RED or BLACK. By constraining the node colors on any
simple path from the root to a leaf, red-black trees ensure that no such path is more
than twice as long as any other, so that the tree is approximately **balanced**.

Each node of the tree now contains the attributes color, key, left, right, and p. If
a child or the parent of a node does not exist, the corresponding pointer attribute
of the node contains the value NIL. We shall regard these NILs as being pointers to
leaves (external nodes) of the binary search tree and the normal, key-bearing nodes
as being internal nodes of the tree.

A red-black tree is a binary tree that satisfies the following red-black **properties**:
1. Every node is either red or black.
2. The root is black.
3. Every leaf (NIL) is black.
4. If a node is red, then both its children are black.
5. For each node, all simple paths from the node to descendant leaves contain the
same number of black nodes.

### --- Func --------------------------

`rbt_create()` - Creates a simple node and add it to the tree.

`rbt_destroy()` - Deallocates the memory that was used by the tree.

`rbt_print()` - Display the tree (root is the most left node of the print).

`rbt_search()` - Search the node by a key.

`rbt_min()` - Returns the node with a minimum key.

`rbt_max()` - Returns the node with a maximum key.

`rbt_transplant()` - Transplant the node to another place.

`rbt_left_rotate()` - Left rotation.

`rbt_right_rotate()` - Right rotation.

`rbt_insert_fixup()` - Restores the Red-Black properties after insertion.

`rbt_insert()` - Insert the node into the tree.

`rbt_delete_fixup()` - Restores the Red-Black properties after deletion.

`rbt_delete()` - Delete the node from the tree.

### --- Refs --------------------------

[CLRS](http://www.realtechsupport.org/UB/SR/algorithms/Cormen_Algorithms_3rd.pdf)
[mkurnosov](http://www.mkurnosov.net/teaching/uploads/DSA/dsa-fall2015-lec2.pdf)
