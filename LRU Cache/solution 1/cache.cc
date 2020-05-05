#include <iostream>
#include <queue>
#include <unordered_map>

#include "cache.h"

struct Key {
    int32_t id;
    uint64_t weightage;
    Key(int32_t id, uint64_t weightage=1) : id(id), weightage(weightage) {};
    bool operator<(const Key &other) const { return weightage > other.weightage;}
    size_t operator()(const Key& tr) const {
        return std::hash<int32_t>()(tr.id);
    }
};

struct THash {
    size_t operator()(const Key& tr) const {
        return std::hash<int32_t>()(tr.id);
    }
};

struct TEqual {
    bool operator()(const Key& tr1, const Key& tr2) const {
        if (tr1.id == tr2.id) return true;
        return false;
    }
};

struct PimpCache {
    uint64_t capacity;
    uint64_t time_ticker;
    std::unordered_map<Key, int32_t, THash, TEqual> map_keys;
    std::priority_queue<Key> lru_min_heap;
    PimpCache(uint64_t cache_size=1) : capacity(cache_size), time_ticker(0){}
};

Cache::Cache(const uint64_t cache_size) : m_pimp(std::make_shared<PimpCache>(cache_size)) {}

Cache::~Cache(){}

void Cache::RehashPriorityQueue()
{
    m_pimp->lru_min_heap = std::priority_queue<Key>(); // clear lru_min_heap
    for (auto &&iter : m_pimp->map_keys) m_pimp->lru_min_heap.emplace(iter.first); // rehash lru_min_heap
}

void Cache::Set(int32_t key, int32_t value) { // sets a new key-val of reset key-value
    m_pimp->time_ticker++; // increments time

    auto _key = Key(key, m_pimp->time_ticker); // create a new key
    auto find_key = m_pimp->map_keys.find(_key); // check if it is already there or not

    if(m_pimp->capacity) m_pimp->capacity--; // only add if there is capacity in the cache to do so
    else if(find_key == m_pimp->map_keys.end()) // capacity full need to remove lru element - if it is not is map
    { // edge case check: if the element is not a new append but an update, then don't proceed
        auto lru = m_pimp->lru_min_heap.top(); m_pimp->lru_min_heap.pop(); // find lru from heap and remove it

        auto find_key_lru = m_pimp->map_keys.find(lru); // find lru from map and remove it
        if(find_key_lru != m_pimp->map_keys.end()) m_pimp->map_keys.erase(find_key_lru);
    }

    if(find_key != m_pimp->map_keys.end()) // now if the new key already there remove it and update priority queue
    {
        m_pimp->map_keys.erase(find_key);
        RehashPriorityQueue();
    }

    m_pimp->map_keys.emplace(_key, value); // finally add the key in 2 DS
    m_pimp->lru_min_heap.emplace(_key);
}

int32_t Cache::Get(int32_t key) { // get a key-value
    m_pimp->time_ticker++; // increments time
    int ret = 0;

    auto _key = Key(key, m_pimp->time_ticker); // create key again, time_ticker need to be updated
    auto find_key = m_pimp->map_keys.find(_key);
    if(find_key != m_pimp->map_keys.end()) { // check key is there or not
        ret = find_key->second; // get the existing value to return
        m_pimp->map_keys.erase(find_key); // remove it

        RehashPriorityQueue(); // rehash priority queue
        
        m_pimp->map_keys.emplace(_key, ret); // finally add the key in 2 DS
        m_pimp->lru_min_heap.emplace(_key);
    }
    else
    {
        std::cout<<"None "; // Keys not found
    }

    return ret;
}
