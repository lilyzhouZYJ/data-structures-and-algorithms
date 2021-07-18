#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "avlTree.h"

#define INDENTATION (2)

static void
treePrintInternal(Node root, size_t depth)
{
    if(root) {
        // print left subtree
        treePrintInternal(getLeftChild(root), depth+1);

        // print indented root
        for(size_t i = 0; i < depth * INDENTATION; i++) {
            putchar(' ');
        }
        printf("%d\n", getValue(root));

        //print right subtree
        treePrintInternal(getRightChild(root), depth+1);
    }
}

void
treePrint(AvlTree tree)
{
    // internal printer indents by depth
    treePrintInternal(tree, 0);
}

int main()
{
	AvlTree t = createTree();

	printf("inserting: \n");
	t = insert(1, t);
	t = insert(2, t);
	t = insert(3, t);
	t = insert(14, t);
	t = insert(0, t);
	t = insert(-7, t);
	t = insert(8, t);
	t = insert(10, t);
	
	treePrint(t);

	printf("======\n");

	printf("delete 10:\n");
	t = delete(10, t);
	
	treePrint(t);

	printf("======\n");

	printf("delete 2:\n");
	t = delete(2, t);
	
	treePrint(t);

	printf("======\n");

	printf("delete 3:\n");
	t = delete(3, t);
	
	treePrint(t);

	printf("======\n");

	printf("delete 8:\n");
	t = delete(8, t);
	
	treePrint(t);

	printf("======\n");
	printf("Is 2 in tree? %d\n", find(2, t)!=0);

	printf("======\n");
	printf("Is 1 in tree? %d\n", find(1, t)!=0);

	printf("======\n");
	printf("max of current tree: %d\n", getValue(findMax(t)));

	// free space
	// run: valgrind -q --tool=memcheck --leak-check=yes ./my-program
	destroyTree(t);

	return 0;
}
