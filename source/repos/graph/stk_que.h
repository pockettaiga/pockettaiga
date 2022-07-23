//typedef struct stk {
//	int value;
//	node* prev;
//} stk;

//typedef struct que {
//	int value;
//	node* next;
//} que;

node* node_create(int n);

void stack_push(node** st, int n);
int stack_pop(node** st);
void stack_free(node* st);

void queue_push(node** q, int n);
int queue_pop(node** q);
void queue_free(node* st);