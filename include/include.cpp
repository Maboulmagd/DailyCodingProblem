//
// Created by Mo Aboulmagd on 10/17/21.
//

#include "include.h"

// NOTE This is recursive ... TODO Change to iterative
bool operator==(const unique_ptr<TreeNode>& a, const unique_ptr<TreeNode>& b) {
    if (a == nullptr && b == nullptr) { return true; }
    else if (a == nullptr && b != nullptr) { return false; }
    else if (a != nullptr && b == nullptr) { return false; }
    return a->val == b->val && a->left == b->left && a->right == b->right;
}