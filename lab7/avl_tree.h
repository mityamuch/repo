#pragma once
#include "binary_tree.h"

template <typename T>
class avl_tree :public binary_tree<T>
{
private:
	struct node
	{
		T data;
		node* left;
		node* right;
		int height;
	};

	node* root;

	node* insert(const T& x, node* t)
	{
		if (t == NULL)
		{
			t = new node;
			t->data = x;
			t->height = 0;
			t->left = t->right = NULL;
		}
		else if (this->m_functor->CallFunctor(x, t->data))
		{
			t->left = insert(x, t->left);
			if (height(t->left) - height(t->right) == 2)
			{
				if (x < t->left->data)
					t = singleRightRotate(t);
				else
					t = doubleRightRotate(t);
			}
		}
		else if (this->m_functor->CallFunctor(t->data, x))
		{
			t->right = insert(x, t->right);
			if (height(t->right) - height(t->left) == 2)
			{
				if (x > t->right->data)
					t = singleLeftRotate(t);
				else
					t = doubleLeftRotate(t);
			}
		}

		t->height =std::max(height(t->left), height(t->right)) + 1;
		return t;
	}

	node* singleRightRotate(node*& t)
	{
		node* u = t->left;
		t->left = u->right;
		u->right = t;
		t->height =std::max(height(t->left), height(t->right)) + 1;
		u->height =std::max(height(u->left), t->height) + 1;
		return u;
	}

	node* singleLeftRotate(node*& t)
	{
		node* u = t->right;
		t->right = u->left;
		u->left = t;
		t->height = std::max(height(t->left), height(t->right)) + 1;
		u->height = std::max(height(t->right), t->height) + 1;
		return u;
	}

	node* doubleLeftRotate(node*& t)
	{
		t->right = singleRightRotate(t->right);
		return singleLeftRotate(t);
	}

	node* doubleRightRotate(node*& t)
	{
		t->left = singleLeftRotate(t->left);
		return singleRightRotate(t);
	}

	node* findMin(node* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->left == NULL)
			return t;
		else
			return findMin(t->left);
	}

	node* remove(const T& x, node* t)
	{
		node* temp;
		if (t == NULL)
			return NULL;
		else if (this->m_functor->CallFunctor(x, t->data))
			t->left = remove(x, t->left);
		else if (this->m_functor->CallFunctor(t->data, x))
			t->right = remove(x, t->right);

		else if (t->left && t->right)
		{
			temp = findMin(t->right);
			t->data = temp->data;
			t->right = remove(t->data, t->right);
		}
		else
		{
			temp = t;
			if (t->left == NULL)
				t = t->right;
			else if (t->right == NULL)
				t = t->left;
			delete temp;
		}
		if (t == NULL)
			return t;

		t->height = std::max(height(t->left), height(t->right)) + 1;
		if (height(t->left) - height(t->right) == 2)
		{
			if (height(t->left->left) - height(t->left->right) == 1)
				return singleRightRotate(t);
			else
				return doubleRightRotate(t);
		}
		else if (height(t->right) - height(t->left) == 2)
		{
			if (height(t->right->right) - height(t->right->left) == 1)
				return singleLeftRotate(t);
			else
				return doubleLeftRotate(t);
		}
		return t;
	}

	int height(node* t)
	{
		return (t == NULL ? -1 : t->height);
	}

	int getBalance(node* t)
	{
		if (t == NULL)
			return 0;
		else
			return height(t->left) - height(t->right);
	}

	T* search(const T& x, node* t) {
		if (!this->m_functor->CallFunctor(t->data, x) || !this->m_functor->CallFunctor(x, t->data))
			return &(t->data);
		else if (this->m_functor->CallFunctor(t->data, x)) {
			if (t->left == nullptr)
				return nullptr;
			return search(x, t->left);
		}
		else {
			if (t->right == nullptr)
				return nullptr;
			return search(x, t->right);
		}
	}
	void printtree(node* t) {
		if (t == nullptr)
			return;
		printtree(t->left);
		std::cout << t->data << std::endl;
		printtree(t->right);

	}

public:
	template <typename U>
	avl_tree(U func)
		:binary_tree<T>(func)
	{
		root = NULL;
	}
	void clean_tree(node* t) {
		if (t == nullptr)
			return;
		clean_tree(t->left);
		clean_tree(t->right);
		delete t;
	}

	~avl_tree() {
		clean_tree(root);
	}

	void Add(T x) override
	{
		root = insert(x, root);
	}

	void Remove(T x) override
	{
		root = remove(x, root);
	}

	T* Find(T x){
		return search(x, root);
	}

	void print() {
		printtree(root);
	}
};