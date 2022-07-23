#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include "euclidforrpn.h"

#define IS_DIGIT(x) (x >= '0' && x <= '9')
#define IS_SIGN(x)  (x == '-' || x == '+' || x == '*' || x == '/' || x == 'g' || x == 'l' || x == '^' || x == '(' || x == ')')

const int opcount = 9;
const char* OP[opcount] = { "gcd", "lcm", "+", "-", "*", "/", "^", "(", ")" };

#define GCD  OP[0]
#define LCM  OP[1]
#define ADD  OP[2]
#define SUB  OP[3]
#define MUL  OP[4]
#define DIV  OP[5]
#define POW  OP[6]
#define OBR  OP[7]
#define CBR  OP[8]

typedef struct stk {
	int value;
	stk* prev;
} stk;

typedef struct ops {
	const char* op;
	ops* prev;
} ops;

void unexpected_symbol(const char* str, char* s) {
	printf("unexpected symbol:\n");
	printf("%s\n", str);
	char* e = (char*)str;
	while (e != s) {
		printf("~");
		e++;
	}
	printf("^\n");
}

stk* stk_push(stk* st, int n) {
	stk* x = (stk*)malloc(sizeof(stk));
	x->value = n;
	x->prev = st;
	st = x;
	return st;
}

stk* stk_operate(stk* st, const char* s) {
	stk* x = (stk*)malloc(sizeof(stk));
	x->value = 0;
	x->prev = st->prev->prev;
	int a = st->prev->value;
	int b = st->value;
	if (s == ADD) {
		x->value = a + b;
	}
	else if (s == SUB) {
		x->value = a - b;
	}
	else if (s == MUL) {
		x->value = a * b;
	}
	else if (s == DIV) {
		x->value = a / b;
	}
	else if (s == POW) {
		x->value = pow(a, b);
	}
	else if (s == GCD) {
		x->value = euclid_binary(a, b);
	}
	else if (s == LCM) {
		x->value = (a * b) / euclid_binary(a, b);
	}
	free(st);
	st = x;
	return st;
}

const char* get_id(char** s) {
	char* id = (char*)malloc(sizeof(char) * 100);
	int i = 0;
	while (**s != ' ' && **s != '\0') {
		if (*(*s + 1) == '(') {
			id[i++] = (char)**s;
			break;
		}
		id[i++] = (char)**s;
		(*s)++;
	}
	if (id) {
		id = (char*)realloc(id, sizeof(char) * i);
		id[i] = '\0';
	}
	return id;
}

const char* det_operation(char** s) {
	switch (**s) {
	case '+':
		return ADD;
	case '-':
		return SUB;
	case '*':
		return MUL;
	case '/':
		return DIV;
	case '^':
		return POW;
	case '(':
		return OBR;
	case ')':
		return CBR;
	default:
		const char* id = get_id(s);
		for (int i = 0; i < opcount; i++) {
			if (!strcmp(id, OP[i])) return OP[i];
		}
		return NULL;
	}
}

int rpn_calculate(const char* str) {
	char* s = (char*)str;
	stk* stack = (stk*)malloc(sizeof(stk));
	stack = NULL;
	while (*s != '\0') {
		if (IS_DIGIT(*s)) {
			stack = stk_push(stack, strtol(s, &s, 10));
		}
		else if (IS_SIGN(*s)) {
			if (stack && stack->prev) {
				const char* op = det_operation(&s);
				if (!op) {
					unexpected_symbol(str, s - 1);
					stack = NULL;
					break;
				}
				stack = stk_operate(stack, op);
			}
			else {
				printf("not enough operands\n");
				stack == NULL;
				break;
			}
			if (*s != '\0') s++;
		}
		else if (*s == ' ') {
			s++;
		}
		else {
			unexpected_symbol(str, s);
			stack = NULL;
			break;
		}
	}
	if (stack) {
		if (stack->prev) {
			printf("too many operands\n");
		}
		else {
			return stack->value;
		}
	}
	return NULL;
}

