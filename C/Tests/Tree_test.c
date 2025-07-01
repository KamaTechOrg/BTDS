#include "Tree_test.h"
#include "../DataStructures/Tree.h"
#include <string.h>

TEST_FUN_IMPL(TreeTest, CreateAndDestroy) {
    Tree* tree = Tree_Create();
    TEST_ASSERT(tree != NULL);
    TEST_ASSERT(tree->root == NULL);
    TEST_ASSERT(Tree_IsEmpty(tree));
    Tree_Free(tree);
} END_FUN

TEST_FUN_IMPL(TreeTest, NodeOperations) {
    Tree* tree = Tree_Create();
    TEST_ASSERT(tree != NULL);

    // Create and test root node
    TreeNode* root = TreeNode_Create(10);
    TEST_ASSERT(root != NULL);
    TEST_ASSERT(root->data == 10);
    TEST_ASSERT(root->left == NULL);
    TEST_ASSERT(root->right == NULL);
    tree->root = root;

    // Create and test child nodes
    TreeNode* left = TreeNode_Create(5);
    TreeNode* right = TreeNode_Create(15);
    root->left = left;
    root->right = right;

    TEST_ASSERT(root->left->data == 5);
    TEST_ASSERT(root->right->data == 15);

    Tree_Free(tree);
} END_FUN

TEST_FUN_IMPL(TreeTest, HeightAndSize) {
    Tree* tree = Tree_Create();
    TEST_ASSERT(tree != NULL);

    // Empty tree
    TEST_ASSERT(Tree_Height(tree) == 0);
    TEST_ASSERT(Tree_Size(tree) == 0);

    // Single node
    tree->root = TreeNode_Create(10);
    TEST_ASSERT(Tree_Height(tree) == 1);
    TEST_ASSERT(Tree_Size(tree) == 1);

    // Add children
    tree->root->left = TreeNode_Create(5);
    tree->root->right = TreeNode_Create(15);
    TEST_ASSERT(Tree_Height(tree) == 2);
    TEST_ASSERT(Tree_Size(tree) == 3);

    // Add one more level to left
    tree->root->left->left = TreeNode_Create(3);
    TEST_ASSERT(Tree_Height(tree) == 3);
    TEST_ASSERT(Tree_Size(tree) == 4);

    Tree_Free(tree);
} END_FUN

TEST_FUN_IMPL(TreeTest, Rotations) {
    Tree* tree = Tree_Create();
    TEST_ASSERT(tree != NULL);

    // Setup initial tree for right rotation
    tree->root = TreeNode_Create(30);
    tree->root->left = TreeNode_Create(20);
    tree->root->left->left = TreeNode_Create(10);

    // Perform right rotation
    tree->root = Tree_rotate_right(tree->root);
    TEST_ASSERT(tree->root->data == 20);
    TEST_ASSERT(tree->root->left->data == 10);
    TEST_ASSERT(tree->root->right->data == 30);

    // Setup for left rotation
    Tree_Free(tree);
    tree = Tree_Create();
    tree->root = TreeNode_Create(10);
    tree->root->right = TreeNode_Create(20);
    tree->root->right->right = TreeNode_Create(30);

    // Perform left rotation
    tree->root = Tree_rotate_left(tree->root);
    TEST_ASSERT(tree->root->data == 20);
    TEST_ASSERT(tree->root->left->data == 10);
    TEST_ASSERT(tree->root->right->data == 30);

    Tree_Free(tree);
} END_FUN

TEST_FUN_IMPL(TreeTest, BalanceFactor) {
    Tree* tree = Tree_Create();
    TEST_ASSERT(tree != NULL);

    // Empty tree
    TEST_ASSERT(Tree_get_balance(tree->root) == 0);

    // Single node
    tree->root = TreeNode_Create(10);
    TEST_ASSERT(Tree_get_balance(tree->root) == 0);

    // Left heavy
    tree->root->left = TreeNode_Create(5);
    TEST_ASSERT(Tree_get_balance(tree->root) == 1);

    // Balanced
    tree->root->right = TreeNode_Create(15);
    TEST_ASSERT(Tree_get_balance(tree->root) == 0);

    // Right heavy
    tree->root->right->right = TreeNode_Create(20);
    TEST_ASSERT(Tree_get_balance(tree->root) == -1);

    Tree_Free(tree);
} END_FUN

INIT_TEST_SUITE(TreeTest)
BIND_TEST(TreeTest, CreateAndDestroy)
BIND_TEST(TreeTest, NodeOperations)
BIND_TEST(TreeTest, HeightAndSize)
BIND_TEST(TreeTest, Rotations)
BIND_TEST(TreeTest, BalanceFactor)
END_INIT_TEST_SUITE(TreeTest) 