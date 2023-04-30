#include <cstring>

#define TABLE_SIZE 100000

using namespace std;

class HashMapNode
{
public:
    char *key;
    int value;
    HashMapNode *next;
    HashMapNode()
    {
        key = nullptr;
        value = 0;
        next = nullptr;
    }
    HashMapNode(char *key, int value)
    {
        this->key = new char[strlen(key) + 1];
        this->key = strcpy(this->key, key);
        this->value = value;
        this->next = nullptr;
    }
};

class HashMap
{
    HashMapNode **table;

    unsigned int hash(const char *str) // djb2 hash function
    {
        unsigned long hash = 5381;
        int c;
        while ((c = *str++))
        {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash % TABLE_SIZE;
    }

public:
    HashMap()
    {
        table = new HashMapNode *[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            table[i] = nullptr;
        }
    }
    void insert(char *key, int value)
    {
        int hashVal = hash(key);
        HashMapNode *currentNode = table[hashVal];
        while (currentNode != nullptr)
        {
            if (strcmp(currentNode->key, key) == 0)
            {
                currentNode->value = value;
                return;
            }
            currentNode = currentNode->next;
        }
        HashMapNode *newNode = new HashMapNode(key, value);
        newNode->next = table[hashVal];
        table[hashVal] = newNode;
    }
    int get(char *key)
    {
        int hashVal = hash(key);
        HashMapNode *currentNode = table[hashVal];
        while (currentNode != nullptr)
        {
            if (strcmp(currentNode->key, key) == 0)
            {
                return currentNode->value;
            }
            currentNode = currentNode->next;
        }
        return -1;
    }
};