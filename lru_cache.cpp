//
// Created by Mo Aboulmagd on 12/6/21.
//

/*
 * This problem was asked by Google.
 *
 * Implement an LRU (Least Recently Used) cache. It should be able to be initialized with a cache size n, and contain the following methods:

    set(key, value): sets key to value. If there are already n items in the cache and we are adding a new item,
    then it should also remove the least recently used item.
    get(key): gets the value at key. If no such key exists, return null.

 * Each operation should run in O(1) time.
 */

#include "include.h"

// Complexity Analysis:
// Time: O(1) for put and get
// Space: O(capacity)

struct DoublyLinkedListNode final {
public:
    explicit DoublyLinkedListNode(const int k, const int value) : key(k), val(value), next(nullptr), prev(nullptr) {}

    int key;
    int val;
    DoublyLinkedListNode* next;
    DoublyLinkedListNode* prev;
};

class LRUCache {
public:
    DoublyLinkedListNode* head_;
    DoublyLinkedListNode* tail_;
    int capacity_;
    unordered_map<int, DoublyLinkedListNode*> cache_;

    LRUCache(int capacity) : head_(nullptr), tail_(nullptr), capacity_(capacity) {
        cache_.reserve(capacity_);
    }

    ~LRUCache() {
        // TODO Delete DoublyLinkedList correctly
    }

    int get(int key) {
        if (cache_.find(key) == cache_.cend()) {
            return -1;
        }

        DoublyLinkedListNode* node = cache_.at(key);

        // If head_ == node, then we don't change our DLL, otherwise node is the new head_
        if (head_ != node) {
            if (tail_ == node) {
                tail_ = node->prev;
            }

            node->prev->next = node->next;
            if (node->next != nullptr) {
                node->next->prev = node->prev;
            }

            node->prev = nullptr;
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }

        return head_->val;
    }

    void put(int key, int value) {
        if (cache_.find(key) != cache_.cend()) {
            // Move node to the front of the list, and update its val
            DoublyLinkedListNode* node = cache_.at(key);

            if (head_ == node) {
                // Update node's value
                head_->val = value;
                return;
            }

            DoublyLinkedListNode* prev_node = node->prev;
            DoublyLinkedListNode* next_node = node->next;

            if (prev_node != nullptr) {
                prev_node->next = next_node;
            }
            if (next_node != nullptr) {
                next_node->prev = prev_node;
            }

            // Update tail if tail_ == node to prev_node
            if (tail_ == node) {
                if (prev_node != nullptr) {
                    tail_ = prev_node;
                }
            }

            node->prev = nullptr;
            node->next = nullptr;
            // Update head
            if (head_ != node) {
                node->next = head_;
                head_->prev = node;// head should NOT be null ever if we're here
            }
            head_ = node;

            // Update node's value
            head_->val = value;
        }

        else {
            if (cache_.size() == capacity_) {
                // Evict LRU key
                DoublyLinkedListNode* node_to_evict = tail_;
                cache_.erase(node_to_evict->key);

                if (head_ != node_to_evict) {
                    DoublyLinkedListNode* node_to_evict_prev = node_to_evict->prev;

                    tail_ = node_to_evict_prev;
                    node_to_evict_prev->next = nullptr;

                    node_to_evict->next = head_;
                    head_->prev = node_to_evict;

                    node_to_evict->prev = nullptr;
                    head_ = node_to_evict;
                }

                // Overwrite key/value
                head_->key = key;
                head_->val = value;
                cache_[key] = head_;
            }

            else {
                // Simply insert new node as head of DLL

                DoublyLinkedListNode* new_node = new DoublyLinkedListNode(key, value);

                if (head_ != nullptr) {
                    new_node->next = head_;
                    head_->prev = new_node;
                }
                else {
                    tail_ = new_node;
                }

                head_ = new_node;

                cache_[key] = new_node;
            }
        }
    }
};

// NOTE/TODO: It'd take me hours to write robust tests for this, so just test it on LeetCode for now
TEST(LRUCache, Capacity2Test) {
    // Test cache with capacity 2 first
    LRUCache lru_cache(2);

    ASSERT_EQ(lru_cache.capacity_, 2);
    ASSERT_EQ(lru_cache.cache_.bucket_count(), 2);

    lru_cache.put(1, 1);

    ASSERT_EQ(lru_cache.cache_.size(), 1);

    ASSERT_NE(lru_cache.head_, nullptr);
    ASSERT_EQ(lru_cache.head_->key, 1);
    ASSERT_EQ(lru_cache.head_->val, 1);

    ASSERT_EQ(lru_cache.head_->prev, nullptr);
    ASSERT_EQ(lru_cache.head_->next, nullptr);

    ASSERT_NE(lru_cache.tail_, nullptr);
    ASSERT_EQ(lru_cache.head_, lru_cache.tail_);

    lru_cache.put(2, 2);

    ASSERT_EQ(lru_cache.cache_.size(), 2);

    ASSERT_NE(lru_cache.head_, nullptr);
    ASSERT_EQ(lru_cache.head_->key, 2);
    ASSERT_EQ(lru_cache.head_->val, 2);

    ASSERT_EQ(lru_cache.head_->prev, nullptr);
    ASSERT_NE(lru_cache.head_->next, nullptr);
    ASSERT_EQ(lru_cache.head_->next, lru_cache.tail_);

    ASSERT_NE(lru_cache.tail_, nullptr);
    ASSERT_EQ(lru_cache.tail_->key, 1);
    ASSERT_EQ(lru_cache.tail_->val, 1);

    ASSERT_NE(lru_cache.tail_->prev, nullptr);
    ASSERT_EQ(lru_cache.tail_->prev, lru_cache.head_);
    ASSERT_EQ(lru_cache.tail_->next, nullptr);

    ASSERT_NE(lru_cache.head_, lru_cache.tail_);

    ASSERT_EQ(lru_cache.get(1), 1);

    ASSERT_NE(lru_cache.head_, nullptr);
    ASSERT_EQ(lru_cache.head_->key, 1);
    ASSERT_EQ(lru_cache.head_->val, 1);

    ASSERT_EQ(lru_cache.head_->prev, nullptr);
    ASSERT_NE(lru_cache.head_->next, nullptr);
    ASSERT_EQ(lru_cache.head_->next, lru_cache.tail_);

    ASSERT_NE(lru_cache.tail_, nullptr);
    ASSERT_EQ(lru_cache.tail_->key, 2);
    ASSERT_EQ(lru_cache.tail_->val, 2);

    ASSERT_NE(lru_cache.tail_->prev, nullptr);
    ASSERT_EQ(lru_cache.tail_->prev, lru_cache.head_);
    ASSERT_EQ(lru_cache.tail_->next, nullptr);

    ASSERT_NE(lru_cache.head_, lru_cache.tail_);
}