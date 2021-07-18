#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "hash.h"

/* Implementation of hash table with separate chaining */

struct hashTable {
	int tableSize;
	int currentSize;
	struct node ** table;
};

struct node {
	char * key;
	struct node * next;
};

#define INITIAL_SIZE (1024)
#define RESIZE_FACTOR (2)
#define MAX_LOAD_FACTOR (1.0)

// creates new hash table
HashTable
createHashTable(void){

	HashTable h = malloc(sizeof(struct hashTable));
	assert(h);
	h->tableSize = INITIAL_SIZE;
	h->currentSize = 0;
	h->table = calloc(INITIAL_SIZE, sizeof(struct node *));
	assert(h->table);

	return h;
}

// frees a linked list, given its head
void freeList(struct node * head){
	struct node * tmp;
	while(head){
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

// frees hash table
void
freeHashTable(HashTable h){
	// free each list
	for(int i = 0; i < h->tableSize; i++){
		if(h->table[i] != 0){
			// free list
			freeList(h->table[i]);
		}
	}
	// free the table
	free(h->table);
	// free the hash table
	free(h);
}

// find a string in a linked list
// returns pointer to that node
Position
findStringInList(char * str, struct node * head){
	
	if(!head) return 0;

	if(strcmp(str, head->key) == 0)
		return head;
	
	return findStringInList(str, head->next);
}

// finds string in hash table
// returns pointer to that node (or 0 if not found)
Position
findString(char * str, HashTable h){

	int  hashVal = hash(str) % h->tableSize;

	if(h->table[hashVal] != 0)
		return findStringInList(str, h->table[hashVal]);
	else
		return 0;
}

// inserts into hash table
void
insert(char * str, HashTable h){

	int hashVal = hash(str) % h->tableSize;

	if(findStringInList(str, h->table[hashVal]) == 0){
		// str is not found in table
		// create new node, insert it to front of list
		struct node * newNode = malloc(sizeof(struct node));
		newNode->key = str;
		newNode->next = h->table[hashVal];
		h->table[hashVal] = newNode;
		// update sizes
		h->currentSize += 1;
		// check if rehashing is needed
		if(h->currentSize >= h->tableSize * MAX_LOAD_FACTOR)
			rehash(h);
	}
}

// deletes from hash table
// returns deleted string
char *
delete(char * str, HashTable h){

	int hashVal = hash(str) % h->tableSize;

	struct node * target = findStringInList(str, h->table[hashVal]);
	
	// if string is not in hash table
	if(target == 0) return 0;

	// else
	h->table[hashVal] = target->next;
	free(target);
	return str;
}

/* Three multiplication hash function:
 * 	1) computation of polynomial
 * 	2) FNV-1
 * 	3) FNV-1a
 * All three essentially follow the same logic: applying 
 * multiplication (or bit shift) and addition (or XOR) on
 * each byte of the string.
 */

// compute polynomial using Horner's algorithm
uint64_t hashMulti(char * str){
	uint64_t hashVal = 0;
	while(*str != '\0'){
		hashVal += (hashVal << 5) + *str;	
		// <<5 is multiply by 32 but faster
		// can also replace addition with XOR to make it faster
		str++;
	}
	return hashVal;
}

#define FNV_PRIME ((1ULL<<40)+(1<<8)+0xb3)		// 1099511628211
#define FNV_OFFSET_BASIS (14695981039346656037ULL)

// FNV-1
uint64_t hashFNV1(unsigned char * str){
	uint64_t hashVal = FNV_OFFSET_BASIS;
	while(*str != '\0'){
		hashVal *= FNV_PRIME;		// multiplication first
		hashVal ^= *str;		// then XOR
		str++;
	}
	return hashVal;
}

// FNV-1a
uint64_t hashFNV1a(unsigned char * str){
	uint64_t hashVal = FNV_OFFSET_BASIS;
	while(*str != '\0'){
		hashVal ^= *str;		// XOR first
		hashVal *= FNV_PRIME;		// then multiplication
		str++;
	}
	return hashVal;
}

// hash function
uint64_t hash(char * str){
	// use FNV-1a
	return hashFNV1a((unsigned char *) str);
}	

// rehash (resizing)
void rehash(HashTable h){

	int oldSize = h->tableSize;
	h->tableSize *= RESIZE_FACTOR;
	h->currentSize = 0;
	struct node ** oldTable = h->table;

	// new table
	h->table = calloc(h->tableSize, sizeof(struct node *));

	// copy items into new table
	for(int i = 0; i < oldSize; i++){
		struct node * curr = h->table[i];
		struct node * tmp;
		while(curr){
			insert(curr->key, h);
			tmp = curr->next;
			free(curr);
			curr = tmp;
		}
	}

	free(oldTable);
}			

// prints values of hash table
void
printHashTable(HashTable h){
	for(int i = 0; i < h->tableSize; i++){
		struct node * curr = h->table[i];
		while(curr){
			puts(curr->key);
			curr = curr->next;
		}
	}
}
