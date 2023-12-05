#ifndef ECE309_SPR23_STREETMAP_HASHTABLE_H
#define ECE309_SPR23_STREETMAP_HASHTABLE_H
#include <list>
#include <vector>

// Hash Table for key K and object T
// Type K must have a defined std::hash<K> and must implement ==
template<class K, class T>
class HashTable {
private:
    using Item = std::pair<K,T>;
public:
    // default constructor: empty hash table, # buckets is optional
    // max. load factor should be initialized to 3.0
    explicit HashTable(size_t buckets=511) {
        numItems = 0;
        numBuckets = buckets;
        maxLoadFactor = 3;
        hashTable.resize(numBuckets);
    }
    // use default copy and move constructors, assignment operators

    // return the number of items stored in the table
    size_t size() const {return numItems;}

    // return the number of buckets used by the hash table
    size_t buckets() const {return numBuckets;}

    // set the maximum load factor (# items per bucket)
    void max_load_factor(float max) {maxLoadFactor = max;}

    // return maximum load factor that is currently enforced for the table
    float max_load_factor() const {return maxLoadFactor;}

    // return true if there are no items stored in the table, false otherwise
    bool empty() const {return numItems == 0;}

    // remove all items from the table (deleting if necessary), resulting in an empty table
    void clear() {
        for (size_t i = 0; i <= numBuckets; i++) {
            if (!hashTable[i].empty()) {
                hashTable[i].clear();
                numItems = 0;
                hashTable.resize(numBuckets);
            }
        }
    }

    // change the number of buckets in the hash table, and relocate items into the correct buckets
    // recommendation is to double the current number of buckets and add +1 (e.g., 511 -> 1023)
    void rehash(size_t buckets) {
        size_t prevNumBuckets = numBuckets;
        numBuckets = buckets;
        std::vector<std::vector<Item>> newHash;
        newHash.resize(numBuckets);
        for (size_t i = 0; i < prevNumBuckets; i++) {
            if (!hashTable[i].empty()) {
                for (size_t j = 0; j < hashTable[i].size(); j++) {
                    Item newItem;
                    newItem = hashTable[i][j];
                    size_t index = hash(newItem.first);
                    newHash[index].push_back(newItem);
                }
            }
        }
        hashTable = std::move(newHash);
    }

    // return true if an item with the specified key is in the table
    // if found, store a copy of the value (type T, not Item) into the found variable
    // if not found, nothing is stored to the found variable
    bool find(K key, T& found) const {
    if (hashTable.size() == 0) return false;
    int index = hash(key);
        for (size_t i = 0; i < hashTable[index].size(); i++) {
            if (key == hashTable[index][i].first) {
                found = hashTable[index][i].second;
                return true;
            }
        }
        return false;
    }

    // insert the value using the specified key
    // return true if the insertion is successful, false otherwise
    // for this assignment, all keys must be unique -- there will never be multiple items with the same key
    bool insert(K key, const T& value) {
    //If the item is already in the table return false
    T v = value;
        if (find(key, v)) return false;
    //If the item is not found in the list, insert it and return true
        Item temp;      // creating a new item object
        temp.first = key;       // setting it's first pair to passsed key
        temp.second = value;    // setting it's second pair to passed value
        size_t thisBucket = hash(key);  // hashing the index
        hashTable[thisBucket].push_back(temp);   //pushing it back into the hashtable
        numItems++;
        float currentLoadFactor = numItems / numBuckets;
        if (currentLoadFactor >= maxLoadFactor){
            size_t newBucketNum = (2*numBuckets) + 1;
            rehash(newBucketNum);
        }
        return true;
    }

    // remove the value using the specified key
    // if found and removed, return true and move/copy the value to the removed parameter
    // if not found, return false
    bool erase(K key, T& removed) {
        size_t index = hash(key);
        int i = 0;
        for (auto it = hashTable[index].begin(); it != hashTable[index].end(); it++) {
            if (key == hashTable[index].at(i).first) {
                removed = hashTable[index].at(i).second;
                hashTable[index].erase(it);
                numItems--;
                return true;
            }
            i++;
        }
        return false;
    }

    // this function is only useful for testing
    // given a key, return the bucket index into which a value would be stored
    size_t keyToBucket(K key) {
        return hash(key);
    }

private:
    // private member variables and member functions
    std::hash<K> hasher;
    size_t hash(K key) const {
        return hasher(key) % numBuckets;
    }
    float numItems;            //Used for size function
    size_t numBuckets;          //used for buckets function
    float maxLoadFactor;
    std::vector<std::vector<Item>> hashTable;
};
#endif //ECE309_SPR23_STREETMAP_HASHTABLE_H
