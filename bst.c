/*
  File: bst.c
  Implementation of the binary search tree data structure.
 
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "linkedListStack.h"
#include "bst.h"


struct Node {
    TYPE         val;
    struct Node *left;
    struct Node *right;
};

struct BSTree {
    struct Node *root;
    int          cnt;
};


/*
 * This is the structure you will use to create an in-order BST iterator.  It
 * is up to you how to define this structure.
 */

struct BSTreeIterator {
    struct Node *current;
    struct LinkedList *stack;
};
/* FIXME: Define an iterator for a binary search tree; */


struct Node *_initNode(TYPE val)
{
   struct Node *newNode;
   newNode = malloc(sizeof(struct Node));
   assert(newNode!=0);
   newNode->val = val;
   newNode->left = 0;
   newNode->right = 0;
   return newNode;
}

/*
  function to create a binary search tree.
  param: none
  pre: none
  post: tree->count = 0
  tree->root = 0;
*/

struct BSTree*  initBSTree()
{
    struct BSTree *tree = (struct BSTree *)malloc(sizeof(struct BSTree));
    assert(tree != 0);
    tree->cnt  = 0;
    tree->root = 0;
    return tree;
}

/*----------------------------------------------------------------------------*/
/*
  function to free the nodes of a binary search tree
  param: node  the root node of the tree to be freed
  pre: none
  post: node and all descendants are deallocated
*/

void _freeBST(struct Node *node)
{
    if (node != 0) {
		_freeBST(node->left);
		node->left = 0;
		_freeBST(node->right);
		node->right = 0;
		free(node);
    }
}

/*
  function to deallocate a dynamically allocated binary search tree
  param: tree   the binary search tree
  pre: tree != null;
  post: all nodes and the tree structure itself are deallocated.
*/
void deleteBSTree(struct BSTree *tree)
{
    _freeBST(tree->root);
    tree->root = 0;
    free(tree);
}

/*----------------------------------------------------------------------------*/
/*
  function to determine if  a binary search tree is empty.

  param: tree    the binary search tree
  pre:  tree is not null
*/
bool isEmptyBSTree(struct BSTree *tree) { return (tree->cnt == 0); }

/*
  function to determine the size of a binary search tree

  param: tree    the binary search tree
  pre:  tree is not null
*/
int sizeBSTree(struct BSTree *tree) { return tree->cnt; }

/*----------------------------------------------------------------------------*/
/*
  recursive helper function to add a node to the binary search tree.
  param:  cur	the current root node
  val	the value to be added to the binary search tree
  pre:	val is not null
*/
struct Node *_addNode(struct Node *node, TYPE val)
{

    if (node == NULL)
       return _initNode(val);
    if (node-> val < val)
        node->right = _addNode(node->right,val);
    if (node-> val > val)
        node->left = _addNode(node->left,val);
/* Assume no node added if it has the same value as an existing node */
    if (node->val == val)
        return node;

/* Returning node if no new node has been allocated, in order not to disrupt the tree */
    return node;
}

/*
  function to add a value to the binary search tree
  param: tree   the binary search tree
  val		the value to be added to the tree

  pre:	tree is not null
  val is not null
  pose:  tree size increased by 1
  tree now contains the value, val
*/
void addBSTree(struct BSTree *tree, TYPE val)
{
    tree->root = _addNode(tree->root, val);
    tree->cnt++;
}


/*
  function to determine if the binary search tree contains a particular element
  param:	tree	the binary search tree
  val		the value to search for in the tree
  pre:	tree is not null
  val is not null
  post:	none
  return true if val is in the tree, false if val is not in the tree
*/

/*----------------------------------------------------------------------------*/
bool containsBSTree(struct BSTree *tree, TYPE val)
{
   assert(tree!=0);
   struct Node *current;
   current = tree->root;
   while(current != 0)
   {
       if (val == current->val)
           return true;
       if(val < current->val)
           current = current -> left;
       if (val > current->val)
           current = current -> right;
   }
   return false;
}

/*
  helper function to find the right most child of a node
  return a pointer of the right most child of cur
  param: cur		the current node
  pre:	cur is not null
  post: none
*/

/*----------------------------------------------------------------------------*/
struct Node *_rightMost(struct Node *cur)
{
    /*FIXME: write this*/
  assert(cur != NULL);
  while (cur->right != NULL) {
    cur = cur->right;
  }
  return cur;
}


