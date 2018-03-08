/*
  File: bst.h
  Interface definition of the binary search tree data structure.
*/

#ifndef __BST_H
#define __BST_H

/* Defines the type to be stored in the data structure.  These macros
 * are for convenience to avoid having to search and replace/dup code
 * when you want to build a structure of doubles as opposed to ints
 * for example.
 */

# ifndef TYPE
# define TYPE      int
# endif


struct BSTree;
struct BSTreeIterator;
/* Declared in the c source file to hide the structure members from the user. */

/* Initialize binary search tree structure. */
struct BSTree *initBSTree();

/* Deallocate nodes in BST and deallocate the BST structure. */
void deleteBSTree(struct BSTree *tree);

/*-- BST interface --*/
bool  isEmptyBSTree(struct BSTree *tree);
int     sizeBSTree(struct BSTree *tree);

void     addBSTree(struct BSTree *tree, TYPE val);
bool containsBSTree(struct BSTree *tree, TYPE val);
void  removeBSTree(struct BSTree *tree, TYPE val);
void printBSTree(struct BSTree *tree);

struct BSTreeIterator* BSTIteratorCreate(struct BSTree* bst);
void BSTIteratorFree(struct BSTreeIterator* iter);
int BSTIteratorHasNext(struct BSTreeIterator* iter);
int BSTIteratorNext(struct BSTreeIterator* iter);
# endif
