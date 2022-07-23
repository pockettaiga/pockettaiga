#ifndef BIG_INT_H
#define BIG_INT_H

typedef struct big_int {
	unsigned int length;
	unsigned char* number;
	unsigned char sign = 1;
} big_int;

void big_int_print(const big_int* n);

big_int* big_int_add(big_int* n1, big_int* n2);

void big_int_free(big_int* x);

int big_int_assign(big_int* n1, const big_int* n2);

void big_int_swap(big_int* a, big_int* b);

big_int* big_int_sub(big_int* n1, big_int* n2, int sign = 1);

#endif
