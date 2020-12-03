#include <stdio.h>
#include <stdlib.h>

#define NODE_TYPE char

struct node {
	NODE_TYPE value;
	struct node *next;
};

struct list_meta {
	struct node *head;
	struct node *tail;
	int length;
};

void traverse(struct node *first) {
	struct node *current;
	for(current=first; current!=NULL; current=current->next) {
		continue;
	}
}

void append_head(struct list_meta *list, struct node *new) {
	new->next = list->head;
	list->head = new;
}

void append_tail(struct list_meta *list, struct node *new) {
	list->tail->next = new;
	list->tail = new;
}

