
#ifndef ZYBOOKS_13_23_MINHEAP_H
#define ZYBOOKS_13_23_MINHEAP_H


#include <vector>

template <typename T>
class MinHeap {
public:
    MinHeap() {
        numItems = 0;
    }

    bool empty() {
        return numItems == 0;
    }

    void insert(T& data) {
        heap.push_back(data);
        percolateUp(heap.size() - 1);
        numItems++;
    }
    T remove() {
        T min = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        percolateDown(0);
        numItems--;
        return min;
    }
    T& peek() {
        return heap[0];
    }
private:
    std::vector<T> heap;
    size_t numItems;
    void percolateUp(size_t index) {
        while (index > 0) {
            size_t parent = (index-1) / 2;
            if (heap[index] < heap[parent]) {
                T tmp = heap[parent];
                heap[parent] = heap[index];
                heap[index] = tmp;
                index = parent;
            }
            else {
                break;
            }
        }
    }
    void percolateDown(size_t index) {
        T val = heap[index];
        size_t items = heap.size();
        size_t child = index * 2 + 1;
        while (child < items) {
            T min_val = val;
            size_t min_index = index;
            for (size_t i = child; i <= child+1 && i < items; i++) {
                if (min_val > heap[i]) {
                    min_val = heap[i];
                    min_index = i;
                }
            }
            if (min_val == val) break;
            T tmp = heap[index];
            heap[index] = heap[min_index];
            heap[min_index] = tmp;
            index = min_index;
            child = index * 2 + 1;
        }
    }
};

#endif //ZYBOOKS_13_23_MINHEAP_H
