#ifndef AVLTREE_H
#define AVLTREE_H
#include "data_types_config.h"

#include "Tree.h"

// Inherit data type and operations from Tree
#define AVL_DATA_TYPE Tree_DATA_TYPE
#define AVL_PARSE_FUN Tree_PARSE_FUN
#define AVL_FREE_FUN Tree_FREE_FUN
#define AVL_COPY_FUN Tree_COPY_FUN
#define AVL_CMP_FUN Tree_CMP_FUN

// Use Tree types
typedef TreeNode AVLTreeNode;
typedef Tree AVLTree;

// Core operations
AVLTree* AVL_Create();
void AVL_Free(AVLTree* tree);
void AVL_Clear(AVLTree* tree);

// AVL-specific operations
void AVL_Insert(AVLTree* tree, AVL_DATA_TYPE data);
void AVL_Remove(AVLTree* tree, AVL_DATA_TYPE data);
AVL_DATA_TYPE* AVL_Find(AVLTree* tree, AVL_DATA_TYPE data);

#endif // AVLTREE_H
