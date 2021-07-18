
/**
 * Hash table with separate chaining
 * Keys are strings
 */

typedef struct hashTable *  HashTable;
typedef struct node * Position;

// creates new hash table
HashTable createHashTable(void);

// frees hash table
void freeHashTable(HashTable h);

// finds string in hash table
// returns pointer to that node
Position findString(char * str, HashTable h);

// inserts into hash table
void insert(char * str, HashTable h);

// deletes from hash table
// returns deleted string
char * delete(char * str, HashTable h);

// hash function
uint64_t hash(char * str);

// rehash (resizing)
void rehash(HashTable h);

// prints values of hash table
void printHashTable(HashTable h);
