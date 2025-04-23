#ifndef HASHSET_H
#define HASHSET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 16
#define LOAD_FACTOR 0.75

//! Node struct to represent one part of the HashSet
typedef struct Node {
    char *key; //!< the string literal of the identifer
    struct Node *next; //!< the next node current is pointing to
} Node;

//! Data Structure to represent the root of HashSet
typedef struct {
    Node **buckets; //!< All of the nodes in the HashSet
    int size;       //!< Number of elements
    int capacity;   //!< Number of buckets
} HashSet;

//! Hash function for HashSet
//! @param str The string we a generating a hash value for
//! @return The hash value
unsigned long hash(const char *str);

//! Initalizes an empty pointer with a blank HashSet - pointer takes ownership
//! @return The initalized HashSet
HashSet* createHashSet();

//! Doubles the HashSet's size
//! @param set HashSet to resize
void resize(HashSet *set);

//! Inserts a new string into the HashSet
//! @param set HashSet we are inserting to
//! @param key String key to identify node
//! @return The success of the insertion
bool insert(HashSet *set, const char *key);

//! Checks if a string is in the HashSet
//! @param set HashSet we are searching
//! @param key The string we are searching for
//! @return Weather or not the string was found
bool contains(HashSet *set, const char *key);

//! Removes a string from the HashSet
//! @param set The HashSet we are removing from
//! @param key The string we want to remove
//! @return The sucess of the removal
bool removeKey(HashSet *set, const char *key);

//! Deletes the HashSet from the heap
//! @param set The HashSet to delete
void freeHashSet(HashSet *set);

#endif