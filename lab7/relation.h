#pragma once
#include <vector>
template <typename T>
class relation {
private:
    
    struct Node {
        T val;
        Node* next;
        Node(T _val) : val(_val), next(nullptr) {}
    };

    struct list {
        Node* first;
        Node* last;
        list() : first(nullptr), last(nullptr) {}
        bool is_empty() {
            return first == nullptr;
        }

        T* push_back(T _val) {
            Node* p = new Node(_val);
            if (is_empty()) {
                first = p;
                last = p;
                return &last->val;
            }
            last->next = p;
            last = p;
            return &last->val;
        }

        Node* find(T _val) {
            Node* p = first;
            while (p && p->val != _val) p = p->next;
            return (p && p->val == _val) ? p : nullptr;
        }

        void remove(T _val) {
            if (is_empty()) return;
            Node* slow = first;
            Node* fast = first->next;
            while (fast && fast->val != _val) {
                fast = fast->next;
                slow = slow->next;
            }
            if (!fast) {
                std::cerr << "This element does not exist" << std::endl;
                return;
            }
            slow->next = fast->next;
            delete fast;
        }

        void print() {
            if (is_empty()) return;
            Node* p = first;
            while (p) {
                std::cout << p->val << " ";
                p = p->next;
            }
            std::cout << std::endl;
        }

    };
    
    list data;
	std::vector <binary_tree<T*>*> indexes;
public:
	void Add(T x) {
        T* node = data.push_back(x);
        for (auto& c : indexes) {
            c->Add(node);
        }
    }

	void Remove(T x){
        Node* node = data.find(x);
        for (auto& c : indexes) {
            c->Remove(node);
        }
        data.remove(x);

    }

	T* Find(T x,int indexnum){
        auto result=indexes[indexnum]->Find(indexnum);
        return &((*result)->val);
    }

	void Addindex(binary_tree<T*>* ind){
        indexes.push_back(ind);
        Node* p = data.first;
        while (p && p->next != nullptr) {
            ind->Add(&p->val);
            p = p->next;
        }
    
    }

	void Removeindex(int indexnum){
        delete indexes[indexnum];
        indexes.erase(indexes.begin()+indexnum);
        
    }


};