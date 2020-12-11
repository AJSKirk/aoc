struct node {
	int val;
	struct node *left,  *right;
};

struct node* search(struct node *root, int target);
struct node* new_node(int val);
struct node* insert(struct node *root, int val);



