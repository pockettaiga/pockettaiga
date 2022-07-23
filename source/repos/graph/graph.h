typedef struct node {
	int value;
	node* next;
} node;

typedef struct list {
	node* head;
} list;

typedef struct graph {
	int count;
	list* adj_list;
} graph;

graph* graph_input();
graph* graph_init(int n);

void add_arc(graph* g, int a, int b);
void del_arc(graph* g, int a, int b);
void add_edge(graph* g, int a, int b);
void del_edge(graph* g, int a, int b);

void graph_print(graph* g);
void graph_free(graph* g);

int graph_write(graph* g, const char* path);
graph* graph_read(const char* path);

int* dfs_bipartite_check(graph* g);
int* bfs_bipartite_check(graph* g);

node* topological_sort(graph* g);

graph* graph_invert(graph* g);
int* scc_kosaraju(graph* g);
int* scc_tarjan(graph* g);