#include <iostream>
#include "graph.h"
#include "stk_que.h"
using namespace std;

#define MIN(x, y) (x <= y) ? x : y

graph* graph_invert(graph* g) {
	graph* result = graph_init(g->count);
	for (int i = 0; i < g->count; i++) {
		node* x = g->adj_list[i].head;
		while (x) {
			add_arc(result, x->value, i);
			x = x->next;
		}
	}
	return result;
}

void order_set(graph* g, int* order, int* visited, int vert) {
	visited[vert] = 1;
	node* x = g->adj_list[vert].head;
	while (x) {
		if (!visited[x->value]) {
			order_set(g, order, visited, x->value);
		}
		x = x->next;
	}
	while (*order) {
		++order;
	}
	*order = vert;
}

void components_find(graph* g, int* visited, int* components, int counter, int vert) {
	visited[vert] = 1;
	components[vert] = counter;
	node* x = g->adj_list[vert].head;
	while (x) {
		if (!visited[x->value]) {
			components_find(g, visited, components, counter, x->value);
		}
		x = x->next;
	}
}

int* scc_kosaraju(graph* g) {
	int n = g->count;
	int* order = (int*)calloc(n, sizeof(int));
	int* visited = (int*)calloc(n, sizeof(int));
	int* components = (int*)calloc(n, sizeof(int));
	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			order_set(g, order, visited, i);
		}
	}
	for (int i = 0; i < n; i++) visited[i] = 0;
	int counter = 0;
	graph* h = graph_invert(g);
	for (int i = 1; i <= n; i++) {
		int a = order[n - i];
		if (!visited[a]) {
			components_find(h, visited, components, counter, a);
			counter++;
		}
	}
	return components;
}


void scc_tarjan_dfs(graph* g, node** stack, int* visited, int* status, int* low, int* components, int vert, int* iter) {
	visited[vert] = (*iter)++;
	status[vert] = 1;
	components[vert] = vert + 1;
	low[vert] = vert + 1;
	node* x = g->adj_list[vert].head;
	while (x) {
		if (!visited[x->value]) {
			stack_push(stack, x->value);
			scc_tarjan_dfs(g, stack, visited, status, low, components, x->value, iter);
		}
		else {
			if (status[x->value] == 1) low[vert] = MIN(low[vert], low[x->value]);
			if (visited[x->value] == low[x->value]) {
				while (*stack) {
					int a = stack_pop(stack);
					status[a] = 2;
					components[a] = low[vert];
					if (a == x->value) break;
				}
			}
		}
		x = x->next;
	}
	return;
}

int* scc_tarjan(graph* g) {
	int n = g->count;
	int iter = 1;
	int* visited = (int*)calloc(n, sizeof(int));
	int* status = (int*)calloc(n, sizeof(int));
	int* low = (int*)calloc(n, sizeof(int));
	int* components = (int*)calloc(n, sizeof(int));
	for (int i = 0; i < n; i++) components[i] = -1;
	node* stack = NULL;
	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			stack_push(&stack, i);
			scc_tarjan_dfs(g, &stack, visited, status, low, components, i, &iter);
		}
	}

	for (int i = 0; i < n; i++) {
		cout << visited[i];
	}
	cout << "<--visited\n";

	free(visited);
	free(low);
	stack_free(stack);
	return components;
}

