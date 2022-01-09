//
// Created by Mo Aboulmagd on 12/21/21.
//

/*
 * This problem was asked by Google.
 *
 * Implement an LFU (Least Frequently Used) cache.
 *
 * It should be able to be initialized with a cache size n, and contain the following methods:
 * set(key, value): sets key to value. If there are already n items in the cache and we are adding a new item,
 * then it should also remove the least frequently used item. If there is a tie, then the least recently used key should be removed
 *
 * get(key): gets the value at key. If no such key exists, return null.
 *
 * Each operation should run in O(1) time.
 */

#include "include.h"

// Complexity Analysis:
// Time: O(1) for get and put
// Space: O(capacity)

struct DLLNode;

struct FreqNode final {
public:
    explicit FreqNode(const int freq_) : freq(freq_), next(nullptr), prev(nullptr), dll_head(nullptr), dll_tail(nullptr) {}

    int freq;
    FreqNode* next;
    FreqNode* prev;

    DLLNode* dll_head;
    DLLNode* dll_tail;
};

struct DLLNode final {
public:
    explicit DLLNode(const int k, const int value)
            : key(k), val(value), next{nullptr}, prev{nullptr}, freq_parent(nullptr) {}

    int key;
    int val;

    DLLNode* next;
    DLLNode* prev;

    FreqNode* freq_parent;
};

class LFUCache {
public:
    FreqNode* freqnode_head_;// This is the head of our freq node DLL
    FreqNode* freqnode_tail_;// This is the tail of our freq node DLL, we'll be inserting at the END of the freq list (unsorted)
    unordered_map<int, FreqNode*> freq_freqNode_;// freq to freqNode in the freq list

    int capacity_;
    unordered_map<int, DLLNode*> key_DLLNode_;// key to DLLNode
    int min_freq_;
    int min_freq_key_;

    explicit LFUCache(int capacity) : capacity_(capacity), min_freq_(1), min_freq_key_(-1) {
        freq_freqNode_.reserve(capacity);

        freqnode_head_ = new FreqNode(1);
        freqnode_tail_ = freqnode_head_;
        freq_freqNode_.insert( {1, freqnode_head_} );

        key_DLLNode_.reserve(capacity_);
    }

    ~LFUCache() {
        // TODO Delete DoublyLinkedLists correctly
    }

    int get(int key) {
        if (key_DLLNode_.find(key) == key_DLLNode_.cend()) {
            return -1;
        }

        DLLNode* dll_node = key_DLLNode_.at(key);
        assert(dll_node != nullptr);
        FreqNode* freqNode_parent = dll_node->freq_parent;
        const int original_freq = freqNode_parent->freq;
        assert(freqNode_parent != nullptr);

        RemoveDLLNode(freqNode_parent, dll_node);

        if (freq_freqNode_.find(original_freq + 1) == freq_freqNode_.cend()) {
            // Create new freq node and insert it at the tail of the freq list

            auto new_freqNode = new FreqNode(original_freq + 1);
            InsertFreqNode(new_freqNode);
        }

        assert(freq_freqNode_.find(original_freq + 1) != freq_freqNode_.cend());
        InsertDLLNode(freq_freqNode_.at(original_freq + 1), dll_node);

        if (min_freq_key_ == dll_node->key) {// Update min_freq_ and min_freq_key_ if need be
            if (freq_freqNode_.find(original_freq) != freq_freqNode_.cend() && freq_freqNode_.at(original_freq)->dll_tail != nullptr) {
                // Need to check if the entry exists and its dll_tail is NOT null,
                // because it is possible that we have nothing, if the freq is 1!
                min_freq_key_ = freq_freqNode_.at(original_freq)->dll_tail->key;
            }

            else {
                min_freq_ = dll_node->freq_parent->freq;
                min_freq_key_ = dll_node->freq_parent->dll_tail->key;
            }
        }

        return dll_node->val;
    }

