#ifndef __P2_H__
#define __P2_H__
#include "recursive.h"

int size(list_t list);
/*
// EFFECTS: Returns the number of elements in "list".
//          Returns zero if "list" is empty.
*/

int sum(list_t list);
/*
// EFFECTS: Returns the sum of all elements in "list".
//          Returns zero if "list" is empty.
*/

int product(list_t list);
/*
// EFFECTS: Returns the product of all elements in "list".
//          Returns one if "list" is empty.
*/

list_t reverse(list_t list);
/*
// EFFECTS: Returns the reverse of "list".
//
// For example: the reverse of ( 3 2 1 ) is ( 1 2 3 )
*/

list_t append(list_t first, list_t second);
/*
// EFFECTS: Returns the list (first second).
//
// For example: append(( 2 4 6 ), ( 1 3 )) gives
// the list ( 2 4 6 1 3 ).
*/

list_t filter(list_t list, bool (*fn)(int));
/*
// EFFECTS: Returns a list containing precisely the elements of "list"
//          for which the predicate fn() evaluates to true, in the
//          order in which they appeared in list.
//
// For example, if predicate bool odd(int a) returns true if a is odd,
// then the function filter(list, odd) has the same behavior as the
// function filter_odd(list).
*/

list_t insert_list(list_t first, list_t second, unsigned int n);
/*
// REQUIRES: n <= the number of elements in "first".
//
// EFFECTS: Returns a list comprising the first n elements of
//          "first", followed by all elements of "second",
//           followed by any remaining elements of "first".
//
//     For example: insert (( 1 2 3 ), ( 4 5 6 ), 2)
//            gives ( 1 2 4 5 6 3 ).
*/

list_t chop(list_t list, unsigned int n);
/*
// REQUIRES: "list" has at least n elements.
//
// EFFECTS: Returns the list equal to "list" without its last n
//          elements.
*/

bool issorted_list(list_t list);
/*
// EFFECTS: Returns true if the "list" is ascending sorted or empty,
//          false otherwise.
*/

//************************************************************
//*********                                     **************
//*********            BINARY TREE              **************
//*********                                     **************
//************************************************************

int tree_sum(tree_t tree);
/*
// EFFECTS: Returns the sum of all elements in "tree".
//          Returns zero if "tree" is empty.
*/

bool tree_search(tree_t tree, int key);
/*
// EFFECTS: Returns true if there exists any element in "tree"
//          whose value is "key". Otherwise, return "false".
*/

int depth(tree_t tree);
/*
// EFFECTS: Returns the depth of "tree", which equals the number of
//          layers of nodes in the tree.
//          Returns zero is "tree" is empty.
//
// For example, the tree
//
//                           4
//                         /   \
//                        /      \
//                       2        5
//                      / \      / \
//                         3        8
//                        / \      / \
//                       6   7
//                      / \ / \
//
// has depth 4.
// The element 4 is on the first layer.
// The elements 2 and 5 are on the second layer.
// The elements 3 and 8 are on the third layer.
// The elements 6 and 7 are on the fourth layer.
//
*/

int tree_min(tree_t tree);
/*
// REQUIRES: "tree" is non-empty.
// EFFECTS: Returns the smallest element in "tree".
*/

list_t traversal(tree_t tree);
/*
// EFFECTS: Returns the elements of "tree" in a list using an
//          in-order traversal. An in-order traversal prints
//          the "left most" element first, then the second-left-most,
//          and so on, until the right-most element is printed.
//
//          For any node, all the elements of its left subtree
//          are considered as on the left of that node and
//          all the elements of its right subtree are considered as
//          on the right of that node.
//
// For example, the tree:
//
//                           4
//                         /   \
//                        /      \
//                       2        5
//                      / \      / \
//                         3
//                        / \
//
// would return the list
//
//       ( 2 3 4 5 )
//
// An empty tree would print as:
//
//       ( )
//
*/

bool tree_hasPathSum(tree_t tree, int sum);
/*
// EFFECTS: Returns true if and only if "tree" has at least one root-to-leaf
//          path such that adding all elements along the path equals "sum".
//
// A root-to-leaf path is a sequence of elements in a tree starting
// with the root element and proceeding downward to a leaf (an element
// with no children).
//
// An empty tree has no root-to-leaf path.
//
// For example, the tree:
//
//                           4
//                         /   \
//                        /     \
//                       1       5
//                      / \     / \
//                     3   6
//                    / \ / \
//
// has three root-to-leaf paths: 4->1->3, 4->1->6 and 4->5.
// Given sum = 9, the path 4->5 has the sum 9, so the function
// should return true. If sum = 10, since no path has the sum 10,
// the function should return false.
//
*/

bool covered_by(tree_t A, tree_t B);
/*
// EFFECTS: Returns true if tree A is covered by tree B.
*/

bool contained_by(tree_t A, tree_t B);
/*
// EFFECTS: Returns true if tree A is covered by tree B
//          or a subtree of B.
*/

tree_t insert_tree(int elt, tree_t tree);
/*
// REQUIRES: "tree" is a sorted binary tree.
//
// EFFECTS: Returns a new tree with elt inserted as a leaf such that
//          the resulting tree is also a sorted binary tree.
//
// For example, inserting 1 into the tree:
//
//                           4
//                         /   \
//                        /      \
//                       2        5
//                      / \      / \
//                         3
//                        / \
//
// would yield
//                           4
//                         /   \
//                        /      \
//                       2        5
//                      / \      / \
//                     1   3
//                    / \ / \
//
*/

bool issorted_tree(tree_t tree);
/*
// EFFECTS: returns true if the tree is sorted or empty,
//          false otherwise.
*/

#endif /* __P2_H__ */
