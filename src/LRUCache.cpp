
#include "LRUCache.h"
#include <iostream>
#include <iomanip>

Node::Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}

LRUCache::LRUCache(int cap)
    : capacity(cap), currentSize(0),
      totalGets(0), cacheHits(0), cacheMisses(0), evictions(0)
{

    head = new Node(0, 0);
    tail = new Node(0, 0);
    head->next = tail;
    tail->prev = head;
}

// Destructor
LRUCache::~LRUCache()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

// addToHead()
void LRUCache::addToHead(Node *node)
{
    node->prev = head;
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
}

void LRUCache::removeNode(Node *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void LRUCache::moveToHead(Node *node)
{
    removeNode(node);
    addToHead(node);
}

Node *LRUCache::evictTail()
{
    Node *lruNode = tail->prev;
    removeNode(lruNode);
    return lruNode;
}

int LRUCache::get(int key)
{
    totalGets++;

    auto it = cache.find(key);
    if (it == cache.end())
    {
        // Cache MISS
        cacheMisses++;
        std::cout << "  -> Cache MISS (key " << key << " not found)\n";
        return -1;
    }

    // Cache HIT — move to head and return the value
    cacheHits++;
    Node *node = it->second;
    moveToHead(node);
    std::cout << "  -> Cache HIT : key=" << key
              << ", value=" << node->value << "\n";
    return node->value;
}

void LRUCache::put(int key, int value)
{
    auto it = cache.find(key);

    if (it != cache.end())
    {
        // Key exists — update value and move to head
        Node *node = it->second;
        node->value = value;
        moveToHead(node);
        std::cout << "  -> Updated: key=" << key
                  << ", value=" << value << "\n";
        return;
    }

    // Key is new — check if we need to evict
    if (currentSize >= capacity)
    {
        Node *lruNode = evictTail();
        std::cout << "  -> Evicted: key=" << lruNode->key
                  << ", value=" << lruNode->value << "\n";

        cache.erase(lruNode->key);
        delete lruNode;
        currentSize--;
        evictions++;
    }

    // Create and insert the new node
    Node *newNode = new Node(key, value);
    addToHead(newNode);
    cache[key] = newNode;
    currentSize++;

    std::cout << "  -> Inserted: key=" << key
              << ", value=" << value << "\n";
}

void LRUCache::display() const
{
    std::cout << "\n  Cache state (MRU -> LRU):\n  ";

    if (currentSize == 0)
    {
        std::cout << "(empty)\n";
        return;
    }

    Node *current = head->next;
    while (current != tail)
    {
        std::cout << "[" << current->key << ":" << current->value << "] ";
        current = current->next;
    }
    std::cout << "\n";
}

void LRUCache::printStats() const
{
    std::cout << "\n  ---------------------------------\n";
    std::cout << "  |      Cache Statistics         |\n";
    std::cout << "  ---------------------------------\n";
    std::cout << "  |  Total GETs   : " << std::setw(10) << totalGets << " |\n";
    std::cout << "  |  Cache Hits   : " << std::setw(10) << cacheHits << " |\n";
    std::cout << "  |  Cache Misses : " << std::setw(10) << cacheMisses << " |\n";
    std::cout << "  |  Evictions    : " << std::setw(10) << evictions << " |\n";

    if (totalGets > 0)
    {
        double hitRatio = static_cast<double>(cacheHits) / totalGets * 100.0;
        std::cout << "  |  Hit Ratio    : " << std::setw(8) << std::fixed
                  << std::setprecision(1) << hitRatio << "%" << " |\n";
    }
    else
    {
        std::cout << "  |  Hit Ratio    :        N/A |\n";
    }

    std::cout << "  ---------------------------------\n";
}