    void put(int key, int value) {
        // Edge case, if capacity_ is <= 0
        if (capacity_ <= 0) {
            return;
        }

        if (key_DLLNode_.find(key) == key_DLLNode_.cend()) {// If key does NOT EXIST in our LRU cache

            if (key_DLLNode_.size() < capacity_) {
                // So we have a key that has not been seen before, and we have the capacity to add it without evicting the LFU key

                auto dll_node = new DLLNode(key, value);

                InsertDLLNode(freqnode_head_, dll_node);

                freq_freqNode_.insert( {1, freqnode_head_} );
            }

            else {
                // Evict LFU key, which is going to be the LAST node in the DLL list with min_freq_
                // and make a new DLLNode, and insert it into the DLL list with freq 1

                DLLNode* node = key_DLLNode_.at(min_freq_key_);
                assert(node != nullptr);
                assert(node->key == min_freq_key_);

                FreqNode* freqNode_parent = node->freq_parent;
                assert(freqNode_parent != nullptr);
                assert(freqNode_parent->freq == min_freq_);
                assert(freqNode_parent->dll_head != nullptr);
                assert(freqNode_parent->dll_tail == node);// Recall our DLL lists are MRU -> LRU, so LRU node SHOULD be the TAIL!

                RemoveDLLNode(freqNode_parent, node);
                assert(node->next == nullptr);
                assert(node->prev == nullptr);
                assert(node->freq_parent == nullptr);

                node->key = key;
                node->val = value;

                assert(freq_freqNode_.find(1) != freq_freqNode_.cend());
                assert(freqnode_head_ != nullptr);
                assert(freqnode_tail_ != nullptr);
                assert(freq_freqNode_.at(1) == freqnode_head_);

                InsertDLLNode(freqnode_head_, node);

                // Key observation: Update min freq (and key)...the incoming new key IS the new min_freq_key_ (with a frequency of 1)!
            }

            // Update min_freq_ and min_freq_key_
            min_freq_key_ = freqnode_head_->dll_tail->key;
            min_freq_ = 1;
        }

        else {
            // Key EXISTS in our cache, so just update its value
            // take it out of its current DLL list, and insert it into the higher freq DLL list

            DLLNode* node = key_DLLNode_.at(key);

            FreqNode* freq_parent = node->freq_parent;
            const int original_freq = freq_parent->freq;

            RemoveDLLNode(freq_parent, node);

            if (freq_freqNode_.find(original_freq + 1) == freq_freqNode_.cend()) {
                // Create new freq node and insert it at the tail of the freq list

                auto new_freqNode = new FreqNode(original_freq + 1);
                InsertFreqNode(new_freqNode);
            }

            assert(freq_freqNode_.find(original_freq + 1) != freq_freqNode_.cend());
            node->val = value;
            InsertDLLNode(freq_freqNode_.at(original_freq + 1), node);

            if (min_freq_key_ == node->key) {// Update min_freq_ and min_freq_key_ if need be
                if (freq_freqNode_.find(original_freq) != freq_freqNode_.cend() &&
                    freq_freqNode_.at(original_freq)->dll_tail != nullptr) {
                    // Need to check if the entry exists and its dll_tail is NOT null,
                    // because it is possible that we have nothing, if the freq is 1!
                    min_freq_key_ = freq_freqNode_.at(original_freq)->dll_tail->key;
                }

                else {
                    min_freq_ = node->freq_parent->freq;
                    min_freq_key_ = node->freq_parent->dll_tail->key;
                }
            }
        }
    }






private:
    void InsertDLLNode(FreqNode* freqNode_parent, DLLNode* dll_node_to_insert) {

        assert(dll_node_to_insert->prev == nullptr);
        assert(dll_node_to_insert->next == nullptr);
        assert(dll_node_to_insert->freq_parent == nullptr);

        DLLNode* dll_head = freqNode_parent->dll_head;
        if (dll_head == nullptr) {// dll_node_to_insert is going to be the head and tail of the DLL list
            freqNode_parent->dll_head = dll_node_to_insert;
            freqNode_parent->dll_tail = dll_node_to_insert;
        }

        else {// Just add dll_node_to_insert at the BEGINNING of the DLL list, so the list is MRU -> LRU
            dll_node_to_insert->next = dll_head;
            dll_node_to_insert->prev = nullptr;

            dll_head->prev = dll_node_to_insert;

            freqNode_parent->dll_head = dll_node_to_insert;// Set head of the DLL list to dll_node_to_insert
        }

        dll_node_to_insert->freq_parent = freqNode_parent;// Set freq parent of dll_node_to_insert

        key_DLLNode_.insert( {dll_node_to_insert->key, dll_node_to_insert} );
    }

