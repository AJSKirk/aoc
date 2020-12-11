#include <stdlib.h>

struct node {
	int val;
	struct node *left,  *right;
};

struct node* search(struct node *root, int target) {
	if (root == NULL || root->val == target) {
		return root;
	} else if (target > root->val) { // Traverse left
		return search(root->right, target);
	} else {
		return search(root->left, target);
	}
}

struct node* new_node(int val) {
	struct node *ptr;
	ptr = malloc(sizeof(struct node));
	ptr->val = val;
	ptr->left = NULL;
	ptr->right = NULL;

	return ptr;
}

struct node* insert(struct node *root, int val) {
	if (root == NULL) {
		return new_node(val);
	} else if (val > root->val) {
		root->right = insert(root->right, val);
	} else {
		root->left = insert(root->left, val);
	}
	return root;
}



