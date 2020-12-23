#include <stdio.h>
#include <stdlib.h>
#include "double_linked_list.h"

#define NODE_TYPE int

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

struct list_meta *copy_list(struct list_meta *src, int depth) {
	struct list_meta *dst = list_create();
	struct node *current;

	for (current=src->head; current!=NULL && depth>0; current=current->next) {
		push_tail(dst, current->value);
		depth--;
	}

	return dst;
}

struct list_meta *slice_after_head(struct list_meta *src, int depth) {
	struct node *current;
	struct list_meta *slice = list_create();

	for (current=src->head->next; current !=NULL && depth>0; current=current->next) {
		src->length--;
		slice->length++;
		depth--;
	}

	slice->head = src->head->next;
	slice->head->prev = NULL;
	slice->tail = current->prev;
	slice->tail->next = NULL;
	src->head->next = current;
	current->prev = src->head;
	return slice;
}

void insert_slice(struct list_meta *list, struct list_meta *slice, struct node *after_node) {
	slice->tail->next = after_node->next;
	if (after_node->next != NULL)
		slice->tail->next->prev = slice->tail;
	else
		list->tail = slice->tail;
	after_node->next = slice->head;
	slice->head->prev = after_node;

	list->length += slice->length;

	free(slice); // No longer need slice metadata
}

void cycle_to_target(struct list_meta *list, NODE_TYPE target) {
	while (list->head->value != target) {
		cycle_fixed(list, 1);
	}
}

void cycle_fixed(struct list_meta *list, int depth) {
	while (depth > 0) {
		list->tail->next = list->head;
		list->head->prev = list->tail;
		list->tail = list->head;
		list->head->next->prev = NULL;
		list->head = list->head->next;
		list->tail->next = NULL;
		depth--;
	}
}

int target_in_list(struct list_meta *list, NODE_TYPE target) {
	struct node *current;
	for (current=list->head; current!=NULL; current=current->next)
		if (current->value == target)
			return 1;
	return 0;
}
