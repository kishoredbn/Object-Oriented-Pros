#pragma once

struct Key;
struct THash;
struct TEqual;
struct PimpCache;

class Cache {
private:
    std::shared_ptr<PimpCache> m_pimp;

    void RehashPriorityQueue();

public:
    Cache(const uint64_t cache_size=1);
    ~Cache();
    void Set(int32_t key, int32_t value);
    int32_t Get(int32_t key);
};
