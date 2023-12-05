#ifndef HW12_10_HASHTABLE_H
#define HW12_10_HASHTABLE_H

#include <list>
#include <vector>
using std::list, std::vector;



class HashTable {
private:

    vector<list<int>> table;

    size_t size; // SIZE of table array
    size_t hash(int value) const { return ( (unsigned long)value * 997) % size; }

public:
    HashTable(size_t htsize=1000) : size{htsize}
    {
        table.resize(size);  // create initial empty lists
    }

    ~HashTable() = default;


    void insert(int data) {
        int index = hash(data);
        if (find(data) == false) table[index].push_back(data);  // add to bucket
    }

    bool find(int data)
    {
        int index = hash(data);
        auto it = table[index].begin();
        while(it != table[index].end())
        {
            if ( *it == data )
                return true;
            ++it;
        }

        return false;
    }

    void remove(int data)
    {
        int index = hash(data);
        auto it = table[index].begin();
        while (it != table[index].end() && *it != data) ++it;
        if (it != table[index].end()) {
            table[index].erase(it);   // remove from list
        }
    }

    // DO NOT REMOVE OR MODIFY
    size_t getTableSize() const { return size; }

    size_t getNumElements() const {
        size_t num = 0;
        for(size_t i=0; i<getTableSize(); i++)
        {
            num += table[i].size();
        }
        return num;
    }
};



#endif //HW12_10_HASHTABLE_H