    void RemoveDLLNode(FreqNode* freqNode_parent, DLLNode* dll_node_to_evict) {

        assert(freqNode_parent != nullptr);
        assert(dll_node_to_evict != nullptr);

        DLLNode* dll_head = freqNode_parent->dll_head;
        assert(dll_head != nullptr);

        if (dll_head == dll_node_to_evict) {// The new head is going to be the next node in the list (could be nullptr)
            DLLNode* next_node = dll_node_to_evict->next;// Could be null, if list is just 1 node

            if (next_node != nullptr) {
                next_node->prev = nullptr;
                freqNode_parent->dll_head = next_node;
            }

            else {
                freqNode_parent->dll_head = nullptr;
                freqNode_parent->dll_tail = nullptr;
            }
        }

        else {
            DLLNode* prev_node = dll_node_to_evict->prev;
            assert(prev_node != nullptr);

            DLLNode* next_node = dll_node_to_evict->next;// Could be null, if list is just 2 nodes

            if (next_node != nullptr) {
                next_node->prev = prev_node;
                prev_node->next = next_node;
            }

            else {
                prev_node->next = nullptr;
                freqNode_parent->dll_tail = prev_node;
                if (prev_node->prev == nullptr) {
                    freqNode_parent->dll_head = prev_node;
                }
            }
        }

        dll_node_to_evict->next = nullptr;
        dll_node_to_evict->prev = nullptr;
        dll_node_to_evict->freq_parent = nullptr;// We will correct for this when we insert the node in its new DLL list (with higher freq)
        key_DLLNode_.erase(dll_node_to_evict->key);

        if (freqNode_parent->dll_head == nullptr) {
            assert(freqNode_parent->dll_tail == nullptr);

            // Erase this freq node from the freq list
            if (freqNode_parent->freq > 1) {
                RemoveFreqNode(freqNode_parent);
                delete freqNode_parent;
            }
        }
    }

    void RemoveFreqNode(FreqNode* freqNode_to_remove) {

        assert(freqNode_to_remove != nullptr);
        assert(freqNode_to_remove->freq != 1);
        assert(freqNode_to_remove->dll_head == nullptr);
        assert(freqNode_to_remove->dll_tail == nullptr);

        FreqNode* freq_head = freqnode_head_;
        assert(freq_head != nullptr);

        // Our freqnode_head_ is always going to be the freqNode with freq 1...so the freq node that we are removing has to come after
        assert(freqNode_to_remove != freqnode_head_);
        assert(freqnode_head_ != freqnode_tail_);

        if (freqnode_tail_ == freqNode_to_remove) {// freqNode_to_remove is the last in the freq list
            freqNode_to_remove->prev->next = nullptr;

            freqnode_tail_ = freqNode_to_remove->prev;
        }

        else {// freqNode_to_remove is in the middle of the freq list, so head and tail of the freq list won't change
            freqNode_to_remove->prev->next = freqNode_to_remove->next;
            freqNode_to_remove->next->prev = freqNode_to_remove->prev;
        }

        freqNode_to_remove->prev = nullptr;
        freqNode_to_remove->next = nullptr;

        freq_freqNode_.erase(freqNode_to_remove->freq);
    }

    void InsertFreqNode(FreqNode* freq_node_to_insert) {

        assert(freq_node_to_insert != nullptr);
        assert(freq_node_to_insert->prev == nullptr);
        assert(freq_node_to_insert->next == nullptr);
        assert(freq_node_to_insert->dll_head == nullptr);
        assert(freq_node_to_insert->dll_tail == nullptr);

        freqnode_tail_->next = freq_node_to_insert;

        freq_node_to_insert->prev = freqnode_tail_;

        freqnode_tail_ = freq_node_to_insert;

        assert(freq_node_to_insert->next == nullptr);
        assert(freq_node_to_insert->dll_head == nullptr);
        assert(freq_node_to_insert->dll_tail == nullptr);

        freq_freqNode_.insert( {freq_node_to_insert->freq, freq_node_to_insert} );// if key not found, insert key
    }
};

// NOTE: It'd take me HOURS to write robust tests (with assertions and everything) for this, so just test it on LeetCode for now
TEST(LFUCache, Capacity2Test) {
    LFUCache lfu_cache(2);

    lfu_cache.put(1, 1);
    lfu_cache.put(2, 2);
    ASSERT_EQ(lfu_cache.get(1), 1);
    lfu_cache.put(3, 3);
    ASSERT_EQ(lfu_cache.get(2), -1);
    ASSERT_EQ(lfu_cache.get(3), 3);
    lfu_cache.put(4, 4);
    ASSERT_EQ(lfu_cache.get(1), -1);
    ASSERT_EQ(lfu_cache.get(3), 3);
    ASSERT_EQ(lfu_cache.get(4), 4);
}


TEST(LFUCache, Capacity3Test) {
    LFUCache lfu_cache(3);

    lfu_cache.put(1, 1);
    lfu_cache.put(2, 2);
    lfu_cache.put(3, 3);
    lfu_cache.put(4, 4);

    ASSERT_EQ(lfu_cache.get(4), 4);
    ASSERT_EQ(lfu_cache.get(3), 3);
    ASSERT_EQ(lfu_cache.get(2), 2);
    ASSERT_EQ(lfu_cache.get(1), -1);
}

