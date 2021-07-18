
/* AVL Tree */

typedef struct treeNode * AvlTree;
typedef struct treeNode * Node;

// creates empty tree
AvlTree createTree(void);

// frees a tree
void destroyTree(AvlTree t);

// find a given target in tree
Node find(int target, AvlTree t);

// find the minimum node
Node findMin(AvlTree t);

// find the maximum node
Node findMax(AvlTree t);

// insert new value to tree
AvlTree insert(int value, AvlTree t);

// delete a value from tree
AvlTree delete(int value, AvlTree t);

// gets the value of a node
int getValue(Node n);

// gets the height of a node
int getHeight(Node n);

// gets the left child of a node
Node getLeftChild(Node n);

// gets the right child of a node
Node getRightChild(Node n);
