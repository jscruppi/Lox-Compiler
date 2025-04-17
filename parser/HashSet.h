#ifndef HASHSET_H
#define HASHSET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 16
#define LOAD_FACTOR 0.75

typedef struct Node {
    char *key;
    struct Node *next;
} Node;

typedef struct {
    Node **buckets;
    int size;      // Number of elements
    int capacity;  // Number of buckets
} HashSet;

unsigned long hash(const char *str);
HashSet* createHashSet();
void resize(HashSet *set);
bool insert(HashSet *set, const char *key);
bool contains(HashSet *set, const char *key);
bool removeKey(HashSet *set, const char *key);
void freeHashSet(HashSet *set);

#endif