/*
  recursive helper function to remove the right most child of a node
  HINT: this function returns cur if its right child is NOT NULL. Otherwise,
  it returns the left child of cur and free cur.

  Note:  If you do this iteratively, the above hint does not apply.

  param: cur	the current node
  pre:	cur is not null
  post:	the right most child of cur is not in the tree
*/
/*----------------------------------------------------------------------------*/
struct Node *_removeRightMost(struct Node *cur)
{
    /*FIXME: write this*/
  if(cur->right == NULL)
  {
    struct Node *temp = cur->left;
    free(cur);
    return temp;
  } else {
    struct Node *rightMost = _rightMost(cur);
    cur->val = rightMost->val;
    
    return cur;
  }
}

/*
  recursive helper function to remove a node from the tree
  param:	cur	the current node
  val	the value to be removed from the tree
  pre:	val is in the tree
  cur is not null
  val is not null
  
  You should use _rightMost (of the left subtree) and _removeRightMost (of the left subtree) 
  to complete this function
*/
/*----------------------------------------------------------------------------*/
struct Node *_removeNode(struct Node *cur, TYPE val)
{
    /*FIXME: write this*/
  struct Node *root = cur;
  // while(cur->val != val)
  //  {
  //      if(val < cur->val)
  //          cur = cur->left;
  //      if (val > cur->val)
  //          cur = cur->right;
  //  }
  if(cur == NULL)
    return NULL;
  if (cur->val == val) {
    if(cur->right == NULL && cur->left == NULL) {
      free(cur);
    } else if (cur->right == NULL || cur->left == NULL) {

    } else {
      _removeRightMost(cur->left);
    }
  } else {
    if(val < cur->val)
      _removeNode(cur->left, val);
    if(val > cur->val)
      _removeNode(cur->right, val);
  }
   return root;
  }

/*
  function to remove a value from the binary search tree
  param: tree   the binary search tree
  val		the value to be removed from the tree
  pre:	tree is not null
  val is not null
  val is in the tree
  pose:	tree size is reduced by 1
*/
void removeBSTree(struct BSTree *tree, TYPE val)
{
/* Because we don't have a pointer to parent, removal has to start from the root as well */
    if (containsBSTree(tree, val)) {
	tree->root = _removeNode(tree->root, val);
	tree->cnt--;
    }
}

/*----------------------------------------------------------------------------*/

/* The following is used only for debugging, set to "#if 0" when used 
   in other applications */
#if 1

/*----------------------------------------------------------------------------*/
void printNode(struct Node *cur) {
    if (cur == 0)
	return;
/* In-order traversal of the binary search tree */
    printf("(");
    printNode(cur->left);	 
	printf("%d", cur->val);
    printNode(cur->right);
    printf(")");
}

void printBSTree(struct BSTree *tree) {
    if (tree == 0)
	return;	 
    printNode(tree->root);	 
	printf("\n");
}
/*----------------------------------------------------------------------------*/

#endif


/*
 * This function should allocate and initialize a new in-order BST iterator
 * given a specific BST over which to iterate.
 *
 * Params:
 *   bst - the BST over which to perform in-order iteration.  May not be NULL.
 *
 * Return:
 *   Should return a pointer to a new in-order BST iterator, initialized so
 *   that the first value returned by bst_iterator_next() is the first in-order
 *   value in bst (i.e. the leftmost value in the tree).
 */
struct BSTreeIterator* BSTIteratorCreate(struct BSTree* tree) {
/* FIXME: Complete this implementation */
  assert(tree != NULL)
  struct BSTreeIterator *iterator = malloc(sizeof(struct BSTreeIterator));
  iterator->current = tree->root;
  iterator->stack = createLinkedList();
  return iterator;
}

/*
 * This function should free all memory allocated to a BST iterator.
 *
 * Params:
 *   iter - the iterator whose memory is to be freed.  May not be NULL.
 */
void BSTIteratorFree(struct BSTreeIterator* iter) {
/* FIXME: Complete this implementation */
  assert(iter != NULL);
  deleteLinkedList(iter->stack);
  free(iter);
}


/*
 * This function should return 1 if there is at least one more node to visit
 * in the in-order iteration of the BST represented by a given iterator.  If
 * there are no more nodes to visit, it should return 0.
 *
 * Params:
 *   iter - the iterator to be checked for more values.  May not be NULL.
 */