ops* ops_push(ops* st, const char* a) {
	ops* x = (ops*)malloc(sizeof(ops));
	x->op = a;
	x->prev = st;
	if (!st) {
		x->prev = NULL;
	}
	st = x;
	return st;
}

ops* ops_pop(ops* st) {
	ops* x = st->prev;
	ops* y = st;
	if (!x) return NULL;
	while (x) {
		y->op = x->op;
		if (!x->prev) {
			y->prev = NULL;
			break;
		}
		y = x;
		x = x->prev;
	}
	return st;
}

char* string_add(int* i, char* str, const char* a) {
	const char* op1 = a;
	if (str[(*i) - 1] != ' ') str[(*i)++] = ' ';
	while (*op1 != '\0') {
		str[(*i)++] = (char)*op1;
		op1++;
	}
	return str;
}

char* rpn_convert(const char* str) {
	char* s = (char*)str;
	char* result = (char*)malloc(sizeof(char) * 100);
	int i = 0;
	const char* op1;
	ops* stack = (ops*)malloc(sizeof(ops));
	stack = NULL;
	while (*s != '\0') {
		if (IS_DIGIT(*s)) {
			if (*s != str[0] && result[i - 1] && !IS_DIGIT(result[i - 1]) && result[i - 1] != ' ') {    //IS_SIGN(result[i - 1])) {
				result[i++] = ' ';
			}
			result[i++] = *s;
		}
		else if (IS_SIGN(*s)) {
			const char* op = det_operation(&s);
			if (!op) {
				unexpected_symbol(str, s);
				return NULL;
			}
			if (IS_DIGIT(*(s-1)) && op != OBR && op != CBR) result[i++] = ' ';
			if (!stack || (op == GCD || op == LCM) || op == OBR) {
				stack = ops_push(stack, op);
			}
			else if (op == CBR) {
				while (stack) {
					if (stack->op == OBR) {
						stack = ops_pop(stack);
						break;
					}
					else {
						result = string_add(&i, result, stack->op);
						stack = ops_pop(stack);
					}
				}
			}
			else if (op == ADD || op == SUB) {
				while (stack && stack->op != OBR) {
					result = string_add(&i, result, stack->op);
					stack = ops_pop(stack);
				}
				stack = ops_push(stack, op);
			}
			else if (op == POW) {
				while (stack && (stack->op == GCD || stack->op == LCM)) {
					result = string_add(&i, result, stack->op);
					stack = ops_pop(stack);
				}
				stack = ops_push(stack, op);
			}
			else {
				while (stack && stack->op != ADD && stack->op != SUB && stack->op != OBR) {
					result = string_add(&i, result, stack->op);
					stack = ops_pop(stack);
				}
				stack = ops_push(stack, op);
			}
		}
		else if (*s == ' ' && IS_DIGIT(*(s - 1))) {
			result[i++] = ' ';
		}
		else if (*s != ' ') {
			unexpected_symbol(str, s);
			return NULL;
		}
		s++;
	}
	while (stack) {
		if (stack->op == OBR || stack->op == CBR) {
			printf("exception with brackets\n");
			return NULL;
		}
		result = string_add(&i, result, stack->op);
		stack = ops_pop(stack);
	}
	free(stack);
	if (result) {
		result = (char*)realloc(result, sizeof(char) * (i));
		result[i] = '\0';
	}
	return result;
}


int main() {
	while (true) { 
		char s[100];
		std::cout << "input: ";
		std::cin.getline(s, 100);
		if (!strcmp(s,"stop")) {
			break;
		}
		if (s[0] != '\0') {
			char* c = rpn_convert(s);
			if (c) {
				std::cout << "output: " << c << std::endl;
				std::cout << "result: " << rpn_calculate(c) << std::endl;
			}
		}
		else std::cout << std::endl;
	}
}