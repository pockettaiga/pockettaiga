#include <iostream>
#include "graph.h"
#include "stk_que.h"
using namespace std;

node* topological_sort(graph* g) {
	node* result = NULL;
	node* stack = NULL; 
	int n = g->count;
	int* visit = (int*)calloc(n, sizeof(int));
	for (int i = 0; i < n; i++) {
		if (!visit[i]) {
			visit[i] = 1;
			stack_push(&stack, i);
			while (stack) {
				int val = stack->value;
				if (visit[val] == 2) {
					stack_push(&result, stack_pop(&stack));
				}
				else {
					int check_visited = 0;
					node* x = g->adj_list[val].head;
					if (!x) {
						visit[val] = 2;
					}
					while (x) {
						if (!visit[x->value]) {
							check_visited = 1;
							visit[x->value] = 1;
							stack_push(&stack, x->value);
						}
						else if (visit[x->value] == 1) {
							cout << "error: cycle";
							return NULL;
						}
						x = x->next;
					}
					if (!check_visited) visit[val] = 2;
				}
			}
		}
	}
	return result;
}