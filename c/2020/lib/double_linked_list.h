#include <stdio.h>
#include <stdlib.h>

#define NODE_TYPE int

struct node {
	NODE_TYPE value;
	struct node *next;
	struct node *prev;

};

struct list_meta {
	struct node *head;
	struct node *tail;
	int length;
};

struct list_meta *list_create(void);
void push_head(struct list_meta *list, NODE_TYPE val);
void push_tail(struct list_meta *list, NODE_TYPE val);
NODE_TYPE peek_head(struct list_meta *list);
NODE_TYPE peek_tail(struct list_meta *list);
NODE_TYPE pop_head(struct list_meta *list);
NODE_TYPE pop_tail(struct list_meta *list);
NODE_TYPE *to_array(struct list_meta *list);
