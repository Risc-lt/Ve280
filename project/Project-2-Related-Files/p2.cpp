#include <iostream>
#include <cstdlib>
#include "p2.h"

using namespace std;

static list_t do_chop(list_t list, unsigned int n);
static int Min(int x, int y, int z);

int size(list_t list){
/*
// EFFECTS: Returns the number of elements in "list".
//          Returns zero if "list" is empty.
*/
    if(list_isEmpty(list)){
        return 0;
    } else{
        return 1 + size(list_rest(list));
    }
}


int sum(list_t list){
/*
// EFFECTS: Returns the sum of all elements in "list".
//          Returns zero if "list" is empty.
*/
    if(list_isEmpty(list)){
        return 0;
    } else{
        return list_first(list) + sum(list_rest(list));
    }
}


int product(list_t list){
/*
// EFFECTS: Returns the product of all elements in "list".
//          Returns one if "list" is empty.
*/
    if(list_isEmpty(list)){
        return 1;
    } else{
        return list_first(list) * product(list_rest(list));
    }
}


list_t reverse(list_t list){
/*
// EFFECTS: Returns the reverse of "list".
*/
    if(list_isEmpty(list)){
        return list_make();
    } else{
        return append(reverse(list_rest(list)), list_make(list_first(list), list_make()));
    }
}


list_t append(list_t first, list_t second){
/*
// EFFECTS: Returns the list (first second).
*/
    if(list_isEmpty(first)){
        return second;
    } else{
        return list_make(list_first(first), append(list_rest(first), second));
    }

}

list_t filter(list_t list, bool (*fn)(int)){
/*
// EFFECTS: Returns a list containing precisely the elements of "list"
//          for which the predicate fn() evaluates to true, in the
//          order in which they appeared in list.
*/
    if(list_isEmpty(list)){
        return list_make();
    } else{
        if(fn(list_first(list))){
            return list_make(list_first(list), filter(list_rest(list), fn));
        } else{
            return filter(list_rest(list), fn);
        }
    }
}


list_t insert_list(list_t first, list_t second, unsigned int n){
/*
// REQUIRES: n <= the number of elements in "first".
//
// EFFECTS: Returns a list comprising the first n elements of
//          "first", followed by all elements of "second",
//           followed by any remaining elements of "first".
*/
    if(n == 0){
        return append(second, first);
    } else{
        return list_make(list_first(first), insert_list(list_rest(first), second, n-1));
    }
}


list_t chop(list_t list, unsigned int n){
/*
// REQUIRES: "list" has at least n elements.
//
// EFFECTS: Returns the list equal to "list" without its last n
//          elements.
*/
    if(n == 0){
        return list;
    } else{
        list_t temp = reverse(list);
        return reverse(do_chop(temp, n));
    }

}

static list_t do_chop(list_t list, unsigned int n){
    if(list_isEmpty(list_rest(list)) && n != 0){
//        cout << "Error: list should have at least n elements\n";
        return list_make();
    }

    if(n == 0){
        return list;
    } else{
        return do_chop(list_rest(list), n-1);
    }
}


bool issorted_list(list_t list){
/*
// EFFECTS: Returns true if the "list" is ascending rted or empty,
//          false otherwise.
*/
    if(list_isEmpty(list)){
        return true;
    } else{
        if(list_isEmpty(list_rest(list))){
            return true;
        } else{
            if(list_first(list) <= list_first(list_rest(list))){
                return issorted_list(list_rest(list));
            } else{
                return false;
            }
        }
    }
}


//************************************************************
//*********                                     **************
//*********            BINARY TREE              **************
//*********                                     **************
//************************************************************

int tree_sum(tree_t tree){
/*
// EFFECTS: Returns the sum of all elements in "tree".
//          Returns zero if "tree" is empty.
*/
    if(tree_isEmpty(tree)){
        return 0;
    } else{
        return tree_elt(tree) + tree_sum(tree_left(tree)) + tree_sum(tree_right(tree));
    }
}

bool tree_search(tree_t tree, int key){
/*
// EFFECTS: Returns true if there exists any element in "tree"
//          whose value is "key". Otherwise, return "false".
*/
    if(tree_isEmpty(tree)){
        return false;
    } else{
        if(tree_elt(tree) == key){
            return true;
        } else{
            return tree_search(tree_left(tree), key) || tree_search(tree_right(tree), key);
        }
    }

}


