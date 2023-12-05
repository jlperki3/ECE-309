#include "IntBSTree.h"

IntBSTree::~IntBSTree() {
    deleteSubTree(root);
}

void IntBSTree::deleteSubTree(BTNode* subroot) {
    if (subroot) {
        deleteSubTree(subroot->left);
        deleteSubTree(subroot->right);
        delete subroot;
    }
}

std::list<int> IntBSTree::getOrderedList() {
    return traverse(root);
}



bool IntBSTree::search(int key) {
    BTNode *node = root;
    while (node) {
        if (node->data == key) return true;
            // key is smaller than node -- move to the left
        else if (key < node->data) {
            node = node->left;
        }
            // key is >= node -- move to the right
        else {
            node = node->right;
        }
    }
    return false;
};

void IntBSTree::insert(int key) {
    auto node = new BTNode(key);
    // if tree is empty, inserted node is the new root
    if (!root) {
        root = node;
    }
    else {
        BTNode * cur = root;
        while (cur) {
            // (1) data is less than current node, insert to the left
            if (key < cur->data) {
                // if there's a left child, can't insert here -- move to the left
                if (cur->left) cur = cur->left;
                    // if no left child, insert and return
                else {
                    cur->left = node;
                    return;
                }

            }
                // (2) data is greater than or equal to current node, insert to the right
            else {
                // if there's a right child, can't insert here -- move to the right
                if (cur->right) cur = cur->right;
                    // if no right child, insert and return
                else {
                    cur->right = node;
                    return;
                }
            }
        }
        // should never reach this point -- will return from inside the loop
    }
}


bool IntBSTree::remove(int key) {
    BTNode *cur = root;
    // our node class does not include a parent pointer
    // so we will track the parent as we descend the tree
    BTNode *parent = nullptr;
    bool removed = false;
    while (!removed && cur) {
        if (cur->data == key) { // found key, remove node
            removeNode(cur, parent);
            delete cur;
            removed = true;  // exit the loop
        } else if (key < cur->data) { // search left
            parent = cur;
            cur = cur->left;
        } else { // search right
            parent = cur;
            cur = cur->right;
        }
    }
    // loop exits if (a) we found the node and removed it, or
    // (b) we could not find the key (cur == nullptr)
    return removed;
}

bool IntBSTree::removeNode(BTNode *node, BTNode *parent) {
    // double-check parent-child relationship
    if (parent && (parent->left != node) && (parent->right != node)) return false;  // error, do nothing
    if (!parent && (node != root)) return false;   // error, do nothing

    // CASE 1: leaf node
    if (!node->left && !node->right) {
        if (!parent) {
            // removing root as only node
            root = nullptr;
        }
            // remove pointer to this node from parent
        else if (parent->left == node) parent->left = nullptr;
        else parent->right = nullptr;
    }

        // CASE 2: one child
        // if internal node with only left child
    else if (node->left && !node->right) {
        // move left child into this node's position
        if (!parent) {
            // replace root with left child
            root = node->left;
        }
        else if (parent->left == node) parent->left = node->left;
        else parent->right = node->left;
    }
        // if internal node with only right child
    else if (!node->left && node->right) {
        // move right child into this node's position
        if (!parent) {
            // replace root with right child
            root = node->right;
        }
        else if (parent->left == node) parent->left = node->right;
        else parent->right = node->right;
    }

        // CASE 3: two children
        // if internal node with two children
    else {
        // don't remove -- find successor, copy data from successor, and then remove that node
        // successor is left-most node in right subtree
        BTNode *s = node->right;  // s is known to be non-null
        BTNode *sp = node;   // successor's parent node
        bool found = false;
        while (!found) {
            // keep looking until there is no left child
            if (!s->left) found = true;
            else {
                sp = s;
                s = s->left;
            }
        }
        // remove s from its position in tree, then replace node with s
        bool rs = removeNode(s, sp);  // recursive!
        // replace node with s
        if (rs) {
            s->left = node->left;
            s->right = node->right;
            if (!parent) root = s;
            else if (parent->left == node) parent->left = s;
            else parent->right = s;
        }
        else return false;  // unable to remove successor?
    }
    return true;
}
