#include "List.h"
#include <iostream>
using namespace std;

void List::reverseInPlace() {
    ListNode * currentNode = head;
    ListNode * tempNext = nullptr;
    ListNode * previousNode = nullptr;

    if (head != tail) {
        while (currentNode != nullptr) {
            tempNext = currentNode->next;       //store the next pointer in a temporary pointer location
            currentNode->next = previousNode;       //set the current next pointer = to previous node (nullptr in first case bc end of list)
            previousNode = currentNode;             //new previous = current node pointer. This gives the next current a previous to point to
            currentNode = tempNext;             //move to the next node and repeat the while loop till entire list has been modified;
            //if (tempNext == tail) break;
        }
    head = previousNode;
    }
}
// DON'T CHANGE ANYTHING BELOW THIS

List::List(const List& other) {
    auto p = other.head;
    while (p) {
        push_back(p->item);
        p = p->next;
    }
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
