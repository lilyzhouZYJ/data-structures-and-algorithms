#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "hash.h"

/* Demonstration of hash table with separate chaining */

int
main(int argc, char ** argv){

	// create hash table
	HashTable h = createHashTable();

	// insert into hash table
	insert("hello", h);
	insert("this", h);
	insert("is", h);
	insert("a", h);
	insert("hash", h);
	insert("table",h);

	// print
	printf(" === printing table === \n");
	printHashTable(h);

	// search
	printf(" === searching === \n");
	printf("is \"hash\" in the table? %d\n", findString("hash", h) != 0);
	printf("is \"hello\" in the table? %d\n", findString("hello", h) != 0);
	printf("is \"lily\" in the table? %d\n", findString("lily", h) != 0);
	
	// delete some stuff
	printf(" === deleting \"hash\" === \n");
	printf("Deleting %s\n", delete("hash", h));

	// search again	
	printf(" === searching again === \n");
	printf("is \"hash\" in the table? %d\n", findString("hash", h) != 0);

	// print again
	printf(" === printing table again === \n");
	printHashTable(h);

	// free
	freeHashTable(h);

	return 0;
}	
