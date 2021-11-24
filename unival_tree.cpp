//
// Created by Mo Aboulmagd on 10/23/21.
//

/*
 * This problem was asked by Google.
 * A unival tree (which stands for "universal value") is a tree where all nodes under it have the same value.
 * Given the root to a binary tree, count the number of unival subtrees.
 * For example, the following tree has 5 unival subtrees:

   0
  / \
 1   0
    / \
   1   0
  / \
 1   1
 */

#include "include.h"

// Complexity Analysis:
// Time: O(N) as we are iterating over every node in the tree once.
// Space: O(N) due to above reason, and hence we have N function calls on the stack.

bool IsUnivalTree(TreeNode* root) {
    if (!root) { return true; }// If we've made it to a null node, then all values we've encountered on the way must've been identical.
    if (root->left && root->left->val != root->val) { return false; }
    if (root->right && root->right->val != root->val) { return false; }

    return IsUnivalTree(root->left) && IsUnivalTree(root->right);
}

TEST(UnivalTree, IsUnivalTreeTests) {
    ASSERT_EQ(IsUnivalTree(deserialize("1,1,1,1,1,null,1")), true);
    ASSERT_EQ(IsUnivalTree(deserialize("2,2,2,5,2")), false);

    // Basic test from problem description
    ASSERT_EQ(IsUnivalTree(deserialize("0,1,0,null,null,1,0,1,1")), false);
}

// Complexity Analysis:
// Time: O(N) as we are iterating over every node in the tree once.
// Space: O(N) due to above reason, and hence we have N function calls on the stack.

bool CountUnivalTreeHelper(const TreeNode* node, int& count) {
    if (!node) { return true; }
    if (!node->left && !node->right) {// Leaf nodes are trivially unival trees.
        ++count;
        return true;
    }

    const bool left = CountUnivalTreeHelper(node->left, count);
    const bool right = CountUnivalTreeHelper(node->right, count);

    if (left && right) {
        const bool valid_left = (node->left && node->left->val == node->val) || (!node->left);
        const bool valid_right = (node->right && node->right->val == node->val) || (!node->right);

        if (valid_left && valid_right) {
            ++count;
            return true;
        }

        return false;
    }

    return false;
}

int CountUnivalTree(TreeNode* root) {
    int count = 0;
    CountUnivalTreeHelper(root, count);
    return count;
}

TEST(UnivalTree, CountUnivalTreeTests) {
    // TODO: We don't delete any of these trees!

    ASSERT_EQ(CountUnivalTree(deserialize("1,1,1,1,1,null,1")), 6);
    ASSERT_EQ(CountUnivalTree(deserialize("2,2,2,5,2")), 3);
    ASSERT_EQ(CountUnivalTree(deserialize("5,1,5,5,5,null,5")), 4);
    ASSERT_EQ(CountUnivalTree(deserialize("5,4,5,4,4,null,5")), 5);

    // Basic test from problem description
    ASSERT_EQ(CountUnivalTree(deserialize("0,1,0,null,null,1,0,1,1")), 5);
}