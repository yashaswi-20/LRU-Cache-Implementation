

#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <unordered_map>
#include <string>

struct Node
{
    int key;
    int value;
    Node *prev;
    Node *next;

    Node(int k, int v);
};

class LRUCache
{
private:
    int capacity;
    int currentSize;

    Node *head;
    Node *tail;

    std::unordered_map<int, Node *> cache;

    int totalGets;
    int cacheHits;
    int cacheMisses;
    int evictions;

    void addToHead(Node *node);
    void removeNode(Node *node);
    void moveToHead(Node *node);
    Node *evictTail();

public:
    explicit LRUCache(int cap);
    ~LRUCache();

    int get(int key);

    void put(int key, int value);

    void display() const;

    void printStats() const;
};

#endif
