#include <stdio.h>
#include <iostream>
#include <string>
#include "graph.h"
#include "stk_que.h"
using namespace std;

int graph_write(graph* g, const char* path) {
	FILE* f; 
	fopen_s(&f, path, "w");
	if (f) {
		int n = g->count;
		fprintf(f, "%d\n", n);
		for (int i = 0; i < n; i++) {
			fprintf(f, "%d", i);
			node* x = g->adj_list[i].head;
			while (x) {
				fprintf(f, "-%d", x->value);
				x = x->next;
			}
			fputc('\n', f);
		}
		fclose(f);
	}
	else return -1;
	return 0;
}

graph* graph_read(const char* path) {
	FILE* f;
	fopen_s(&f, path, "r");
	graph* g = NULL;
	if (f) {
		int n;
		int vert;
		fscanf_s(f, "%d", &n);
		g = graph_init(n);
		for (int i = 0; i < n; i++) {
			fscanf_s(f, "%d", &vert);
			char c = fgetc(f);
			while (c != '\n' && c != EOF) {
				fscanf_s(f, "%d", &vert);
				add_arc(g, i, vert);
				c = fgetc(f);
			}
		}
	}
	return g;
}

//int main() {
//	int n = 9;
//	graph* g = graph_init(n);
//	add_edge(g, 0, 1);
//	add_edge(g, 0, 2);
//	add_edge(g, 1, 3);
//	add_edge(g, 3, 4);
//	add_edge(g, 4, 5);
//	add_edge(g, 4, 6);
//	add_edge(g, 4, 7);
//	add_edge(g, 7, 8);
//	for (int i = 0; i < 1; i++) {
//		string path = "graph_" + to_string(i) + ".txt";
//		graph_write(g, path.c_str());//"graph_test.txt");
//	}
//	graph_print(graph_read("graph_test.txt"));
//}