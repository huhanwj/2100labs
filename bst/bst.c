#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;

Node* createTree() {
	// create an example tree at root
	Node* root = (Node*)malloc(sizeof(Node));
	root->key = 6;

	Node* node1 = (Node*)malloc(sizeof(Node));   node1->key = 2;
	node1->left = node1->right = NULL;
	root->left = node1;
	Node* node2 = (Node*)malloc(sizeof(Node));   node2->key = 9;
	root->right = node2;
	node2->left = node2->right = NULL;

	Node* node3 = (Node*)malloc(sizeof(Node));   node3->key = 0;
	node3->left = node3->right = NULL;
	node1->left = node3;
	Node* node4 = (Node*)malloc(sizeof(Node));   node4->key = 3;
	node4->left = node4->right = NULL;
	node1->right = node4;

	Node* node6 = (Node*)malloc(sizeof(Node));   node6->key = 4;
	node6->left = node6->right = NULL;
	node4->right = node6;

	return root;
}


void InOrderTraversal(Node* node) {
	if (node == NULL) return;
	InOrderTraversal(node->left);
	printf("%d", node->key);
	InOrderTraversal(node->right);
}

Node* search(Node * node, int key) {
	// search the tree/subtree headed by "node" for "key"
	if (node == NULL) return NULL;
	if (node->key == key) return node;
	else if (key < node->key) return search(node->left, key);
	else if (key > node->key) return search(node->right, key);
}


void insert(Node * node, int key) {
	// insert the "key" into the right position
	// inside the tree/subtree with "node" as root
	if (node == NULL) return NULL;
	if (key > node->key) {
		if (!node->right) {
			Node* newNode = (Node*)malloc(sizeof(Node));
			newNode->key = key;
			newNode->left = NULL;
			newNode->right = NULL;
			node->right = newNode;
			return;
		}
		else
			return insert(node->right, key);
	}
	else{
		if (!node->left) {
			Node* newNode = (Node*)malloc(sizeof(Node));
			newNode->key = key;
			newNode->left = NULL;
			newNode->right = NULL;
			node->left = newNode;
			return;
		}
		else
			return insert(node->left, key);
	}
}
Node* searchParent(Node* root, Node* children) {
	if (!root || (!root->left && !root->right))	return NULL;
	if (root->left == children || root->right == children)
		return root;
	else {
		Node* turnLeft = NULL;
		Node* turnRight = NULL;
		if (root->left)
			turnLeft = searchParent(root->left, children);
		if (root->right)
			turnRight = searchParent(root->right, children);
		if (turnLeft)
			return turnLeft;
		if (turnRight)
			return turnRight;
		return NULL;
	}
}
Node* delete(Node * root, int key) {
	// delete the "key" without changing the BST
	// rules; also, return the root node after deletion
	// (sometimes the root can be deleted)

	Node* deleteNode = NULL;
	deleteNode = search(root, key);
	if (!deleteNode)	return root;
	else {
		if (!deleteNode->left && !deleteNode->right) {
			Node* parent = searchParent(root, deleteNode);
			if (parent->left == deleteNode)	parent->left = NULL;
			if (parent->right == deleteNode)	parent->right = NULL;
			deleteNode = NULL;
		}
		else if (!deleteNode->left || !deleteNode->right) {
			Node* parent = searchParent(root, deleteNode);
			Node* child = NULL;
			if (deleteNode->left)	child = deleteNode->left;
			if (deleteNode->right)	child = deleteNode->right;
			if (parent->left == deleteNode)	parent->left = child;
			if (parent->right == deleteNode)	parent->right = child;
			deleteNode = NULL;
		}
		else {
			Node* successor = deleteNode->right;
			while (successor->left)
				successor = successor->left;
			deleteNode->key = successor->key;
			Node* successorParent = searchParent(root, successor);
			successorParent->left = NULL;
			successor = NULL;
		}
	}
	return root;
}

int main()
{
	Node* root = NULL;

	root = createTree();
	printf("Original Tree: ");
	InOrderTraversal(root);
	printf("\n");

	// testing search
	int queries[] = { 9,4,1,12 };
	int i;
	for (i = 0; i < 4; i++) {
		Node* result = NULL;
		result = search(root, queries[i]);
		if (result != NULL) printf("%d found!\n", result->key);
		else printf("%d not found!\n", queries[i]);
	}

	// testing insert
	insert(root, 1);
	insert(root, 8);
	insert(root, 7);
	printf("Tree after inserting 1,8,7: ");
	InOrderTraversal(root);
	printf("\n");

	// testing delete
	root = delete(root, 11);
	root = delete(root, 7);
	root = delete(root, 3);
	printf("Tree after deleting 11,7,3: ");
	InOrderTraversal(root);
	printf("\n");
	root = delete(root, 6);
	printf("Tree after deleting 6: ");
	InOrderTraversal(root);
	printf("\n");
	return 0;
}
