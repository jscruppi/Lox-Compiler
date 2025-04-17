#include "HashSet.h"

// Hash function (djb2)
unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    return hash;
}

// Initialize a new hash set
HashSet* createHashSet() {
    HashSet *set = malloc(sizeof(HashSet));
    set->capacity = INITIAL_CAPACITY;
    set->size = 0;
    set->buckets = calloc(set->capacity, sizeof(Node*));
    return set;
}

// Resize the hash table when load factor is exceeded
void resize(HashSet *set) {
    int new_capacity = set->capacity * 2;
    Node **new_buckets = calloc(new_capacity, sizeof(Node*));

    // Rehash all elements
    for (int i = 0; i < set->capacity; i++) {
        Node *current = set->buckets[i];
        while (current != NULL) {
            Node *next = current->next;
            unsigned long idx = hash(current->key) % new_capacity;
            current->next = new_buckets[idx];
            new_buckets[idx] = current;
            current = next;
        }
    }

    free(set->buckets);
    set->buckets = new_buckets;
    set->capacity = new_capacity;
}

// Insert a key into the set (returns true if newly added)
bool insert(HashSet *set, const char *key) {
    if ((double)set->size / set->capacity >= LOAD_FACTOR) {
        resize(set);
    }

    unsigned long idx = hash(key) % set->capacity;
    Node *current = set->buckets[idx];

    // Check if key already exists
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return false;  // Key already exists
        }
        current = current->next;
    }

    // Add new node
    Node *new_node = malloc(sizeof(Node));
    new_node->key = strdup(key);  // Copy the string
    new_node->next = set->buckets[idx];
    set->buckets[idx] = new_node;
    set->size++;
    return true;
}

// Check if a key exists
bool contains(HashSet *set, const char *key) {
    unsigned long idx = hash(key) % set->capacity;
    Node *current = set->buckets[idx];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Remove a key (returns true if found and removed)
bool removeKey(HashSet *set, const char *key) {
    unsigned long idx = hash(key) % set->capacity;
    Node **current = &set->buckets[idx];
    while (*current != NULL) {
        if (strcmp((*current)->key, key) == 0) {
            Node *to_free = *current;
            *current = (*current)->next;
            free(to_free->key);  // Free the copied string
            free(to_free);
            set->size--;
            return true;
        }
        current = &(*current)->next;
    }
    return false;
}

// Free the entire set
void freeHashSet(HashSet *set) {
    for (int i = 0; i < set->capacity; i++) {
        Node *current = set->buckets[i];
        while (current != NULL) {
            Node *next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
    }
    free(set->buckets);
    free(set);
}