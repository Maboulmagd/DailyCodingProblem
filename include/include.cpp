//
// Created by Mo Aboulmagd on 10/17/21.
//

#include "include.h"

// NOTE This is recursive ... TODO Change to iterative
bool TreesEqual(const TreeNode* lhs, const TreeNode* rhs) {
    if (!lhs && !rhs) { return true; }
    else if (!lhs && rhs) { return false; }
    else if (lhs && !rhs) { return false; }
    return lhs->val == rhs->val && TreesEqual(lhs->left, rhs->left);
}

// Encodes a tree to a single string.
string serialize(TreeNode* root) {
    if (root == nullptr) {
        return "";
    }

    string s;

    queue<TreeNode*> q;
    q.push(root);

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

            if (curr_node->left) { q.push(curr_node->left); }
            else if (!curr_node->left) { q.push(nullptr); }

            if (curr_node->right) { q.push(curr_node->right); }
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
TreeNode* deserialize(string data) {
    // Remove all whitespace from input string first

    TreeNode* root = nullptr;

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
            TreeNode* new_node = new TreeNode(val);
            if (root == nullptr) {// This should only ever execute once, moving ownership to a "global" unique_ptr.
                root = new_node;
                q.push(root);
                continue;
            }
            q.push(new_node);

            TreeNode* curr_parent = q.front();
            if (curr_parent->left == nullptr && !seen_null) {
                curr_parent->left = new_node;
                seen_null = true;
            }
            else {
                curr_parent->right = new_node;

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