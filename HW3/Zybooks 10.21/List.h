#ifndef HW10_21_LIST_H
#define HW10_21_LIST_H

#include <string>

using Item = std::string;

class List {
private:

    class ListNode {
    public:
        Item item;
        ListNode * next;
        ListNode(Item i, ListNode *n=nullptr) {
            item = i;
            next = n;
        }
    };

    ListNode * head = nullptr;
    ListNode * tail = nullptr;

public:
    class iterator {
        ListNode *node;
        iterator(ListNode *n) : node {n} {}
        friend class List;
    public:
        Item& operator*() { return node->item; }
        iterator& operator++() { node = node->next; return *this; }
        bool operator!=(const iterator& other) const { return node != other.node; }
    };

public:
    List() = default;
    List(const List &other);
    ~List();
    bool empty() const { return head==nullptr; }
    void push_back(const Item& a);
    void push_front(const Item& a);
    void reverseInPlace();

    iterator begin() const { return iterator(head); }
    iterator end() const { return iterator(nullptr); }
};


#endif //HW10_21_LIST_H
