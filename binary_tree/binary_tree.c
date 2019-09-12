#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char key;
	struct node* left;
	struct node* right;
} Node;

Node* createTree() {
	// create an example tree at root
	Node* root = (Node*)malloc(sizeof(Node));
	root->key = '*';

	Node* node1 = (Node*)malloc(sizeof(Node));   node1->key = '3';
	node1->left = node1->right = NULL;
	root->left = node1;
	Node* node2 = (Node*)malloc(sizeof(Node));   node2->key = '-';
	node2->left = node2->right = NULL;
	root->right = node2;

	Node* node3 = (Node*)malloc(sizeof(Node));   node3->key = '*';
	node3->left = node3->right = NULL;
	node2->left = node3;
	Node* node4 = (Node*)malloc(sizeof(Node));   node4->key = '1';
	node4->left = node4->right = NULL;
	node2->right = node4;

	Node* node5 = (Node*)malloc(sizeof(Node));   node5->key = '2';
	node5->left = node5->right = NULL;
	node3->left = node5;
	Node* node6 = (Node*)malloc(sizeof(Node));   node6->key = '4';
	node6->left = node6->right = NULL;
	node3->right = node6;

	return root;
}

void InOrderTraversal(Node* node) {
	if (!node) return;
	if (node->left != NULL) {
		printf("(");
		InOrderTraversal(node->left);
	}
	printf("%c", node->key);
	if (node->right != NULL) {
		InOrderTraversal(node->right);
		printf(")");
	}
}

void PreOrderTraversal(Node * node) {
	if (node == NULL)	return;
	if (node->key == '+')
		printf("add(");
	else if (node->key == '-')
		printf("sub(");
	else if (node->key == '*')
		printf("mul(");
	else if (node->key == '/')
		printf("div(");
	else
		printf("%c", node->key);
	if (node->left) {
		PreOrderTraversal(node->left);
		printf(",");
	}
	if (node->right) {
		PreOrderTraversal(node->right);
		printf(")");
	}
}

void PostOrderTraversal(Node * node) {
	if (node == NULL)	return;
	PostOrderTraversal(node->left);
	PostOrderTraversal(node->right);
	printf("%c", node->key);
}

int main()
{
	Node* root = NULL;

	root = createTree();
	printf("In-order: ");
	InOrderTraversal(root);
	printf("\nPre-order: ");
	PreOrderTraversal(root);
	printf("\nPost-order: ");
	PostOrderTraversal(root);
	printf("\n");


	return 0;
}
