#ifndef ECE309_SPR23_STREETMAP_HASHTABLE_H
#define ECE309_SPR23_STREETMAP_HASHTABLE_H

#include <vector>
#include <iostream>
#include <list>

// Hash Table for key K and object T
// Class T must implement: K T::key()
// Type K must have a defined std::hash<K> and must implement ==
template<class K, class T>
class HashTable {
private:
    using Item = std::pair<K,T>;
public:
    // default constructor: empty hash table, # buckets is optional
    explicit HashTable(size_t buckets=511)
    : numBuckets{buckets}, table(buckets) {}
    // use default copy and move constructors, assignment operators

    void rehash(size_t buckets);
    bool find(K key, T& found) const;
    bool insert(K key, const T& value);
    bool erase(const K& key, T& removed);

    size_t buckets() const { return numBuckets; }
    size_t size() const { return numItems; }
    float max_load_factor() const { return max_lf; }
    void max_load_factor(float mf) {
        max_lf = mf;
    }
    bool empty() const { return numItems == 0; }
    void clear() {
        for (size_t b {0}; b < numBuckets; ++b) table.at(b).clear();
        numItems = 0;
    }
    // normally would not be public, but specified for testing
    size_t keyToBucket(const K& key) const {
        return hash(key) % numBuckets;
    }

private:
    size_t numBuckets;
    std::vector<std::list<Item>> table;
    size_t numItems {0};
    std::hash<K> hash;
    float max_lf { 3 };

public:
    // NOTE: Iterator was not required for the Program.
    class iterator {
        friend class HashTable;
    public:
        // listIter is an iterator into one of the bucket lists
        Item& operator*() const { return *listIter; }
        bool operator==(const iterator& other) const {
            // no need to check table, because listIter will only be equal if within same list
            if (&table != &other.table) return false;
            if (bucket != other.bucket) return false;
            if (bucket == numBuckets) return true;  // both are end()
            return listIter == other.listIter;
        }
        bool operator!=(const iterator& other) const {
            // no need to check table, because listIter will only be equal if within same list
            if (&table != &other.table) return true;
            if (bucket != other.bucket) return true;
            if (bucket == numBuckets) return false;  // both are end()
            return listIter != other.listIter;
        }
        iterator& operator++() {
            if (bucket == numBuckets) return *this;   // already at end()
            if (++listIter == table[bucket].end()) {
                // if incrementing listIter reaches end of bucket list, find the next non-empty list
                while (1) {
                    ++bucket;   // if == numBuckets, this is end()
                    if (bucket == numBuckets) break;
                    auto& theList { table[bucket] };
                    if (!theList.empty()) {
                        listIter = theList.begin();
                        break;
                    }
                }
            }
            return *this;
        }
    private:
        std::vector<std::list<Item>>& table; // reference to table in HashTable
        size_t numBuckets;
        size_t bucket;
        typename std::list<Item>::iterator listIter;
        iterator(std::vector<std::list<Item>>& t, size_t nb, bool end)
        : table{t}, numBuckets{nb} {
            if (end) { bucket = numBuckets; }
            else {
                // initialize iter to first non-empty list
                for (bucket = 0; (bucket < numBuckets) && (table[bucket].empty()); ++bucket);
                if (bucket < numBuckets) {
                    listIter = table[bucket].begin();
                }
            }
        }
    };

    iterator begin() { return {table, numBuckets, false}; }
    iterator end() { return {table, numBuckets, true}; }
};

#if 0   // Note: two implementations -- the one below uses hash table iterator
template <class K, class T>
void HashTable<K,T>::rehash(size_t buckets) {
    std::vector<std::list<Item>> newTable(buckets);
    // remove every item from the old table, and hash into the new table
    for (size_t j {0}; j < numBuckets; ++j) {
        auto list = table[j];
        while (!list.empty()) {
            auto kv = list.front();
            size_t b = hash(kv.first) % buckets;
            newTable[b].push_back(std::move(kv));
            list.pop_front();
        }
    }
    numBuckets = buckets;
    table = std::move(newTable);
}
#else
template <class K, class T>
void HashTable<K,T>::rehash(size_t buckets) {
    std::vector<std::list<Item>> tmp { std::move(table) };
    table.clear();   // should be empty due to move, but making sure
    table.resize(buckets);
    numBuckets = buckets;
    numItems = 0;
    for (auto & old : tmp) {
        // for each list in old table...
        while (!old.empty()) {
            auto & kv = old.front();
            insert(kv.first, kv.second);
            old.pop_front();
        }
    }
}
#endif


template <class K, class T>
bool HashTable<K,T>::find(K key, T& found) const {
    size_t bucket = keyToBucket(key);
    auto & items = table[bucket];
    for (auto & i : items) {
        if (i.first == key) {
            found = i.second;
            return true;
        }
    }
    return false;
}

template <class K, class T>
bool HashTable<K,T>::insert(K key, const T& value) {
    size_t bucket = keyToBucket(key);
    for (auto& x : table[bucket]) {
        if (x.first == key) { return false; }  // don't allow duplicates
    }
    table[bucket].push_back({key,value});
    ++numItems;
    float lf = static_cast<float>(numItems) / numBuckets;
    if (lf > max_lf) rehash(numBuckets * 2 + 1);
    return true;
}

template <class K, class T>
bool HashTable<K,T>::erase(const K& key, T& removed) {
    size_t bucket = keyToBucket(key);
    auto& items = table[bucket];
    for (auto i{items.begin()}; i != items.end(); ++i) {
        if (i->first == key) {
            removed = i->second;
            items.erase(i);
            --numItems;
            return true;
        }
    }
    return false;
}


#endif //ECE309_SPR23_STREETMAP_HASHTABLE_H
