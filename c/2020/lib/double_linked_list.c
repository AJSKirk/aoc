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

struct list_meta *list_create(void) {
	struct list_meta *l = malloc(sizeof(struct list_meta));
	l->head = l->tail = NULL;
	l->length = 0;
	return l;
}

void push_head(struct list_meta *list, NODE_TYPE val) {
	struct node *new_node = malloc(sizeof(struct node));
	new_node->value = val;
	new_node->next = list->head;
	new_node->prev = NULL;
	if (list->length == 0) {
		list->tail = new_node;
	} else {
		list->head->prev = new_node;
	}
	list->length++;
	list->head = new_node;
}

void push_tail(struct list_meta *list, NODE_TYPE val) {
	struct node *new_node = malloc(sizeof(struct node));
	new_node->value = val;
	new_node->prev = list->tail;
	new_node->next = NULL;
	if (list->length == 0) {
		list->head = new_node;
	} else {
		list->tail->next = new_node;
	}
	list->length++;
	list->tail = new_node;
}

NODE_TYPE peek_head(struct list_meta *list){
	return list->head->value;
}

NODE_TYPE peek_tail(struct list_meta *list){
	return list->tail->value;
}

NODE_TYPE pop_head(struct list_meta *list) {
	if (list->length == 0)
		return 0;
	NODE_TYPE v = list->head->value;
	struct node *orphan_loc = list->head;
	if (list->length > 1)
		list->head->next->prev = NULL;
	list->head = orphan_loc->next;
	list->length--;
	free(orphan_loc);
	return v;
}

NODE_TYPE pop_tail(struct list_meta *list) {
	if (list->length == 0)
		return 0;
	NODE_TYPE v = list->tail->value;
	struct node *orphan_loc = list->tail;
	if (list->length > 1)
		list->tail->prev->next = NULL;
	list->tail = orphan_loc->prev;
	list->length--;
	free(orphan_loc);
	return v;
}

NODE_TYPE *to_array(struct list_meta *list) {
	NODE_TYPE *arr = malloc(list->length * sizeof(NODE_TYPE));
	int i = 0;
	struct node *current;
	for (current=list->head; current!=NULL; current=current->next) {
		arr[i++] = current->value;
	}
	return arr;
}
