//
// Created by motanel on 09.03.2023.
//

#ifndef PA_BTREE_H
#define PA_BTREE_H

#include <iostream>

// Degree means maximum number of keys stored in any node
template<unsigned int degree>
class BTree {
    class Node {
    public:
        // True if is leaf node, False if internal node
        bool is_leaf_node = false;
        // Number of keys currently stored in node
        int key_count = 0;
        // Keys themselves, stored in monotonically increasing order
        int key[degree] { };
        // Pointers to children
        Node* child[degree + 1] { nullptr };

        Node() = default;
        ~Node() = default;
    };
    // Every other node other than the root must have at least minimum_degree - 1 keys
    // Every internal node other than the root has at least minimum_degree children
    // Every node may contain at most 2 * minimum_degree - 1 keys
    const unsigned int minimum_degree = (degree + 1) / 2;
public:
    Node* root;
    BTree() {
        // Create root node
        Node* node = new Node;
        node->is_leaf_node = true;
        root = node;
    }

    // Searches and returns key. Node is missing satellite data.
    int find(Node* node, int key) {
        // If this is a leaf node, just check if the key exists
        if (node->is_leaf_node == true) {
            for (int i = 0; i < node->key_count; ++i) {
                if (node->key[i] == key)
                    return key;
            }

            return -1;
        }

        // Otherwise, either check if it exists or recurse
        for (int i = 0; i < node->key_count; ++i) {
            if (node->key[i] >= key) {
                if (node->key[i] == key)
                    return key;
                else
                    return find(node->child[i], key);
            }
        }

        // If we couldn't find a key greater, we are on the last branch
        return find(node->child[node->key_count - 1], key);
    }


    void insert(int key) {
        // If root full, split it
        if (root->key_count == degree) {
            split_root();
        }

        insert_non_full(root, key);
    }

    void insert_non_full(Node* node, int key) {
        // Since in B-trees insertions are done at leaf level,
        // just fit the key.
        if (node->is_leaf_node == true) {
            // Shift keys to make space for insertion
            int i;
            for (i = node->key_count - 1; i >= 0 && key < node->key[i]; --i) {
                node->key[i + 1] = node->key[i];
            }

            // Place the key
            node->key[i + 1] = key;
            node->key_count++;
        }
        else {
            // Find where the key belongs
            int i;
            for (i = node->key_count - 1; i >= 0 && key < node->key[i]; --i)
                ;

            // Need to increment with 1
            i += 1;

            // If child is full, split it
            if (node->child[i]->key_count == degree) {
                split_child(node, i);

                // Maybe the key should go in the next child now (remember the split)
                if (key > node->key[i])
                    i++;
            }

            // Insert into child
            insert_non_full(node->child[i], key);
        }
    }

    void split_root() {
        Node* new_root = new Node();

        // The root can never be a leaf node
        new_root->is_leaf_node = false;

        new_root->child[0] = root;

        split_child(new_root, 0);

        root = new_root;
    }

    void split_child(Node* node, int which) {
        // Full node to split
        // This means child.key_count = 2 * minimum_degree - 1 or degree
        Node* child = node->child[which];
        Node* new_node = new Node();
        // If we are splitting a leaf, the emerging node is also a leaf
        new_node->is_leaf_node = child->is_leaf_node;

        // Allocate minimal space (yeah I mean that symbolically.)
        new_node->key_count = minimum_degree - 1;

        // Copy the greatest keys to the new node
        for (int i = 0; i < minimum_degree - 1; ++i) {
            // Remember a node can have at most 2 * minimum_degree - 1 keys
            new_node->key[i] = child->key[i + minimum_degree];
        }

        // Copy the children as well but only if not leaf
        if (child->is_leaf_node == false) {
            for (int i = 0; i < minimum_degree; ++i) {
                // Remember a node can have at most 2 * minimum_degree children
                new_node->child[i] = child->child[i + minimum_degree];
            }
        }

        // The child keeps the first minimum_degree - 1 keys, leaving the median key out
        child->key_count = minimum_degree - 1;

        // Shift children pointers of parent node to right to make space for new_node
        for (int i = node->key_count + 1; i > which; --i)
            node->child[i + 1] = node->child[i];

        node->child[which + 1] = new_node;

        // Shift keys of parent node to right to make space for new_node
        for (int i = node->key_count; i >= which; --i)
            node->key[i + 1] = node->key[i];

        // Now place the median key inside the parent
        node->key[which] = child->key[minimum_degree - 1];

        // Parent has gained a new child
        node->key_count++;
    }

    void print(Node* node, int depth = 0) {
        int temp_depth = depth;
        while (temp_depth--) {
            std::cout << " ";
        }

        std::cout << "[";
        for (int i = 0; i < node->key_count; ++i) {
            std::cout << node->key[i];
            if (i != node->key_count - 1)
                std::cout << ", ";
        }

        std::cout << "]\n";
        for (int i = 0; i < node->key_count + 1; ++i) {
            if (node->child[i] != nullptr)
                print(node->child[i], depth + 1);
        }
    }
};


#endif //PA_BTREE_H
