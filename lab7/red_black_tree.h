#pragma once

#include "binary_tree.h"

template <typename T>
class   Red_black_tree : public binary_tree<T>
{
private:
    enum            color { RED, BLACK };

    struct          tree_node
    {
        T           data;
        int         color;
        tree_node* left;
        tree_node* right;
        tree_node* parent;

        //
    };

private:
    tree_node* root;
    unsigned int    rotations;

   
    T* search(tree_node* node, T x) {
        if (node != nullptr)
        {
            if (!this->m_functor->CallFunctor(t->data, x) && !this->m_functor->CallFunctor(x, t->data))
                return (&t->data);
            if (this->m_functor->CallFunctor(x, t->data))
                return search(node->left, x);
            else
                return search(node->right, x);
        }
        return (nullptr);
    }

    int             get_color(tree_node*& node) {
        if (node == nullptr)
            return (BLACK);
        return (node->color);
    }

    void            rotate_left(tree_node*& node) {
        tree_node* right_child = node->right;

        node->right = right_child->left;
        if (node->right != nullptr)
            node->right->parent = node;
        right_child->parent = node->parent;

        if (node->parent == nullptr)
            root = right_child;
        else if (node == node->parent->left)
            node->parent->left = right_child;
        else
            node->parent->right = right_child;

        right_child->left = node;
        node->parent = right_child;
        rotations++;
    }

    void            rotate_right(tree_node*& node) {
        tree_node* left_child = node->left;

        node->left = left_child->right;
        if (node->left != nullptr)
            node->left->parent = node;
        left_child->parent = node->parent;

        if (node->parent == nullptr)
            root = left_child;
        else if (node == node->parent->left)
            node->parent->left = left_child;
        else
            node->parent->right = left_child;

        left_child->right = node;
        node->parent = left_child;
        rotations++;
    }

    void            delete_tree(tree_node* node) {
        if (node != nullptr)
        {
            delete_tree(node->left);
            delete_tree(node->right);
            delete node;
        }
    }

