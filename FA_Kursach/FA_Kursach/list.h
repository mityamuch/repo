#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Elem
{
    T data; // данные
    Elem* next, * prev;
};
template <typename T>
class List
{
    // Голова, хвост
    Elem<T>* Head, * Tail;
    // Количество элементов
    int Count;



public:

    // Конструктор
    List() {
        Head = Tail = NULL;
        Count = 0;
    }

    ~List() {
    }

    Elem<T>* GetElem(int pos) {
        Elem* temp = Head;
        if (pos < 1 || pos > Count)
        {
            cout << "Incorrect position !!!\n";
            return 0;
        }

        int i = 1;
        while (i < pos && temp != 0)
        {
            temp = temp->next;
            i++;
        }

        if (temp == 0)
            return 0;
        else
            return temp;
    }

    void AddTail(int n) {
        Elem* temp = new Elem;
        temp->next = 0;
        temp->data = n;
        temp->prev = Tail;
        if (Tail != 0)
            Tail->next = temp;

        if (Count == 0)
            Head = Tail = temp;
        else
            Tail = temp;

        Count++;
    }

    void AddHead(int n) {
        Elem* temp = new Elem;
        temp->prev = 0;
        temp->data = n;
        temp->next = Head;
        if (Head != 0)
            Head->prev = temp;
        if (Count == 0)
            Head = Tail = temp;
        else
            Head = temp;
        Count++;
    }

    void Print() {
        if (Count != 0)
        {
            Elem* temp = Head;
            cout << "( ";
            while (temp->next != 0)
            {
                cout << temp->data << ", ";
                temp = temp->next;
            }

            cout << temp->data << " )\n";
        }
    }

};