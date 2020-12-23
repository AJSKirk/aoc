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
struct list_meta *copy_list(struct list_meta *src, int depth);
struct list_meta *slice_after_head(struct list_meta *src, int depth);
void insert_slice(struct list_meta *list, struct list_meta *slice, NODE_TYPE after);
void cycle_to_target(struct list_meta *list, NODE_TYPE target);
void cycle_fixed(struct list_meta *list, int depth);
int target_in_list(struct list_meta *list, NODE_TYPE target);
