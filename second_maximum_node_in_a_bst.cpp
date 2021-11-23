//
// Created by Mo Aboulmagd on 11/20/21.
//

/*
 * This problem was asked by Dropbox.
 *
 * Given the root to a binary search tree, find the second largest node in the tree.
 */

#include "include.h"

// Complexity Analysis:
// Time: O(N)
// Space: O(N)

void HelperLeft(TreeNode* curr, TreeNode*& res) {
    if (curr == nullptr) {
        return;
    }

    if (curr->right == nullptr) {
        res = curr;// This has to be the second largest node in the left subtree
        return;
    }

    HelperLeft(curr->right, res);
}

void HelperRight(TreeNode* curr, TreeNode*& res) {
    if (curr == nullptr) {
        return;
    }

    if (curr->right == nullptr) {// curr is the rightmost (max) node
        if (curr->left != nullptr) {
            // Second max node is in the left subtree, so just get the maximum node in the left subtree at this point
            TreeNode* next = curr->left;
            while (next->right != nullptr) {
                next = next->right;
            }
            res = next;
        }
        return;
    }

    HelperRight(curr->right, res);
    if (res == nullptr) {
        res = curr;
    }
}

TreeNode* SecondMaximumNodeInBST(TreeNode* root) {
    TreeNode* res = nullptr;

    if (root->right == nullptr) {// Then the second max node is the rightmost node in the left subtree
        HelperLeft(root->left, res);
        if (res == nullptr) {
            res = root->left;
        }
    }
    else {// Then the second max node is the parent of the rightmost node in the right subtree
        HelperRight(root->right, res);
        if (res == nullptr) {
            res = root;
        }
    }

    return res;
}

class SecondMaximumNodeInBSTTest : public ::testing::Test {
protected:
    explicit SecondMaximumNodeInBSTTest() {
        // [3,1,4,null,2]
        TreeNode* root = new TreeNode(3);
        root->left = new TreeNode(1);
        root->right = new TreeNode(4);
        root->left->right = new TreeNode(2);

        trees_.push_back(root);

        //[5,3,6,2,4,null,null,1]
        TreeNode* root2 = new TreeNode(5);
        root2->left = new TreeNode(3);
        root2->right = new TreeNode(6);
        root2->left->left = new TreeNode(2);
        root2->left->right = new TreeNode(4);
        root2->left->left->left = new TreeNode(1);

        trees_.push_back(root2);

        //[2,1,3]
        TreeNode* root3 = new TreeNode(2);
        root3->left = new TreeNode(1);
        root3->right = new TreeNode(3);

        trees_.push_back(root3);

        //[3,2,null,1]
        TreeNode* root4 = new TreeNode(3);
        root4->left = new TreeNode(2);
        root4->left->left = new TreeNode(1);

        trees_.push_back(root4);

        //[3,1,null,null,2]
        TreeNode* root5 = new TreeNode(3);
        root5->left = new TreeNode(1);
        root5->left->right = new TreeNode(2);

        trees_.push_back(root5);

        //[1,null,3,2]
        TreeNode* root6 = new TreeNode(1);
        root6->right = new TreeNode(3);
        root6->right->left = new TreeNode(2);

        trees_.push_back(root6);

        //[5,null,8,6,13]
        TreeNode* root7 = new TreeNode(5);
        root7->right = new TreeNode(8);
        root7->right->left = new TreeNode(6);
        root7->right->right = new TreeNode(13);

        trees_.push_back(root7);

        //[3,null,8,6,null,4,7]
        TreeNode* root8 = new TreeNode(3);
        root8->right = new TreeNode(8);
        root8->right->left = new TreeNode(6);
        root8->right->left->left = new TreeNode(4);
        root8->right->left->right = new TreeNode(7);

        trees_.push_back(root8);

        //[3,null,8,6,13,4,7,9,16]
        TreeNode* root9 = new TreeNode(3);
        root9->right = new TreeNode(8);
        root9->right->left = new TreeNode(6);
        root9->right->right = new TreeNode(13);
        root9->right->left->left = new TreeNode(4);
        root9->right->left->right = new TreeNode(7);
        root9->right->right->left = new TreeNode(9);
        root9->right->right->right = new TreeNode(16);

        trees_.push_back(root9);
    }

    ~SecondMaximumNodeInBSTTest() {
        // TODO Delete trees correctly!


    }

    vector<TreeNode*> trees_;
};

TEST_F(SecondMaximumNodeInBSTTest, Tests) {
    // Second max node is the root of the tree
    ASSERT_THAT(SecondMaximumNodeInBST(trees_[0]), trees_[0]);
    ASSERT_THAT(SecondMaximumNodeInBST(trees_[1]), trees_[1]);
    ASSERT_THAT(SecondMaximumNodeInBST(trees_[2]), trees_[2]);

    // Second max node is in left subtree
    ASSERT_THAT(SecondMaximumNodeInBST(trees_[3]), trees_[3]->left);
    ASSERT_THAT(SecondMaximumNodeInBST(trees_[4]), trees_[4]->left->right);

    // Second max node is in right subtree
    ASSERT_THAT(SecondMaximumNodeInBST(trees_[5]), trees_[5]->right->left);
    ASSERT_THAT(SecondMaximumNodeInBST(trees_[6]), trees_[6]->right);
    ASSERT_THAT(SecondMaximumNodeInBST(trees_[7]), trees_[7]->right->left->right);
    ASSERT_THAT(SecondMaximumNodeInBST(trees_[8]), trees_[8]->right->right);
}