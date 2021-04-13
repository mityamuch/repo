#pragma once
#include<iostream>
#include "binary_tree.h"


template <typename T>
class RBTree
{

private:
	struct TreeStruct {
		int info;
		T key;
		bool black; //True - черное 
		TreeStruct* right;
		TreeStruct* left;
		TreeStruct* parent;
	};
    TreeStruct* newTree(int key, int info, TreeStruct* parent) {
        TreeStruct* curr = new TreeStruct;
        curr->info = info;
        curr->key = key;
        curr->right = curr->left = nullptr;
        curr->parent = parent;
        curr->black = false;
        return curr;
    }
    TreeStruct* grandparent(TreeStruct* curr) {
        if ((curr != nullptr) && (curr->parent != nullptr))
            return curr->parent->parent;
        else
            return nullptr;
    }
    TreeStruct* uncle(TreeStruct* curr) {
        TreeStruct* g = grandparent(curr);
        if (g == nullptr)
            return nullptr; // No grandparent means no uncle
        if (curr->parent == g->left)
            return g->right;
        else
            return g->left;
    }
    void insert1(TreeStruct* n) {
        if (n->parent == nullptr)
            n->black = true;
        else
            insert2(n);

    }
    void insert2(TreeStruct* n) {
        if (n->parent->black)
            return;
        else
            insert3(n);
    }
    void insert3(TreeStruct* n) {
        TreeStruct* u = uncle(n), * g;

        if ((u != NULL) && (!u->black)) {
            n->parent->black = true;
            u->black = true;
            g = grandparent(n);
            g->black = false;
            insert1(g);
        }
        else {
            insert4(n);
        }
    }
    void insert4(TreeStruct* n) {
        TreeStruct* g = grandparent(n);

        if ((n == n->parent->right) && (n->parent == g->left)) {
            rotateLeft(n->parent);
            n = n->left;
        }
        else if ((n == n->parent->left) && (n->parent == g->right)) {
            rotateRight(n->parent);
            n = n->right;
        }
        insert5(n);
    }
    void insert5(TreeStruct* n) {
        TreeStruct* g = grandparent(n);

        n->parent->black = true;
        g->black = false;
        if ((n == n->parent->left) && (n->parent == g->left)) {
            rotateRight(g);
        }
        else {
            rotateLeft(g);
        }
    }
    void delete1(TreeStruct* n) {
        if (n == node) {
            node = nullptr;
            return;
        }
        if (!n->right && !n->left) {
            if (n->parent->right == n)
                n->parent->right = nullptr;
            else
                n->parent->left = nullptr;
            return;
        }
        else {
            if ((n->left && n->right == nullptr) || (n->right && n->left == nullptr)) {
                if (n->right)
                    if (n->parent->right == n)
                        n->parent->right = n->right;
                    else
                        n->parent->left = n->right;
                else
                    if (n->parent->right == n)
                        n->parent->right = n->left;
                    else
                        n->parent->left = n->left;
            }
            else
                delete2(n);
        }
    }
	void delete2(TreeStruct* n);




    void rotateLeft(TreeStruct* n) {
        TreeStruct* pivot = n->right;

        pivot->parent = n->parent;
        if (n->parent != nullptr) {
            if (n->parent->left == n)
                n->parent->left = pivot;
            else
                n->parent->right = pivot;
        }

        n->right = pivot->left;
        if (pivot->left != nullptr)
            pivot->left->parent = n;

        n->parent = pivot;
        pivot->left = n;
        if (n == node)
            node = pivot;
    }
    void rotateRight(TreeStruct* n) {
        TreeStruct* pivot = n->left;
        pivot->parent = n->parent; /* ïðè ýòîì, âîçìîæíî, pivot ñòàíîâèòñÿ êîðíåì äåðåâà */
        if (n->parent != nullptr) {
            if (n->parent->left == n)
                n->parent->left = pivot;
            else
                n->parent->right = pivot;
        }
        n->left = pivot->right;
        if (pivot->right != nullptr)
            pivot->right->parent = n;

        n->parent = pivot;
        pivot->right = n;
        if (n == node)
            node = pivot;
    }
    void setRight(TreeStruct* curr, int key, int info) {
        curr->right = newTree(key, info, curr);
    }
    void setLeft(TreeStruct* curr, int key, int info) {
        curr->left = newTree(key, info, curr);
    }


public:
    TreeStruct* node;
    RBTree() {

        node = nullptr;
    }
    void insert(int key, int info) {
        TreeStruct* curr, * next;
        if (node == nullptr) {
            node = newTree(key, info);
            node->black = true;
            node->key = key;
            node->info = info;
        }
        curr = next = node;
        while (next != nullptr) {
            curr = next;
            if (key < curr->key)
                next = curr->left;
            if (key > curr->key)
                next = curr->right;
            if (key == curr->key) {
                curr->info = info;
                return;
            }
        }
        if (key < curr->key) {
            setLeft(curr, key, info);
            next = curr->left;
        }
        else {
            setRight(curr, key, info);
            next = curr->right;
        }
        insert1(next);
    }
    void erase(int key) {
        if (!exist(key))
            return;
        TreeStruct* curr, * next;
        curr = next = node;
        while (next != nullptr) {
            curr = next;
            if (key < curr->key)
                next = curr->left;
            if (key > curr->key)
                next = curr->right;
            if (key == curr->key) {
                delete1(curr); 
                return;
            }
        }
    }
    int  get(int key) {
        TreeStruct* curr, * next;
        curr = next = node;
        if (exist(key))
            while (next != nullptr) {
                curr = next;
                if (key < curr->key)
                    next = curr->left;
                if (key > curr->key)
                    next = curr->right;
                if (key == curr->key) {
                    return curr->info;
                }
            }
    }
    bool exist(int key) {
        TreeStruct* curr, * next;
        curr = next = node;
        while (next != nullptr) {
            curr = next;
            if (key < curr->key)
                next = curr->left;
            if (key > curr->key)
                next = curr->right;
            if (key == curr->key) {
                return true;
            }
        }
        return false;
    }
    ~RBTree() {
        delete node;
    }
};
