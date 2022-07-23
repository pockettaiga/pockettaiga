#include <iostream>
#include <stdio.h>
#define IS_DIGIT(x)  (x >= '0' && x <= '9')
#define IS_SIGN(x)   (x == '-' || x == '+')

  
typedef struct tree {
	int weight;
	tree* left;
	tree* right;
} tree;


typedef struct sbt {
	int top;
	int bot;
	sbt* left;
	sbt* right;
} sbt;


typedef struct sbf {
	int left_top;
	int left_bot;
	int right_top;
	int right_bot;
} sbf;


void bin_tree_free(tree* t) {
	tree* r = t->right;
	tree* l = t->left;
	free(t);
	if (r) {
		bin_tree_free(r);
	}
	if (l) {
		bin_tree_free(l);
	}
	return;
}


tree* bin_tree_create(int n) {
	tree* result = (tree*)malloc(sizeof(tree));
	if(result) {
		result->weight = n;
		result->left = NULL;
		result->right = NULL;
	}
	return result;
}


tree* bin_tree_add(tree* t, int n){
	tree* x = t;
	while (x) {
		if (n >= x->weight) {
			if (x->right == NULL) {
				x->right = bin_tree_create(n);
				break;
			}
			x = x->right;
		}
		else {
			if (x->left == NULL) {
				x->left = bin_tree_create(n);
				break;
			}
			x = x->left;
		}
	}
	return t;
}


tree* bin_tree_build(const char* str) {
	char* s = (char*)str;
	int n = strtol(s, &s, 10);
	tree* result = bin_tree_create(n);
	while (*s != '\0') {
		if (IS_DIGIT(*s)) {
			n = strtol(s, &s, 10);
			result = bin_tree_add(result, n);
		}
		else {
			s++;
		}
	}
	return result;
}


void tree_print(tree* t) {
	if(t->left) tree_print(t->left);
	printf(" %d ", t->weight);
	if (t->right) tree_print(t->right);
}


int* get_array(tree* t, int* N, int* i) {
	if (t->left) N = get_array(t->left, N, i);
	N[*i] = t->weight;
	(*i)++;
	if (t->right) N = get_array(t->right, N, i);
	return N;
}


tree* bin_tree_build_array(int* M, int n) {
	tree* t = bin_tree_create(M[0]);
	for (int i = 1; i < n; i++) {
		t = bin_tree_add(t, M[i]);
	}
	return t;
}


int* bin_array_build(int* M, int n) {
	tree* t = bin_tree_build_array(M, n);
	int* N = (int*) malloc(n*sizeof(int));
	int j = 0;
	get_array(t, N, &j);
	return N;
}


sbf* fraction_create(int lt, int lb, int rt, int rb) {
	sbf* result = (sbf*)malloc(sizeof(sbf));
	result->left_top = lt;
	result->left_bot = lb;
	result->right_top = rt;
	result->right_bot = rb;
	return result;
}


sbt* get_stern_broco_subtree(int n, sbf* f) {
	sbt* result = (sbt*)malloc(sizeof(sbt));
	result->top = f->left_top + f->right_top;
	result->bot = f->left_bot + f->right_bot;
	if (n > 1) {
		result->left = get_stern_broco_subtree(n - 1, fraction_create(f->left_top, f->left_bot, result->top, result->bot));
		result->right = get_stern_broco_subtree(n - 1, fraction_create(result->top, result->bot, f->right_top, f->right_bot));
	}
	else if (n == 1) {
		result->left = NULL;
		result->right = NULL;
	}
	free(f);
	return result;
}


sbt* get_stern_broco_tree(int n) {
	sbf* f = fraction_create(0, 1, 1, 0);
	sbt* result = get_stern_broco_subtree(n, f);
	return result;
}


char* sb_number(double r, sbt* tree, int length) {
	sbt* x = tree;
	double y;
	char* s = (char*)malloc(sizeof(char)* (length+1));
	int i = 0;
	while (x && (i < length)) {
		y = ((double)x->top / x->bot);
		printf("%f\n", y);
		if (r > y) {
			s[i++] = 'R';
			x = x->right;
		}
		else {
			s[i++] = 'L';
			x = x->left;
		}
	}
	if (x) s[length] = '\0';
	else {
		s = (char*)realloc(s, sizeof(char) * i);
		s[i] = '\0';
	}
	return s;
}


int main() {
	/*const char* s = "5 79 33 6";
	tree* t = bin_tree_build(s);
	tree_print(t);
	bin_tree_free(t);*/
	//printf("%d", t->right->left->weight);
	/*int n = 10;
	sbt* st = get_stern_broco_tree(n);
	char* a = sb_number(1.513202102021, st, n);
	printf("%s", a);*/
	int M[] = {5, 79, 33, 6};
	int* p = bin_array_build(M, 4);
	for (int i = 0; i < 4; i++) {
		printf("%d ", p[i]);
	}
}