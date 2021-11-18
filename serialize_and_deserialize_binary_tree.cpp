//
// Created by Mo Aboulmagd on 10/18/21.
//

/*
 * This problem was asked by Google.
 * Given the root to a binary tree, implement serialize(root), which serializes the tree into a string, and deserialize(s),
 * which deserializes the string back into the tree.
 * For example, given the following Node class

class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
The following test should pass:

node = Node('root', Node('left', Node('left.left')), Node('right'))
assert deserialize(serialize(node)).left.left.val == 'left.left'
 */

#include "include.h"

/*
 * Key idea is to mimic how LeetCode serializes/deserializes binary trees.
 * The seen_null bool in the deserialize function is a way to keep track of when we should be popping the parent off of the queue.
 */

// Complexity Analysis:
// Time: O(N) for the serialize function, where N is however many nodes there would be in that tree, if it were complete.
//       O(N) for the deserialize function, where N is the length of the input string.
// Space: O(N) for the serialize function, since we use a queue, which will have N/2 nodes for the last level of the tree.
//        O(N) for the deserialize function, for the same reason as above.

class SerializeAndDeserializeTreeTest : public ::testing::Test {
protected:
    explicit SerializeAndDeserializeTreeTest() {
        // [1,2,3,null,null,4,5]
        TreeNode* root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        root->right->left = new TreeNode(4);
        root->right->right = new TreeNode(5);

        trees_.push_back(root);

        //[1,-2,3,null,4,5,6,null,7,8,9]
        TreeNode* root2 = new TreeNode(1);
        root2->left = new TreeNode(-2);
        root2->right = new TreeNode(3);
        root2->left->right = new TreeNode(4);
        root2->right->left = new TreeNode(5);
        root2->right->right = new TreeNode(6);
        root2->left->right->right = new TreeNode(7);
        root2->right->left->left = new TreeNode(8);
        root2->right->left->right = new TreeNode(9);

        trees_.push_back(root2);
    }

    ~SerializeAndDeserializeTreeTest() {
        // TODO Delete trees correctly!


    }

    vector<TreeNode*> trees_;
};

TEST_F(SerializeAndDeserializeTreeTest, SerializeTests) {
    ASSERT_EQ(serialize(trees_[0]), "1,2,3,null,null,4,5");
    ASSERT_EQ(serialize(trees_[1]), "1,-2,3,null,4,5,6,null,7,8,9");
}

TEST_F(SerializeAndDeserializeTreeTest, DeserializeTests) {
    ASSERT_TRUE(TreesEqual(deserialize("1,2,3,null,null,4,5"), trees_[0]));
    ASSERT_TRUE(TreesEqual(deserialize("1,-2,3,null,4,5,6,null,7,8,9"), trees_[1]));
}