int BSTIteratorHasNext(struct BSTreeIterator* iter) {
/* FIXME: Complete this implementation */
  assert(iter != NULL);
  if(iter->current == NULL && isEmptyLinkedList(iter->stack))
  {
    return 0;
  } else {
    return 1;
  }
}


/*
 * This function should return the next value in the in-order iteration of the
 * BST represented by a given iterator.
 *
 * Params:
 *   iter - the iterator whose next value is to be returned.  May not be NULL
 *     and must have at least one more value to be returned.
 */
int BSTIteratorNext(struct BSTreeIterator* iter) {
/* FIXME: Complete this implementation */
  assert(iter != NULL || !BSTIteratorHasNext(iter));
  int singleStep = 0;
  int nextVal = NULL;
  while(singleStep == 0) 
  {
    if(iter->current != NULL)
    {
      pushLinkedList(iter->stack, iter->current)
      iter->current = iter->current->left;
    } else {
      if(!isEmptyLinkedList(iter-stack))
      {
        iter->current = topLinkedList(iter->stack);
        popLinkedList(iter->stack);
        nextVal = iter->current->val;
        iter->current = iter->current->right;
        singleStep = 1;
      }
    }
  }
  return nextVal;
}


/************************************************************************************************************************
from here to the end of this file are a set of fucntions for testing the fucntions of the BST
***************************************************************************************************************************/
/*
  function to built a Binary Search Tree (BST) by adding numbers in this specific order
  
*/
struct BSTree *buildBSTree() {
    struct BSTree *tree	= initBSTree();		
		
    /*Create value of the type of data that you want to store*/
	
    /*add the values to BST*/
	/* This tree can be found in Slide 24 of the BST slides */
    addBSTree(tree, 50);
    addBSTree(tree, 25);
    addBSTree(tree, 75);
    addBSTree(tree, 35);
    addBSTree(tree, 20);
    addBSTree(tree, 60);
    addBSTree(tree, 65);
    addBSTree(tree, 45);
    addBSTree(tree, 30);
    addBSTree(tree, 85);
	addBSTree(tree, 80);
    
    return tree;
}

/*
  fucntion to test the right_Most_element 

*/
void testRightMost() {
    struct BSTree *tree = buildBSTree();
    
	printf("right most of root: %d\n", _rightMost(tree->root)->val);
    
    printf("right most of left of root: %d\n", _rightMost(tree->root->left)->val);
    
    printf("right most of right of left of root: %d", _rightMost(tree->root->left->right)->val);
    
    printf("right most of right of root: %d", _rightMost(tree->root->right)->val);

    printf("Deleting the BSTree...\n");
    deleteBSTree(tree);
    printf("Returning from testLeftMost().\n");

}

void testRemoveRightMost() {
    struct BSTree *tree = buildBSTree();
/*    struct Node *cur; */
    
    _removeRightMost(tree->root);
    printBSTree(tree);
    
    _removeRightMost(tree->root->right);
    printBSTree(tree);
	
    _removeRightMost(tree->root);
    printBSTree(tree);

    deleteBSTree(tree);
}

void testRemoveNode() {
    struct BSTree *tree = buildBSTree();
    struct Node *cur;

    _removeNode(tree->root, 20);
    printBSTree(tree);
	        
    _removeNode(tree->root, 35);
    printBSTree(tree);
	   
    _removeNode(tree->root, 75);
    printBSTree(tree);
        
    cur = _removeNode(tree->root, 50);
    if (!cur)
        tree->root = NULL;
    printBSTree(tree);
    deleteBSTree(tree);
}

void testIterator() {
    struct BSTree *tree = buildBSTree();
    struct BSTreeIterator* iter = BSTIteratorCreate(tree);
    printf("\n== BST contents (in order):");
    while (BSTIteratorHasNext(iter)) {
        int val = BSTIteratorNext(iter);
        printf(" %4d", val);
    }
    printf("\n");
	/* Result from not using the iterator */
    printf("Baseline comparison:\n");
	printBSTree(tree);
    BSTIteratorFree(iter);
	deleteBSTree(tree);
}

/*

  Main function for testing different functions of the Assignment #3.

*/

int main(int argc, char *argv[]){	
    testRightMost();
	
    printf("\n");
    testRemoveRightMost();
	
    printf("\n");
    testRemoveNode();
    printf("\n");
	
    testIterator();
	
    return 0;
}
