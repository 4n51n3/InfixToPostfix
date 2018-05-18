//
// Created by d on 24.01.18.
//

#ifndef CPP_LIST_LIST_H
#define CPP_LIST_LIST_H

#include <cstdlib>

//#include <algorithm> //std::copy
class Item {
public:
    char c;
};





class List {
private:
    class Node;

private:
    unsigned long int Count;

public:
    Node *head;
	Node *last;

public:
    List();

    virtual ~List();

    bool IsEmpty();

    bool IsFull();

    void AddItem(Item &item);

    void Traverse(void (*pFunc)(Item item));

	void Delete(Item* item);

    void Free();

    unsigned long int GetCount(){
        return Count;
    }

    Item &operator[](int x);

    List(const List &other);

    class Iterator;

};



class List::Node {
public:
    Item item;
    Node *next;
	Node *prev;
public:
    Node();

    virtual ~Node();

    void CopyToNode(Item &item){
        //  std::copy(&item, &item, &(this->item));
        memcpy(&(this->item), &item, sizeof(Item));//work
    }

    void Dispose() {
        delete this;
    }


};

class List::Iterator{
    
public:
    Item* item;
	Node* curr;

    virtual ~Iterator() {
        item = nullptr;
        curr = nullptr;
    }

    explicit Iterator(List &lst){
        this->curr = lst.head;
        item = &curr->item;
    }

    explicit Iterator(List *lst){
        this->curr = lst->head;
        item = &curr->item;
    }

    Iterator() = delete;

    bool operator()(){
        return curr != nullptr;
    }

    void operator++(){
        curr = curr->next;
        item = &curr->item;
    }

    void operator++(int notUsed){
        curr = curr->next;
        item = &curr->item;
    }
};
#endif //CPP_LIST_LIST_H
