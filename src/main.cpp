

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include "LRUCache.h"

std::string toUpper(const std::string &s)
{
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

void printBanner()
{
    std::cout << "\n";
    std::cout << "============================================\n";
    std::cout << "          LRU Cache Simulator               \n";
    std::cout << "          Interactive Console               \n";
    std::cout << "============================================\n";
    std::cout << "\n";
}

void printHelp()
{
    std::cout << "  Commands:\n";
    std::cout << "    PUT <key> <value>  — Insert or update an entry\n";
    std::cout << "    GET <key>          — Look up a value\n";
    std::cout << "    DISPLAY            — Show cache contents\n";
    std::cout << "    STATS              — Show cache statistics\n";
    std::cout << "    HELP               — Show this message\n";
    std::cout << "    EXIT               — Quit\n\n";
}

void runDemo(LRUCache &cache)
{
    std::cout << "\n--- Running Demo (capacity = 3) ---\n\n";

    std::cout << "> PUT 1 100\n";
    cache.put(1, 100);
    cache.display();

    std::cout << "\n> PUT 2 200\n";
    cache.put(2, 200);
    cache.display();

    std::cout << "\n> PUT 3 300\n";
    cache.put(3, 300);
    cache.display();

    std::cout << "\n> GET 1\n";
    cache.get(1);
    cache.display();

    std::cout << "\n> PUT 4 400\n";
    cache.put(4, 400);
    cache.display();

    std::cout << "\n> GET 2\n";
    cache.get(2);
    cache.display();

    cache.printStats();

    std::cout << "\n--- Demo Complete ---\n\n";
}

void runInteractive(LRUCache &cache)
{
    printHelp();

    std::string line;
    while (true)
    {
        std::cout << "lru> ";
        if (!std::getline(std::cin, line))
            break;

        if (line.empty())
            continue;

        std::istringstream iss(line);
        std::string command;
        iss >> command;
        command = toUpper(command);

        if (command == "PUT")
        {
            int key, value;
            if (!(iss >> key >> value))
            {
                std::cout << "  Usage: PUT <key> <value>\n";
                continue;
            }
            cache.put(key, value);
            cache.display();
        }
        else if (command == "GET")
        {
            int key;
            if (!(iss >> key))
            {
                std::cout << "  Usage: GET <key>\n";
                continue;
            }
            cache.get(key);
            cache.display();
        }
        else if (command == "DISPLAY")
        {
            cache.display();
        }
        else if (command == "STATS")
        {
            cache.printStats();
        }
        else if (command == "HELP")
        {
            printHelp();
        }
        else if (command == "EXIT" || command == "QUIT")
        {
            cache.printStats();
            std::cout << "\nGoodbye!\n";
            break;
        }
        else
        {
            std::cout << "  Unknown command: " << command
                      << "  (type HELP for usage)\n";
        }
    }
}

int main()
{
    printBanner();

    std::cout << "Choose mode:\n";
    std::cout << "  1. Run built-in demo   (capacity = 3)\n";
    std::cout << "  2. Interactive console\n";
    std::cout << "\nYour choice (1 or 2): ";

    int mode;
    std::cin >> mode;
    std::cin.ignore();

    if (mode == 1)
    {
        LRUCache cache(3);
        runDemo(cache);
    }
    else
    {
        int capacity;
        std::cout << "Enter cache capacity: ";
        std::cin >> capacity;
        std::cin.ignore();

        if (capacity <= 0)
        {
            std::cerr << "Error: capacity must be positive.\n";
            return 1;
        }

        LRUCache cache(capacity);
        std::cout << "\nLRU Cache created with capacity " << capacity << ".\n\n";
        runInteractive(cache);
    }

    return 0;
}
