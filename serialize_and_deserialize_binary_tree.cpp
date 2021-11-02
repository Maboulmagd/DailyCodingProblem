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

// Encodes a tree to a single string.
string serialize(unique_ptr<TreeNode> root) {
    if (root == nullptr) {
        return "";
    }

    string s;

    queue<TreeNode*> q;
    q.push(root.get());

    while (!q.empty()) {
        // Think of this as a way to keep track of the current level we are on in the level-order traversal
        const int size = static_cast<int>(q.size());

        for (int i = 0; i < size; ++i) {
            const auto curr_node = q.front();
            q.pop();

            if (curr_node == nullptr) {
                s += "null,";
                continue;
            }

            // Serialize
            s += to_string(curr_node->val) + ",";

            if (curr_node->left) { q.push(curr_node->left.get()); }
            else if (!curr_node->left) { q.push(nullptr); }

            if (curr_node->right) { q.push(curr_node->right.get()); }
            else if (!curr_node->right) { q.push(nullptr); }
        }
    }

    s.pop_back(); // Erase last comma
    while (s.length() > 6 &&
          (s.substr(s.length() - 5) == ",null" || s.substr(s.length() - 5) == ",NULL")) {// Erase extra "null"s
        s.erase(s.length() - 5);
    }

    return s;
}

// Decodes your encoded data to tree.
unique_ptr<TreeNode> deserialize(string data) {
    // Remove all whitespace from input string first

    unique_ptr<TreeNode> root = nullptr;

    queue<TreeNode*> q;
    bool seen_null = false;

    const int len = static_cast<int>(data.length());
    for (int i = 0; i < len; ++i) {
        if (data[i] == '-' || (data[i] >= 48 && data[i] <= 57)) {// Current character is '-' OR a digit, so its part of a value of a node
            bool negate = false;
            if (data[i] == '-') {
                negate = true;
                ++i;
            }

            int val = 0;
            while (data[i] >= 48 && data[i] <= 57) {
                val *= 10;
                val += data[i] - '0';
                ++i;
            }
            if (negate) {
                val *= -1;
            }

            // Now we have the complete value, so we can create the new TreeNode
            unique_ptr<TreeNode> new_node = make_unique<TreeNode>(val);
            if (root == nullptr) {// This should only ever execute once, moving ownership to a "global" unique_ptr.
                root = move(new_node);
                q.push(root.get());
                continue;
            }
            q.push(new_node.get());

            TreeNode* curr_parent = q.front();
            if (curr_parent->left == nullptr && !seen_null) {
                curr_parent->left = move(new_node);
                seen_null = true;
            }
            else {
                curr_parent->right = move(new_node);

                // Now that both children have been set, we can safely discard the ptr to curr_parent
                q.pop();
                seen_null = false;
            }
        }

        else if (data.substr(i, 4) == "null" || data.substr(i, 4) == "NULL") {
            if (seen_null) {
                q.pop();
                seen_null = false;
            }

            else {
                seen_null = true;
            }

            i += 4;
        }
    }

    return root;
}

TEST(SerializeAndDeserializeTree, SerializeTests) {
    unique_ptr<TreeNode> root = make_unique<TreeNode>(1);
    root->left = make_unique<TreeNode>(2);
    root->right = make_unique<TreeNode>(3);
    root->right->left = make_unique<TreeNode>(4);
    root->right->right = make_unique<TreeNode>(5);

    ASSERT_THAT(serialize(move(root)), "1,2,3,null,null,4,5");

    //[1,-2,3,null,4,5,6,null,7,8,9]
    unique_ptr<TreeNode> root2 = make_unique<TreeNode>(1);
    root2->left = make_unique<TreeNode>(-2);
    root2->right = make_unique<TreeNode>(3);
    root2->left->right = make_unique<TreeNode>(4);
    root2->right->left = make_unique<TreeNode>(5);
    root2->right->right = make_unique<TreeNode>(6);
    root2->left->right->right = make_unique<TreeNode>(7);
    root2->right->left->left = make_unique<TreeNode>(8);
    root2->right->left->right = make_unique<TreeNode>(9);

    ASSERT_EQ(serialize(move(root2)), "1,-2,3,null,4,5,6,null,7,8,9");
}

TEST(SerializeAndDeserializeTree, DeserializeTests) {
    // [1,2,3,null,null,4,5]
    unique_ptr<TreeNode> root = make_unique<TreeNode>(1);
    root->left = make_unique<TreeNode>(2);
    root->right = make_unique<TreeNode>(3);
    root->right->left = make_unique<TreeNode>(4);
    root->right->right = make_unique<TreeNode>(5);

    ASSERT_EQ(deserialize("1,2,3,null,null,4,5"), root);

    //[1,-2,3,null,4,5,6,null,7,8,9]
    unique_ptr<TreeNode> root2 = make_unique<TreeNode>(1);
    root2->left = make_unique<TreeNode>(-2);
    root2->right = make_unique<TreeNode>(3);
    root2->left->right = make_unique<TreeNode>(4);
    root2->right->left = make_unique<TreeNode>(5);
    root2->right->right = make_unique<TreeNode>(6);
    root2->left->right->right = make_unique<TreeNode>(7);
    root2->right->left->left = make_unique<TreeNode>(8);
    root2->right->left->right = make_unique<TreeNode>(9);

    ASSERT_EQ(deserialize("1,-2,3,null,4,5,6,null,7,8,9"), root2);
}