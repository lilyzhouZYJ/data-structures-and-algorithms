#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "avlTree.h"

struct treeNode {
	int val;
	struct treeNode * left;		// left child
	struct treeNode * right;	// right child
	int height;					// distance to leaf
};

// creates empty tree
AvlTree
createTree(void){
	return 0;			// just null pointer
}

// frees a tree
void
destroyTree(AvlTree t){

	if(t == 0) return;

	destroyTree(t->left);
	destroyTree(t->right);
	free(t);
}

// find a given target in tree
Node
find(int target, AvlTree t){

	if(t == 0) return 0;

	if(t->val == target)
		// return t
		return t;
	if(t->val > target)
		// go to left child
		return find(target, t->left);
	if(t->val < target)
		// go to right child
		return find(target, t->right);
	
	return 0;
}

// find the minimum node
Node
findMin(AvlTree t){

	while(t && t->left)
		t = t->left;

	return t;
}

// find the maximum node
Node
findMax(AvlTree t){

	while(t && t->right)
		t = t->right;

	return t;
}

// gets the height of a node
int
getHeight(Node n){
	if(n == 0) return -1;
	return n->height;
}

// gets max
static int
max(int a, int b){
	return a > b ? a : b;
}


/*
// single rotation
//           x               y
//          / \             / \
//         A   y     =>    x   C
//            / \         / \
//            B C        A   B
*/
static AvlTree
singleRotate(AvlTree t, int L0R1){

	Node x = t;
	Node y = 0;
	Node B;

	// rotating left
	if(L0R1 == 0){
		y = x->right;
		B = y->left;
		y->left = x;
		x->right = B;
	}

	// rotating right
	if(L0R1 == 1){
		y = x->left;
		B = y->right;
		y->right = x;
		x->left = B;
	}

	// update height
	x->height = max( getHeight(x->left), getHeight(x->right) ) + 1;
	y->height = max( getHeight(y->left), getHeight(y->right) ) + 1;	

	return y;
}



/*
// double rotation
//         x           x            z
//        / \         / \          / \
//       D   y       D   z        x   y
//          / \  =>     / \  =>  / \ / \
//         z  C        A   y     D A B  C
//        / \             / \
//       A   B           B  C
*/
static AvlTree
doubleRotate(AvlTree t, int L0R1){
	// rotating left
	if(L0R1 == 0){
		t->right = singleRotate(t->right, 1);	// single rotate right
		return singleRotate(t, 0);		// single rotate left
	}

	// rotating right
	if(L0R1 == 1){
		t->left = singleRotate(t->left, 0);
		return singleRotate(t, 1);	
	}

	return 0;
}

// insert new value to tree
AvlTree
insert(int value, AvlTree t){

	// base
	if(t == 0){
		// create new node
		t = malloc(sizeof(struct treeNode));
		assert(t);
		t->val = value;
		t->height = 0;
		t->left = 0;
		t->right = 0;
		return t;
	}

	// recursion
	if(value < t->val){
		// insert to left child
		t->left = insert(value, t->left);
		// check balance
		if( getHeight(t->left) - getHeight(t->right) > 1){
			if(value < t->left->val)
				t = singleRotate(t, 1);
			if(value > t->left->val)
				t = doubleRotate(t, 1);
		}
	}
	else if(value > t->val){
		// insert to right child
		t->right = insert(value, t->right);
		// check balance
		if( getHeight(t->right) - getHeight(t->left) > 1){
			if(value > t->right->val)
				t = singleRotate(t, 0);
			if(value < t->right->val)
				t = singleRotate(t, 0);
		}
	}
	// update height of t
	t->height = max( getHeight(t->left), getHeight(t->right) ) + 1;
	
	return t;
}

// delete a node with given value
AvlTree
delete(int value, AvlTree t){

	// if t is empty, do nothing
	if(t == 0) return t;

	if(t->val == value){	// need to delete t
		// does t have no children?
		if(t->left == 0 && t->right == 0){
			free(t);
			return 0;
		}

		// does t have 0 or 1 child?
		else if(t->left == 0 || t->right == 0){
			Node tmp = t->left ? t->left : t->right;
			free(t);
			t = tmp;
		}

		// does t have 2 children?
		else {
			// replace t with minimum of right child
			t->val = getValue(findMin(t->right));
			// remove the minimum node of right child
			t->right = delete(t->val, t->right);
		}
	} else if (t->val < value){
		// go to right child
		t->right = delete(value, t->right);
	} else if (t->val > value){
		// go to left child
		t->left = delete(value, t->left);
	}

	// check balance at t
	int leftH = getHeight(t->left);
	int rightH = getHeight(t->right);
	if(leftH - rightH > 1){
		if(getHeight(t->left->right) > getHeight(t->left->left))
			t = doubleRotate(t, 1);
		else
			t = singleRotate(t, 1);
	} else if (rightH - leftH > 1){
		if(getHeight(t->right->left) > getHeight(t->right->right))
			t = doubleRotate(t, 0);
		else
			t = singleRotate(t, 0);
	}

	// update height of t
	t->height = max( getHeight(t->left), getHeight(t->right) ) + 1;
	
	return t;
}

// return the value of a node
int
getValue(Node n){
	return n->val;
}

// gets the left child of a node
Node
getLeftChild(Node n){
	return n->left;
}

// gets the right child of a node
Node
getRightChild(Node n){
	return n->right;
}