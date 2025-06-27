#ifndef TREEMAP_H
#define TREEMAP_H

#include <iostream>
#include <vector>

#include "KeyValuePair.h"
#include "ScapegoatTree.h"

template<class K, class V>
class TreeMap {
public: // DO NOT CHANGE THIS PART.
    TreeMap();

    void clear();

    const V &get(const K &key) const;

    bool pop(const K &key);

    bool update(const K &key, const V &value);

    const KeyValuePair<K, V> &ceilingEntry(const K &key);

    const KeyValuePair<K, V> &floorEntry(const K &key);

    const KeyValuePair<K, V> &firstEntry();

    const KeyValuePair<K, V> &lastEntry();

    void pollFirstEntry();

    void pollLastEntry();

    std::vector<KeyValuePair<K, V> > subMap(K fromKey, K toKey) const;

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    ScapegoatTree<KeyValuePair<K, V> > stree;
};

template<class K, class V>
TreeMap<K, V>::TreeMap() {}

template<class K, class V>
void TreeMap<K, V>::clear() {
    stree.removeAllNodes();
}

template<class K, class V>
const V &TreeMap<K, V>::get(const K &key) const {
    KeyValuePair<K,V> element(key);
    return(stree.get(element)).getValue();
}

template<class K, class V>
bool TreeMap<K, V>::pop(const K &key) {
    KeyValuePair<K,V> element(key);
    return stree.remove(element);
}

template<class K, class V>
bool TreeMap<K, V>::update(const K &key, const V &value) {
    KeyValuePair<K,V> element(key, value);
    return stree.insert(element);
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::ceilingEntry(const K &key) {
    KeyValuePair<K,V> element(key);
    return stree.getCeiling(element);
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::floorEntry(const K &key) {
    KeyValuePair<K,V> element(key);
    return stree.getFloor(element);
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::firstEntry() {
    return stree.getMin();
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::lastEntry() {
    return stree.getMax();
}

template<class K, class V>
void TreeMap<K, V>::pollFirstEntry() {
    KeyValuePair<K,V> element = firstEntry();
    stree.remove(element);
}

template<class K, class V>
void TreeMap<K, V>::pollLastEntry() {
    KeyValuePair<K,V> element = lastEntry();
    stree.remove(element);
}

template<class K, class V>
std::vector<KeyValuePair<K, V> > TreeMap<K, V>::subMap(K fromKey, K toKey) const {
    std::vector<KeyValuePair<K,V> > result_map;
    KeyValuePair<K,V> element, added_key(fromKey);
    
    while(added_key != toKey)
    {
        element = stree.get(added_key);
        result_map.push_back(element);
        added_key = stree.getNext(element);
    }
    element = stree.get(added_key);
    result_map.push_back(element);
    
    return result_map;
}

template<class K, class V>
void TreeMap<K, V>::print() const {

    std::cout << "# Printing the tree map ..." << std::endl;

    std::cout << "# ScapegoatTree<KeyValuePair<K, V> > stree:" << std::endl;
    stree.printPretty();

    std::cout << "# Printing is done." << std::endl;
}

#endif //TREEMAP_H
