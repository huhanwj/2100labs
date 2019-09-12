#include <stdio.h>
#include <stdlib.h>

#define BLACK 0
#define RED 1

typedef struct Node {
	struct Node* left;
	struct Node* right;
	int value;
	int color;
} Node;

Node* search(Node* root, int value) {
	if (root == NULL) {
		return NULL;
	}
	else {
		if (root->value == value) {
			return root;
		}
		if (value < root->value) {
			return search(root->left, value);
		}
		if (value > root->value) {
			return search(root->right, value);
		}
	}
}

Node* insertInBST(Node* root, int value) {
	if (root == NULL) {
		return NULL;
	}
	else {
		if (root->left == NULL && root->right == NULL) {
			Node* newNode = malloc(sizeof(Node));
			newNode->left = NULL;
			newNode->right = NULL;
			newNode->value = value;
			newNode->color = RED;
			if (value < root->value) {
				root->left = newNode;
			}
			else {
				root->right = newNode;
			}
			return newNode;
		}
		else {
			if (value < root->value) {
				return insertInBST(root->left, value);
			}
			else if (value > root->value) {
				return insertInBST(root->right, value);
			}
		}
	}
}

Node* findParent(Node* root, Node* child) {
	if (child == root || child == NULL || root == NULL) {
		return NULL;
	}
	if (root->left == child || root->right == child) {
		return root;
	}
	if (root->value < child->value) {
		return findParent(root->right, child);
	}
	if (root->value > child->value) {
		return findParent(root->left, child);
	}
}

Node* findUncle(Node* root, Node* child) {
	Node* parent = findParent(root, child);
	if (parent == root) {
		return NULL;
	}
	Node* grand = findParent(root, parent);
	if (grand->left == parent) return grand->right;
	if (grand->right == parent) return grand->left;
}

void rotate(Node * root, Node * child) {
	Node* parent = findParent(root, child);
	Node* grand = findParent(root, parent); //can be NULL
	if (parent->right == child) {
		parent->right = child->left;
		child->left = parent;
		if (grand != NULL && grand->left == parent) grand->left = child;
		if (grand != NULL && grand->right == parent) grand->right = child;
	}
	else if (parent->left == child) {
		parent->left = child->right;
		child->right = parent;
		if (grand != NULL && grand->right == parent) grand->right = child;
		if (grand != NULL && grand->left == parent) grand->left = child;
	}
}

Node* insert(Node * root, int value) {
	if (root == NULL) {
		root = malloc(sizeof(Node));
		root->left = NULL;
		root->right = NULL;
		root->value = value;
		root->color = BLACK;
		return root;
	}
	else {
		Node* newNode = insertInBST(root, value);
		Node* parent = findParent(root, newNode);
		Node* uncle = NULL;
		if (parent->color == BLACK) return root;
		uncle = findUncle(root, newNode);
		if (uncle == NULL) return root;
		else {
			if (parent->color == RED && uncle->color == RED) {
				Node* grand = findParent(root, parent);
				grand->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				return root;
			}
			if (parent->color == RED && uncle->color == BLACK) {
				Node* grand = findParent(root, parent);
				if ((grand->left == parent && parent->right == newNode) || (grand->right == parent && parent->left == newNode)) {
					rotate(root, newNode);
					rotate(root, newNode);
					newNode->color = BLACK;
					grand->color = RED;
				}
				else {
					rotate(root, newNode);
					parent->color = BLACK;
					grand->color = RED;
				}
			}
		}
	}
	return root;
}

void printRBT(Node * root) {  //inOrder traversal

	if (root->left != NULL) printRBT(root->left);
	if (root->color == BLACK) printf("R");
	if (root->color == RED) printf("B");
	printf("%d ", root->value);
	if (root->right != NULL) printRBT(root->right);
}

int main() {
	Node* root = NULL;
	root = insert(root, 7);
	root = insert(root, 9);
	root = insert(root, 1);
	printRBT(root);
}


//Best Regards,
//ZHOU, Mingjun

