# LRU Cache Simulator

A console-based **Least Recently Used (LRU) Cache** implementation in C++17.

---

## What is an LRU Cache?

An LRU Cache is a fixed-size data structure that stores key-value pairs. When the cache is full and a new entry needs to be inserted, the **least recently used** entry is automatically evicted.

**Real-world usage:**
- Operating system page caches
- Web browser caches
- Database query caches
- CDN (Content Delivery Network) caches

### How it works

```
HashMap (unordered_map)          Doubly Linked List
┌────────┬──────────┐
│  key   │  Node*   │──────►   HEAD ←→ A ←→ B ←→ C ←→ TAIL
├────────┼──────────┤          (MRU)                   (LRU)
│   1    │  ptr_A   │
│   2    │  ptr_B   │          • GET/PUT moves node to HEAD
│   3    │  ptr_C   │          • Eviction removes node at TAIL
└────────┴──────────┘
```

- **HashMap** gives O(1) lookup by key.
- **Doubly Linked List** maintains access order and allows O(1) insert/remove.
- Combined, both `get()` and `put()` run in **O(1) time**.

---

## Project Structure

```
lru-cache/
├── src/
│   ├── main.cpp          # Console interface (demo + interactive)
│   └── LRUCache.cpp      # Cache implementation
├── include/
│   └── LRUCache.h        # Cache header with data structure overview
└── README.md             # This file
```

---

## How to Compile

Using **g++** (requires C++17 support):

```bash
g++ -std=c++17 -Iinclude src/main.cpp src/LRUCache.cpp -o lru
```

On Windows:
```cmd
g++ -std=c++17 -Iinclude src\main.cpp src\LRUCache.cpp -o lru.exe
```

---

## How to Run

```bash
./lru          # Linux / macOS
lru.exe        # Windows
```

You will be prompted to choose:
1. **Demo mode** — runs a pre-built sequence showing hits, misses, and evictions.
2. **Interactive mode** — type commands manually.

---

## Commands (Interactive Mode)

| Command            | Description                          |
|--------------------|--------------------------------------|
| `PUT <key> <value>`| Insert or update an entry            |
| `GET <key>`        | Look up a value (returns -1 if miss) |
| `DISPLAY`          | Show cache contents (MRU → LRU)      |
| `STATS`            | Show hit/miss/eviction statistics    |
| `HELP`             | Show available commands              |
| `EXIT`             | Quit the program                     |

---

## Example Session

```
Cache capacity: 3

lru> PUT 1 100
  -> Inserted: key=1, value=100
  Cache state (MRU -> LRU):
  [1:100]

lru> PUT 2 200
  -> Inserted: key=2, value=200
  Cache state (MRU -> LRU):
  [2:200] [1:100]

lru> PUT 3 300
  -> Inserted: key=3, value=300
  Cache state (MRU -> LRU):
  [3:300] [2:200] [1:100]

lru> GET 1
  -> Cache HIT : key=1, value=100
  Cache state (MRU -> LRU):
  [1:100] [3:300] [2:200]

lru> PUT 4 400
  -> Evicted: key=2, value=200
  -> Inserted: key=4, value=400
  Cache state (MRU -> LRU):
  [4:400] [1:100] [3:300]

lru> STATS
  ┌─────────────────────────────┐
  │      Cache Statistics        │
  ├─────────────────────────────┤
  │  Total GETs   :          1 │
  │  Cache Hits   :          1 │
  │  Cache Misses :          0 │
  │  Evictions    :          1 │
  │  Hit Ratio    :    100.0%  │
  └─────────────────────────────┘
```

---

## Key Concepts for Students

| Concept                | Where to find it             |
|------------------------|------------------------------|
| Doubly Linked List     | `LRUCache.h`, `LRUCache.cpp`|
| HashMap (unordered_map)| `LRUCache.h`                |
| O(1) time complexity   | Comments in `LRUCache.cpp`   |
| Sentinel nodes pattern | Constructor in `LRUCache.cpp`|
| Cache eviction policy  | `evictTail()` in `LRUCache.cpp`|
