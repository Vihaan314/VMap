# VMap
Implementation of map data structure in C++

<b>How it works</b>:
<br>
Implemented using a binary search tree, which consists of a tree of nodes, where each node consists of
its key, value and children nodes. In a binary search tree, the left child node is always less than its direct parent,
while the right child is always greater than the direct parent node. This comparison is done automatically for each type.
Observe that this means all keys of nodes in the left branch from the root node will be less than the key of the root node and the opposite for the
right branch.
This is an example visual of a BST: 
<br>

            5
          /   \
         2     9
              /
             7
Note the 7s position because it is greater than the 5 but less than the 9. 
<br><br>
<strong>Adding:</strong>
If we want to append the number 4, we traverse the binary tree while comparing keys. The most common way to traversing a binary tree is a DFS in-order traveral. The process looks like: 4 is less than the 5 (root) so we move to the left branch. Then the 4 is greater than the 2 so we move to the right sub-branch, and its right child is empty so that becomes 4. 

           5
         /   \
        2     9
         \   /
          4 7

Adding a few more nodes for demonstration yields:

           5
         /   \
        2     9
       / \   /
      1   4 7
         /
        3
<br>

<strong>Searching</strong>: 
<br>
Searching simply requires a traversal of the binary tree, which is one of ths strenghts and purposes of a binary tree because it is so efficient. There are many ways to traverse a binary tree such as a DFS, which includes an in-order, pre-order and post-order traveral, or an iterative / non recursive approach. In my implementation I used a binary search which is the most efficient as it leverages the comparisons between the keys to trace a direct path to the desired node. Suppose we use the tree from above and want to search for the value at key 4. The path that the search would take is: 

```5, 2, 4```

Because we can recursively halve branches based on the comparisons (< or >) resulting in an O(log(n)) time complexity.

<strong>Removing</strong>:

If we were to remove a key, for instance 2:
1) Search for key to remove - 2
2) Make that node's parent's left child be that node's right child } 
3) Make its sibling be the left child of that new right child       } The entry to remove is replaced with its successor                              
4) Remove node 2                                                   }
```
           5
         /   \
        /     9
       /     /
  1 - 4     7
```
5) Notice height balancing is off so we rebalance the heights
```
           5
         /   \
        4     9
       /     /
      1     7
```
Note: In my implementations of these functions I traverse the tree in different ways - some with recursion (in-order traveral) and some iteratively.
Most helper functions are for implementations that require recursion

Features:
* put - add entry to map
* get - retrieve value from key
* getKey - retrieves first instance of key with specified value
* remove - removes key from map
* getKeySet - returns std::vector of keys
* getValueSet - returns std::vector of values
* isEmpty - is the map empty
* size - size of map
* clear - removes all entries of the map
* printTree - visualize the binary search tree created with the keys (work in progress)
* << - print operator overload for displaying map
