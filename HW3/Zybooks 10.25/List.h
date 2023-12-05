#ifndef HW10_25_LIST_H
#define HW10_25_LIST_H

#include <string>
#include <vector>


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
    List(const List& other);
    List& operator=(const List& rhs);
    List(List&& other);
    List& operator=(List&& rhs);
    ~List();
    bool empty() const { return head==nullptr; }
    void push_back(const Item& a);
    void push_front(const Item& a);

    iterator begin() const { return iterator(head); }
    iterator end() const { return iterator(nullptr); }

    friend std::vector<void*> getListPtrs(const List&);
};


#endif //HW10_25_LIST_H
