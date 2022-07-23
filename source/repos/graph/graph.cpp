#include <iostream>
#include "graph.h"
using namespace std;


node* node_create(int n) {
	node* result = (node*)malloc(sizeof(node));
	result->value = n;
	result->next = NULL;
	return result;
}

void add_arc(graph* g, int a, int b) {
	if (a >= g->count || b >= g->count) return;
	node* temp = g->adj_list[a].head;
	if (temp) {
		if (temp->value == b) return;
		while (temp->next) {
			if (temp->next->value == b) {
				return;
			}
			temp = temp->next;
		}
		temp->next = node_create(b);
	}
	else g->adj_list[a].head = node_create(b);
}

void del_arc(graph* g, int a, int b) {
	if (a >= g->count || b >= g->count) return;
	node* temp = g->adj_list[a].head;
	while (temp) {
		if (temp->value == b) {
			if (!temp->next) {
				g->adj_list[a].head = NULL;
			}
			else {
				while (temp->next) {
					temp->value = temp->next->value;
					if (!temp->next->next) {
						temp->next = NULL;
						break;
					}
					temp = temp->next;
				}
			}
			break;
		}
		temp = temp->next;
	}
}

void add_edge(graph* g, int a, int b) {
	add_arc(g, a, b);
	add_arc(g, b, a);
}

void del_edge(graph* g, int a, int b) {
	del_arc(g, a, b);
	del_arc(g, b, a);
}

graph* graph_init(int n) {
	if (n < 1) return NULL;
	graph* result = (graph*)malloc(sizeof(graph));
	result->count = n;
	result->adj_list = (list*)malloc(n * sizeof(node));
	for (int i = 0; i < n; i++) {
		result->adj_list[i].head = NULL;
	}
	return result;
}

void graph_print(graph* g) {
	if (!g) return;
	list* x = g->adj_list;
	for (int i = 0; i < g->count; i++) {
		cout << i;
		node* y = g->adj_list[i].head;
		while (y) {
			cout << "-" << y->value;
			y = y->next;
		}
		cout << "\n";
	}
}

void graph_free(graph* g) {
	if (!g) return;
	list* x = g->adj_list;
	for (int i = 0; i < g->count; i++) {
		node* t = x[i].head;
		while (t) {
			node* p = t;
			t = t->next;
			free(p);
		}
	}
	free(x);
	free(g);
}

graph* graph_input() {
	int n, m;
	cout << "number of nodes: ";
	cin >> n;
	graph* g = graph_init(n);
	cout << "number of arcs: ";
	cin >> m;
	if (!g) {
		cout << "at least 1 node expected";
	}
	else if (m > ((n - 1) * 5 + n)) {
		cout << "too many arcs";
	}
	else {
		int a, b;
		for (int i = 0; i < m; i++) {
			cout << i + 1 << ": ";
			cin >> a >> b;
			add_arc(g, a, b);
		}
		cout << "\n";
		return g;
	}
	return NULL;
}