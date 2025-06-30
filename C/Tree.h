#ifndef TREE_H
#define TREE_H

#include "data_types_config.h"
#include <stdlib.h>
#include <stdbool.h>
#include "POD_Utils.h"

// Data type and operations
#ifndef Tree_DATA_TYPE
#define Tree_DATA_TYPE int
#endif

#define Tree_PARSE_FUN CAT(Tree_DATA_TYPE, _Parse)
#define Tree_FREE_FUN CAT(Tree_DATA_TYPE, _Free)
#define Tree_COPY_FUN CAT(Tree_DATA_TYPE, _Copy)
#define Tree_CMP_FUN CAT(Tree_DATA_TYPE, _CMP)


// Tree node structure
typedef struct TreeNode {
	Tree_DATA_TYPE data;
	struct TreeNode* left;
	struct TreeNode* right;
	int height;  // Height field useful for all tree implementations
} TreeNode;

// Tree structure
typedef struct {
	TreeNode* root;
} Tree;

// Core operations
Tree* Tree_Create();
void Tree_Free(Tree* tree);
void Tree_Clear(Tree* tree);

// Node operations
TreeNode* TreeNode_Create(Tree_DATA_TYPE data);
void TreeNode_Free(TreeNode* node);
TreeNode* TreeNode_Copy(TreeNode* node);

// Utility functions
uint64_t Tree_Height(const Tree* tree);
uint64_t Tree_Size(const Tree* tree);
uint64_t Tree_NodeSize(const TreeNode* tree);
bool Tree_IsEmpty(const Tree* tree);

// Helper functions for AVL operations
TreeNode* Tree_rotate_left(TreeNode* node);
TreeNode* Tree_rotate_right(TreeNode* node);
int Tree_node_height(TreeNode* node);
int Tree_get_balance(TreeNode* node);

#endif // TREE_H 