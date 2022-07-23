#include <iostream>
#include "graph.h"
#include "stk_que.h"
using namespace std;


void stack_push(node** st, int n) {
	node* x = (node*)malloc(sizeof(node));
	x->value = n;
	x->next = *st;
	*st = x;
}

int stack_pop(node** st) {
	if (!(*st)) return NULL;
	node* x =  (*st)->next;
	node* y = *st;
	int n = y->value;
	if (!x) *st = NULL;
	else {
		while (x) {
			y->value = x->value;
			if (!x->next) {
				free(y->next);
				y->next = NULL;
				break;
			}
			y = x;
			x = x->next;
		}
	}
	return n;
}

void stack_free(node* st) {
	node* x;
	while (st != NULL) {
		x = st->next;
		free(st);
		st = x;
	}
}

void queue_push(node** q, int n) {
	if (!(*q)) {
		node* x = (node*)malloc(sizeof(node));
		x->value = n;
		x->next = NULL;
		*q = x;
	}
	else {
		node* x = *q;
		while (x->next != NULL) {
			x = x->next;
		}
		x->next = (node*)malloc(sizeof(node));
		x->next->value = n;
		x->next->next = NULL;
	}
}

int queue_pop(node** q) {
	if (!q) return NULL;
	node* x =  (*q)->next;
	node* y = *q;
	int n = y->value;
	if (!x) *q = NULL;
	else {
		while (x) {
			y->value = x->value;
			if (!x->next) {
				free(y->next);
				y->next = NULL;
				break;
			}
			y = x;
			x = x->next;
		}
	}
	return n;
}

void queue_free(node* q) {
	node* x;
	while (q != NULL) {
		x = q->next;
		free(q);
		q = x;
	}
}

int* dfs_bipartite_check(graph* g) {
	int n = g->count;
	node* stack = (node*)malloc(sizeof(node));
	stack = NULL;
	int* colors = (int*)calloc(n, sizeof(int));
	for (int i = 0; i < n; i++) {
		if (!colors[i]) {
			colors[i] = 1;
			stack_push(&stack, i);
			while (stack) {
				int a = stack_pop(&stack);
				node* x = g->adj_list[a].head;
				while (x) {
					if (!colors[x->value]) {
						if (colors[a] == 1) colors[x->value] = 2;
						else colors[x->value] = 1;
						stack_push(&stack, x->value);
					}
					else if (colors[x->value] == colors[a]) {
						stack_free(stack);
						free(colors);
						return NULL;
					}
					x = x->next;
				}
			}
		}
	}
	stack_free(stack);
	return colors;
}

int* bfs_bipartite_check(graph* g) {
	int n = g->count;
	node* queue = (node*)malloc(sizeof(node));
	queue = NULL;
	int* colors = (int*)calloc(n, sizeof(int));
	for (int i = 0; i < n; i++) {
		if (!colors[i]) {
			colors[i] = 1;
			queue_push(&queue, i);
			while (queue) {
				int a = queue_pop(&queue);
				node* x = g->adj_list[a].head;
				while (x) {
					if (!colors[x->value]) {
						if (colors[a] == 1) colors[x->value] = 2;
						else colors[x->value] = 1;
						queue_push(&queue, x->value);
					}
					else if (colors[x->value] == colors[a]) {
						queue_free(queue);
						free(colors);
						return 0;
					}
					x = x->next;
				}
			}
		}
	}
	queue_free(queue);
	return colors;
}