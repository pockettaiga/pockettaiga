#include <iostream>
#include <stdio.h>
#include <cstring>
#include "polynom.h"

//#define IS_SIGN(x)   (x == '-' || x == '+')
//#define IS_DIGIT(x)  (x >= '0' && x <= '9')

//<errno.h>

/*typedef struct poly {
	int coeff;
	int exp;
	poly* next;
} poly;*/


//enum poly_parseer { NUMBER, SIGN, X, EXP };


void poly_free(poly* p) {
	poly* x;
	while (p != NULL) {
		x = p->next;
		free(p);
		p = x;
	}
	return;
}


poly* monomial_build(int c, int e) {
	poly* result = (poly*)malloc(sizeof(poly));
	result->coeff = c;
	result->exp = e;
	result->next = NULL;
	return result;
}


poly* poly_add_monomial(poly* p, poly* m) {
	poly* x = p;
	poly* y = NULL;
	poly* t = monomial_build(m->coeff, m->exp);
	while (x != NULL) {
		if (x->coeff == 0 && x->exp == 0) {
			x->coeff = m->coeff;
			x->exp = m->exp;
			break;
		}
		else if (x->exp == m->exp) {
			x->coeff += m->coeff;
			break;
		}
		else if (x->exp < m->exp) {
			if (x == p) {
				t->next = p;
				p = t;
			}
			else {
				t->next = x;
				y->next = t;
			}
			break;
		}
		else if ((x->exp > m->exp) && (x->next == NULL)) {
			x->next = t;
			break;
		}
		y = x;
		x = x->next;
	}
	return p;
}


poly* monomial_get(const char *str, char **e) {
	int exp, coeff;
	exp = coeff = 0;
	poly_parseer state = SIGN;
	int sign = 1;
	char* s = (char*)str;
	while (*s != '\0' && !((state == X || state == NUMBER) && IS_SIGN(*s))) {
		if (IS_SIGN(*s) && state == SIGN) {
			if (*s == '-') {
				sign *= -1;
				s++;
			}
			else {
				s++;
			}
		}
		else if (IS_DIGIT(*s)) {
			if (state == SIGN) {
				coeff = strtol(s, &s, 10) * sign;
				state = NUMBER;
			}
			else if (state == EXP) {
				exp = strtol(s, &s, 10);
				state = NUMBER;
			}
		}
		else if (*s == 'x' && (state == NUMBER || state == SIGN)) {
			exp = 1;
			if (state == SIGN) {
				coeff = sign;
			}
			state = X;
			s++;
		}
		else if (*s == '^' && state == X) {
			state = EXP;
			s++;
		}
		else {
			*e = s;
			return NULL;
		}
	}
	return monomial_build(coeff, exp);
}


void exception_handle(const char* str, char *e) {
	printf("Exception: ");
	if (str == e) {
		printf("empty string\n\n");
		return;
	}
	else if (*(e - 1) == '^') {
		printf("number expected");
	}
	else if (*(e - 1) == 'x') {
		printf("'^' or sign expected");
	}
	else if (IS_DIGIT(*(e - 1)) && *(e - 2) == '^') {
		printf("number or sign expected");
	}
	else {
		printf("'x' or number or sign expected");
	}
	printf("\n%s\n", str);
	char* s_except = (char*)str;
	while (s_except != e) {
		printf("~");
		s_except++;
	}
	printf("^\n\n");
}


poly* poly_get(const char* str, char** e) {
	if (str == NULL || *str == '\0') {
		*e = (char *)str;
		return NULL;
	}
	poly* result = monomial_build(0, 0);
	poly* m;
	char* s = (char*) str;
	while (*s != '\0') {
		if ((IS_SIGN(*s) && !(IS_SIGN(*(s-1)))) || s == str) {
			m = monomial_get(s, e);
			if (m) {
				result = poly_add_monomial(result, m);
			}
			else {
				poly_free(result);
				return NULL;
			}
		}
		s++;
	}
	*e = NULL;
	return result;
}


void poly_print(const poly* p) {
	if (p == NULL) {
		printf("NULL");
		printf("\n");
	}
	else {
		if (p->coeff == -1) {
			printf("-");
		}
		else if (p->coeff != 0 && p->coeff != 1) {
			printf("%d", p->coeff);
		}
		if (p->coeff != 0) {
			if (p->exp == 1) {
				printf("x");
			}
			else if (p->exp != 0) {
				printf("x^%d", p->exp);
			}
			else if (p->coeff == 1 || p->coeff == -1) {
				printf("1");
			}
		}
		if (p->coeff == 0 && p->next == NULL) {
			printf("0");
		}
		p = p->next;
		while (p != NULL) {
			if (p->coeff > 0 && p->coeff != 1) {
				printf("+%d", p->coeff);
			}
			else if (p->coeff < 0 && p->coeff != -1) {
				printf("%d", p->coeff);
			}
			else if (p->coeff == 1) {
				printf("+");
			}
			else if (p->coeff == -1) {
				printf("-");
			}
			if (p->coeff != 0) {
				if (p->exp == 1) {
					printf("x");
				}
				else if (p->exp != 0) {
					printf("x^%d", p->exp);
				}
				else if (p->coeff == 1 || p->coeff == -1) {
					printf("1");
				}
			}
			p = p->next;
		}
		printf("\n");
	}
	return;
}


poly* poly_add(poly* m, poly* n) {
	poly* x = m;
	poly* y = n;
	poly* result = monomial_build(0, 0);
	if (x == NULL || y == NULL) {
		return NULL;
	}
	while (x != NULL && y != NULL) {
		result = poly_add_monomial(result, x);
		result = poly_add_monomial(result, y);
		x = x->next;
		y = y->next;
	}
	return result;
}


poly* poly_mul(poly* m, poly* n) {
	poly* x = m;
	poly* y = n;
	poly* result = monomial_build(0, 0);
	if (x == NULL || y == NULL) {
		return NULL;
	}
	while (x != NULL) {
		while (y != NULL) {
			result = poly_add_monomial(result, monomial_build(x->coeff * y->coeff, x->exp + y->exp));
			y = y->next;
		}
		y = n;
		x = x->next;
	}
	return result;
}


int main() {
	const char* a = "+x^2-3+++----2x";
	const char* b = "10x-1+-+-+-+-2x^4";
	char* e;
	poly* p = poly_get(a, &e);
	if (e) exception_handle(a, e);
	poly* q = poly_get(b, &e);
	if (e) exception_handle(b, e);
	poly* s = poly_add(p, q);
	poly* m = poly_mul(p, q);
	
	printf("#1: ");
	poly_print(p);
	printf("\n");
	
	printf("#2: ");
	poly_print(q);
	printf("\n");

	printf("addition: ");
	poly_print(s);
	printf("\n");

	printf("multiplication: ");
	poly_print(m);
	printf("\n");
	
	poly_free(p);
	poly_free(q);
	poly_free(s);
	poly_free(m);
	return 0;
} 