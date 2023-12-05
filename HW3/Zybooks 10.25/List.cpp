#include "List.h"

// IMPLEMENT MOVE CONSTRUCTOR

// IMPLEMENT MOVE ASSIGNMENT OPERATOR

List::List(const List& other) {
    auto p = other.head;
    while (p) {
        push_back(p->item);
        p = p->next;
    }
}

List& List::operator=(const List& rhs) {
    if (&rhs == this) return *this;
    // delete old list
    auto p = head;
    while (p) {
        auto tmp = p->next;
        delete p;
        p = tmp;
    }
    head = tail = nullptr;
    // copy from rhs
    p = rhs.head;
    while (p) {
        push_back(p->item);
    }
    // return reference to self
    return *this;
}

List::~List() {
    auto p = head;
    while (p) {
        auto tmp = p->next;
        delete p;
        p = tmp;
    }
}

void List::push_back(const Item& a) {
    auto node {new ListNode(a)};
    if ( head == nullptr ) {
        // empty list
        head = node;
        tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
}

void List::push_front(const Item& a) {
    auto node {new ListNode(a)};
    if (head == nullptr) {
        head = node;
        tail = node;
    }
    else {
        node->next = head;
        head = node;
    }
}

List::List(List &&other) {

        head = other.head;
        other.head = nullptr;
        tail = other.tail;
        other.tail = nullptr;

}

List& List::operator=(List&& rhs) {
    if (this->head != rhs.head) {
        head = rhs.head;
        rhs.head = nullptr;
        tail = rhs.tail;
        rhs.tail = nullptr;
    }
    return *this;
}