    void            fix_insert(tree_node*& node) {
        tree_node* parent = nullptr;
        tree_node* grandparent = nullptr;

        while (node != root && get_color(node) == RED && get_color(node->parent) == RED)
        {
            parent = node->parent;
            grandparent = parent->parent;
            if (parent == grandparent->left)
            {
                tree_node* uncle = grandparent->right;

                if (get_color(uncle) == RED)
                {
                    set_color(uncle, BLACK);
                    set_color(parent, BLACK);
                    set_color(grandparent, RED);
                    node = grandparent;
                }
                else
                {
                    if (node == parent->right)
                    {
                        rotate_left(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rotate_right(grandparent);
                    std::swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
            else
            {
                tree_node* uncle = grandparent->left;

                if (get_color(uncle) == RED)
                {
                    set_color(uncle, BLACK);
                    set_color(parent, BLACK);
                    set_color(grandparent, RED);
                    node = grandparent;
                }
                else
                {
                    if (node == parent->left)
                    {
                        rotate_right(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rotate_left(grandparent);
                    std::swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }
        set_color(root, BLACK);
    }

    void            fix_delete(tree_node*& node) {
        if (node == nullptr)
            return;
        if (node == root)
        {
            root = nullptr;
            return;
        }
        if (get_color(node) == RED || get_color(node->left) == RED || get_color(node->right) == RED)
        {
            tree_node* child = node->left != nullptr ? node->left : node->right;

            if (node == node->parent->left) {
                node->parent->left = child;
                if (child != nullptr)
                    child->parent = node->parent;
                set_color(child, BLACK);
                delete node;
            }
            else
            {
                node->parent->right = child;
                if (child != nullptr)
                    child->parent = node->parent;
                set_color(child, BLACK);
                delete node;
            }
        }
        else
        {
            tree_node* sibling = nullptr;
            tree_node* parent = nullptr;
            tree_node* ptr = node;

            set_color(ptr, BLACK);
            while (ptr != root && get_color(ptr) == BLACK)
            {
                parent = ptr->parent;
                if (ptr == parent->left)
                {
                    sibling = parent->right;
                    if (get_color(sibling) == RED)
                    {
                        set_color(sibling, BLACK);
                        set_color(parent, RED);
                        rotate_left(parent);
                    }
                    else
                    {
                        if (get_color(sibling->left) == BLACK && get_color(sibling->right) == BLACK)
                        {
                            set_color(sibling, RED);
                            if (get_color(parent) == RED)
                                set_color(parent, BLACK);
                            else
                                set_color(parent, BLACK);
                            ptr = parent;
                        }
                        else
                        {
                            if (get_color(sibling->right) == BLACK)
                            {
                                set_color(sibling->left, BLACK);
                                set_color(sibling, RED);
                                rotate_right(sibling);
                                sibling = parent->right;
                            }
                            set_color(sibling, parent->color);
                            set_color(parent, BLACK);
                            set_color(sibling->right, BLACK);
                            rotate_left(parent);
                            break;
                        }
                    }
                }
                else
                {
                    sibling = parent->left;
                    if (get_color(sibling) == RED)
                    {
                        set_color(sibling, BLACK);
                        set_color(parent, RED);
                        rotate_right(parent);
                    }
                    else
                    {
                        if (get_color(sibling->left) == BLACK && get_color(sibling->right) == BLACK)
                        {
                            set_color(sibling, RED);
                            if (get_color(parent) == RED)
                                set_color(parent, BLACK);
                            else
                                set_color(parent, BLACK);
                            ptr = parent;
                        }
                        else
                        {
                            if (get_color(sibling->left) == BLACK)
                            {
                                set_color(sibling->right, BLACK);
                                set_color(sibling, RED);
                                rotate_left(sibling);
                                sibling = parent->left;
                            }
                            set_color(sibling, parent->color);
                            set_color(parent, BLACK);
                            set_color(sibling->left, BLACK);
                            rotate_right(parent);
                            break;
                        }
                    }
                }
            }
            if (node == node->parent->left)
                node->parent->left = nullptr;
            else
                node->parent->right = nullptr;
            delete node;
            set_color(root, BLACK);
        }
    }

    void            set_color(tree_node*& node, int color) {
        if (node == nullptr)
            return;
        node->color = color;
    }

    tree_node* create_node(T val) {
        tree_node* node = new tree_node;

        if (node != nullptr)
        {
            node->data = val;
            node->color = RED;
            node->left = nullptr;
            node->right = nullptr;
            node->parent = nullptr;
        }
        return (node);
    }

    tree_node* find_min(tree_node*& node) {

        tree_node* ptr = node;

        while (ptr->left != nullptr)
            ptr = ptr->left;

        return ptr;
    }

    tree_node* delete_bst(tree_node*& root, T data) {
        if (root == nullptr)
            return root;
        if (this->comparator->compare(data, (*root).data) < 0)
            return delete_bst(root->left, data);
        if (this->comparator->compare(data, (*root).data) > 0)
            return delete_bst(root->right, data);
        if (root->left == nullptr || root->right == nullptr)
            return root;

        tree_node* temp = find_min(root->right);

        root->data = temp->data;
        return delete_bst(root->right, temp->data);
    }

    tree_node* insert_bst(tree_node*& root, tree_node*& node) {

        if (root == nullptr)
            return (node);

        if (this->comparator->compare((*node).data, (*root).data) < 0)
        {
            root->left = insert_bst(root->left, node);
            root->left->parent = root;
        }
        else if (this->comparator->compare((*node).data, (*root).data) >= 0)
        {
            root->right = insert_bst(root->right, node);
            root->right->parent = root;
        }
        return (root);
    }



public:

    template typename <U>
    Red_black_tree(U func)
        :binary_tree<T>(func)
    {
        root = nullptr;
    }

    ~Red_black_tree() {
        if (root != nullptr)
            delete_tree(this->root);
    }

    T* Find(tree_node* node, T val) {
        return search(root, val);
    }

    bool            is_empty() {
        return (root == nullptr);
    }

    void            clear_tree() {
        if (root != nullptr)
            delete_tree(root);
        root = nullptr;
        rotations = 0;
    }

    void Add(T x)() {
        tree_node* node = create_node(x);

        if (node != nullptr)
        {
            root = insert_bst(root, node);
            fix_insert(node);
        }
    }

    void Remove(T x)() {
        tree_node* node = delete_bst(root, x);

        fix_delete(node);
    }

    unsigned int    get_rotations() {
        return (rotations);
    }
};
















