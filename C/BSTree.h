#ifndef BSTREE_H
#define BSTREE_H
///////////////////////////////////////////
// Binary Search Tree without balancing. //
///////////////////////////////////////////
#include "data_types_config.h"

#include <stdbool.h>
#include "POD_Utils.h"
#include "Tree.h"

// TODO: Data structure value types should be defined only in <DS>.h
// Use Tree's data type
#ifndef BST_DATA_TYPE
#define BST_DATA_TYPE Tree_DATA_TYPE
#endif

// Reuse the parsing / free / copy / comparison helpers that are already defined for `Tree`.

// Typedef Tree structures for BST use
typedef Tree BST;
typedef TreeNode BSTNode;

#ifndef BST_PARSE_FUN
#define BST_PARSE_FUN Tree_PARSE_FUN
#endif
#ifndef BST_FREE_ELEMENT_FUN
#define BST_FREE_ELEMENT_FUN Tree_FREE_FUN
#endif
#ifndef BST_COPY_ELEMENT_FUN
#define BST_COPY_ELEMENT_FUN Tree_COPY_FUN
#endif
#ifndef BST_CMP_FUN
#define BST_CMP_FUN Tree_CMP_FUN
#endif

BST* BST_Create();
void BST_Free(BST* tree);
bool BST_insert(BST* tree, BST_DATA_TYPE value);
BSTNode* BST_find(BST* tree, BST_DATA_TYPE value);
bool BST_delete(BST* tree, BST_DATA_TYPE value);

#endif // BSTREE_H
