//
// Created by Mo Aboulmagd on 11/4/21.
//

/*
 * This problem was asked by Google.
 * Given two singly linked lists that intersect at some point, find the intersecting node. The lists are non-cyclical.
 * For example, given A = 3 -> 7 -> 8 -> 10 and B = 99 -> 1 -> 8 -> 10, return the node with value 8.
 * In this example, assume nodes with the same value are the exact same node objects.
 * Do this in O(M + N) time (where M and N are the lengths of the lists) and constant space.
 */

#include "include.h"

// Key idea is to figure out the lengths of both lists, and then if one list is longer than the other,
// then we need to move it until it is equal in length to the other list.
// Once we have that going, we can easily figure out the node that both lists intersect at.

// Complexity Analysis:
// Time: O(M + N), since in the worst case, we will iterate over the entire length of both lists.
// Space: O(1), since we are not using recursion or any containers.

int GetListLength(ListNode* node) {
    int list_length = 0;

    while (node) {
        ++list_length;
        node = node->next;
    }

    return list_length;
}

ListNode* GetIntersectionNode(ListNode* a, ListNode* b) {
    if (!a || !b) { return nullptr; }// If any or both pointers are null, return null

    ListNode* a_ptr = a;
    ListNode* b_ptr = b;

    int a_length = GetListLength(a_ptr);
    int b_length = GetListLength(b_ptr);

    // Reset both pointers
    a_ptr = a;
    b_ptr = b;

    while (a_length > b_length) {
        a_ptr = a_ptr->next;
        --a_length;
    }

    while (b_length > a_length) {
        b_ptr = b_ptr->next;
        --b_length;
    }

    while (a_ptr != b_ptr) {
        a_ptr = a_ptr->next;
        b_ptr = b_ptr->next;
    }

    return a_ptr;
}

class IntersectionOfTwoLinkedListsTest : public ::testing::Test {
protected:
    explicit IntersectionOfTwoLinkedListsTest() {
        // [4,1,8,4,5]
        ListNode* head = new ListNode(4);
        head->next = new ListNode(1);
        head->next->next = new ListNode(8);
        head->next->next->next = new ListNode(4);
        head->next->next->next->next = new ListNode(5);

        lists_a.push_back(move(head));

        // [5,6,1,8,4,5]
        head = new ListNode(5);
        head->next = new ListNode(6);
        head->next->next = new ListNode(1);
        head->next->next->next = lists_a[0]->next->next;

        lists_b.push_back(move(head));

        // [1,9,1,2,4]
        head = new ListNode(1);
        head->next = new ListNode(9);
        head->next->next = new ListNode(1);
        head->next->next->next = new ListNode(2);
        head->next->next->next->next = new ListNode(4);

        lists_a.push_back(move(head));

        // [3,2,4]
        head = new ListNode(3);
        head->next = lists_a[1]->next->next->next;

        lists_b.push_back(move(head));

        // [2,6,4]
        head = new ListNode(2);
        head->next = new ListNode(6);
        head->next->next = new ListNode(4);

        lists_a.push_back(move(head));

        // [1,5]
        head = new ListNode(1);
        head->next = new ListNode(5);

        lists_b.push_back(move(head));

        // [3,7,8,10]
        head = new ListNode(3);
        head->next = new ListNode(7);
        head->next->next = new ListNode(8);
        head->next->next->next = new ListNode(10);

        lists_a.push_back(move(head));

        // [99,1,8,10]
        head = new ListNode(99);
        head->next = new ListNode(1);
        head->next->next = lists_a[3]->next->next;

        lists_b.push_back(move(head));
    }

    ~IntersectionOfTwoLinkedListsTest() {
        for (ListNode* list : lists_a) {
            DeleteList(list);
        }

        // Disconnecting lists
        lists_b[0]->next->next->next = nullptr;
        lists_b[1]->next = nullptr;
        lists_b[3]->next->next = nullptr;

        for (ListNode* list : lists_b) {
            DeleteList(list);
        }
    }

    vector<ListNode*> lists_a;
    vector<ListNode*> lists_b;
};

TEST_F(IntersectionOfTwoLinkedListsTest, BasicTests) {
    ASSERT_THAT(GetIntersectionNode(lists_a[0], lists_b[0]), lists_a[0]->next->next);
    ASSERT_THAT(GetIntersectionNode(lists_a[1], lists_b[1]), lists_a[1]->next->next->next);
    ASSERT_THAT(GetIntersectionNode(lists_a[2], lists_b[2]), nullptr);

    // Basic test from problem description
    ASSERT_THAT(GetIntersectionNode(lists_a[3], lists_b[3]), lists_a[3]->next->next);
}