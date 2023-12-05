#include <iostream>
#include "MinHeap.h"

int main() {
    MinHeap<int> min_heap;
    for (int i = 10; i >= 0; i--) {
        min_heap.insert(i);
    }
    while (!min_heap.empty()) {
        int min_item = min_heap.remove();
        std::cout << min_item << " ";
    }
// Output: 1 3 5 8

    return 0;
}