int depth(tree_t tree){
/*
// EFFECTS: Returns the depth of "tree", which equals the number of
//          layers of nodes in the tree.
//          Returns zero if "tree" is empty.
*/
    if(tree_isEmpty(tree)){
        return 0;
    } else{
        int left_depth = depth(tree_left(tree));
        int right_depth = depth(tree_right(tree));
        return 1 + (left_depth > right_depth ? left_depth : right_depth);
    }
}


int tree_min(tree_t tree){
/*
// REQUIRES: "tree" is non-empty.
// EFFECTS: Returns the smallest element in "tree".
*/
    if(tree_isEmpty(tree)){
//        cout << "Error: tree is empty\n";
        return 0;
    } else{
        if(tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))){
            return tree_elt(tree);
        } else{
            return Min(tree_min(tree_left(tree)), tree_min(tree_left(tree)), tree_elt(tree));
        }
    }
}

static int Min(int x, int y, int z){
    if(x <= y && x <= z){
        return x;
    } else if(y <= x && y <= z){
        return y;
    } else{
        return z;
    }
}



list_t traversal(tree_t tree){
/*
// EFFECTS: Returns the elements of "tree" in a list using an
//          in-order traversal. An in-order traversal prints
//          the "left most" element first, then the second-left-most,
//          and so on, until the right-most element is printed.
*/
    if(tree_isEmpty(tree)){
        return list_make();
    } else{
        return append(append(traversal(tree_left(tree)), list_make(tree_elt(tree), list_make())), traversal(tree_right(tree)));
    }
}


bool tree_hasPathSum(tree_t tree, int sum){
/*
// EFFECTS: Returns true if and only if "tree" has at least one root-to-leaf
//          path such that adding all elements along the path equals "sum".
*/
    if(tree_isEmpty(tree)){
        return false;
    } else{
        if(tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))){
            return sum == tree_elt(tree);
        } else{
            return tree_hasPathSum(tree_left(tree), sum - tree_elt(tree)) || tree_hasPathSum(tree_right(tree), sum - tree_elt(tree));
        }
    }
}


bool covered_by(tree_t A, tree_t B){
/*
// EFFECTS: Returns true if tree A is covered by tree B.
*/
    if(tree_isEmpty(A)){
        return true;
    } else if(tree_isEmpty(B)){
        return false;
    } else{
        return tree_elt(A) == tree_elt(B) && covered_by(tree_left(A), tree_left(B)) && covered_by(tree_right(A), tree_right(B));
    }
}


bool contained_by(tree_t A, tree_t B){
/*
// EFFECTS: Returns true if tree A is covered by tree B
//          or a subtree of B.
*/
    if(tree_isEmpty(A)){
        return true;
    } else if(tree_isEmpty(B)){
        return false;
    } else{
        return covered_by(A, B) || contained_by(A, tree_left(B)) || contained_by(A, tree_right(B));
    }
}


tree_t insert_tree(int elt, tree_t tree){
/*
// REQUIRES: "tree" is a sorted binary tree.
//
// EFFECTS: Returns a new tree with elt inserted as a leaf such that
//          the resulting tree is also a sorted binary tree.
*/
    if(tree_isEmpty(tree)){
        return tree_make(elt, tree_make(), tree_make());
    } else{
        if(elt < tree_elt(tree)){
            return tree_make(tree_elt(tree), insert_tree(elt, tree_left(tree)), tree_right(tree));
        } else{
            return tree_make(tree_elt(tree), tree_left(tree), insert_tree(elt, tree_right(tree)));
        }
    }
}


bool issorted_tree(tree_t tree){
/*
// EFFECTS: returns true if the tree is sorted or empty,
//          false otherwise.
*/
    if(tree_isEmpty(tree)){
        return true;
    } else{
        if(tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))){
            return true;
        } else if(tree_isEmpty(tree_left(tree))){
            return tree_elt(tree) <= tree_elt(tree_right(tree)) && issorted_tree(tree_right(tree));
        } else if(tree_isEmpty(tree_right(tree))){
            return tree_elt(tree_left(tree)) <= tree_elt(tree) && issorted_tree(tree_left(tree));
        } else{
            return tree_elt(tree_left(tree)) <= tree_elt(tree) && tree_elt(tree) <= tree_elt(tree_right(tree)) && issorted_tree(tree_left(tree)) && issorted_tree(tree_right(tree));
        }
    }
}