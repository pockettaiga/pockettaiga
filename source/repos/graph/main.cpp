#include <iostream>
#include "graph.h"
using namespace std;

void test_bipartite() {
	int n = 9;
	graph* g = graph_init(n);
	add_edge(g, 0, 1);
	add_edge(g, 0, 2);
	add_edge(g, 1, 3);
	add_edge(g, 3, 4);
	add_edge(g, 4, 5);
	add_edge(g, 4, 6);
	add_edge(g, 4, 7);
	add_edge(g, 7, 8);
	graph_print(g);
	int* colors = dfs_bipartite_check(g);
	cout << "first: ";
	for (int i = 0; i < n; i++) {
		if (colors[i] == 1) {
			cout << i << " ";
		}
	}
	cout << "\nsecond: ";
	for (int i = 0; i < n; i++) {
		if (colors[i] == 2) {
			cout << i << " ";
		}
	}
	cout << "\n";
}

void print_sorted_nodes(graph* g) {
	node* sorted_nodes = topological_sort(g);
	while (sorted_nodes) {
		cout << sorted_nodes->value << " ";
		sorted_nodes = sorted_nodes->next;
	}
}

int main() {
	int n = 8;
	graph* g = graph_init(n);

	/*add_arc(g, 0, 1);
	add_arc(g, 0, 4);
	add_arc(g, 1, 2);
	add_arc(g, 2, 3);
	add_arc(g, 3, 1);
	add_arc(g, 4, 3);*/

	add_arc(g, 0, 1);
	add_arc(g, 1, 2);
	add_arc(g, 1, 4);
	add_arc(g, 1, 5);
	add_arc(g, 2, 3);
	add_arc(g, 2, 6);
	add_arc(g, 3, 2);
	add_arc(g, 3, 7);
	add_arc(g, 4, 0);
	add_arc(g, 4, 5);
	add_arc(g, 5, 6);
	add_arc(g, 6, 5);
	add_arc(g, 7, 3);
	add_arc(g, 7, 6);

	graph_print(g);
	cout << "\n";

	int* components_kos = scc_kosaraju(g);
	for (int i = 0; i < n; i++) {
		cout << components_kos[i];
	}
	cout << "\n";
	
	int* components_tar = scc_tarjan(g);
	for (int i = 0; i < n; i++) {
		cout << components_tar[i];
	}
}