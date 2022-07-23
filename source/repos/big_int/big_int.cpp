#include <iostream>
#include <cstring>
#include "big_int.h"

/*typedef struct big_int {
	unsigned int length;
	unsigned char* number;
	unsigned char sign = 1;
} big_int;*/

void big_int_print(const big_int* n) {
	unsigned char d = 0x80;
	int extr = 0;
	if (n->sign == 0) {
		printf("-");
	}
	if ((n->length == 1) && (n->number[0] == 0)) {
		printf("%c", '0');
	}
	for (; d; d >>= 1) {
		if ((n->number[n->length - 1] & d) ? 1 : 0) {
			break;
		}
		extr++;
	}
	d = 0x80 >> extr;
	for (; d; d >>= 1) {
		printf("%d", (n->number[n->length - 1] & d) ? 1 : 0);
	}
	for (int i = n->length - 2; i >= 0; i--) {
		d = 0x80;
		for (; d; d >>= 1) {
			printf("%d", (n->number[i] & d) ? 1 : 0);
		}
	}
	return;
}

big_int* big_int_get(const char* num_bin) {
	unsigned int num_length = strlen(num_bin);
	unsigned int len = num_length >> 3;
	if ((num_length & 7) > 0) {
		len++;
	}
	big_int* result = (big_int*)malloc(sizeof(big_int));
	if (result) {
		result->length = len;
		result->number = (unsigned char*)malloc(len);
		if(result->number) {
			if (num_bin[0] == '-') {
				result->sign = 0;
			}
			else {
				result->sign = 1;
			}
			for (int i = 0; i < len; i++) {
				unsigned char cont = 0;
				for (int j = 0; j < 8; j++) {
					if (num_bin[num_length - 1 - (i * 8 + j)] == '1') {
						cont |= (1 << j);
					}
				}
				result->number[i] = cont;
			}
		}
	}
	return result;
}

big_int* big_int_add(big_int* n1, big_int* n2) {
	if (n1->sign == 1 && n2->sign == 0) {
		big_int* a = big_int_get("0");
		big_int_assign(a, n2);
		a->sign = 1;
		return big_int_sub(n1, a);
	}
	else if (n1->sign == 0 && n2->sign == 1) {
		big_int* a = big_int_get("0");
		big_int_assign(a, n1);
		a->sign = 1;
		return big_int_sub(n2, a);
	}
	unsigned int len;
	if (n1->length < n2->length) {
		len = n2->length;
	}
	else {
		len = n1->length;
	}
	big_int* result = (big_int*)malloc(sizeof(big_int));
	if (result) {
		result->length = len;
		result->number = (unsigned char*)malloc(len);
		if (result->number) {
			unsigned char c = 0;
			unsigned char expand = 0;
			for (int i = 0; i < len; ++i) {
				unsigned char cont = 0;
				for (int j = 0; j < 8; ++j) {
					unsigned char a = 0, b = 0;
					if (n1->length > i) {
						a = (n1->number[i] & (1 << j) ? 1 : 0);
					}
					if (n2->length > i) {
						b = (n2->number[i] & (1 << j) ? 1 : 0);
					}
					c = ((a != b) ? 1 : 0);
					if (expand) {
						c ^= expand;
					}
					expand = ((a & b) || (expand && (a != b)));
					cont |= (c << j);
				}
				result->number[i] = cont;
			}
			if (expand) {
				result->length++;
				result->number = (unsigned char*)realloc(result->number, len + 1);
				result->number[result->length] = 1;
			}
			if (n1->sign == 0 && n2->sign == 0) {
				result->sign = 0;
			}
			return result;
		}
	}
	return 0;
}

void big_int_free(big_int* x) {
	free(x->number);
	free(x);
	return;
}

int big_int_assign(big_int* n1, const big_int* n2) {
	unsigned char* new_number = (unsigned char*)malloc(n2->length);
	if (new_number) {
		free(n1->number);
		n1->number = new_number;
		n1->length = n2->length;
		memcpy((void*)n1->number, (void*)n2->number, n2->length);
	}
	else return 1;
	return 0;
}

void big_int_swap(big_int* a, big_int* b) {
	unsigned int len_1 = a->length;
	big_int* temp = (big_int*)malloc(sizeof(big_int));
	if (temp) {
		temp->number = (unsigned char*)malloc(len_1);
	}
	big_int_assign(temp, a);
	big_int_assign(a, b);
	big_int_assign(b, temp);
	big_int_free(temp);
	return;
}

big_int* big_int_sub(big_int* n1, big_int* n2, int sign) {
	if (n1->sign != n2->sign) {
		big_int* a = big_int_get("0");
		big_int_assign(a, n2);
		a->sign = n1->sign;
		return big_int_add(n1, a);
	}
	if (n1->length < n2->length) {
		sign ^= 1;
		return big_int_sub(n2, n1, sign);
	}
	else if (n1->length == n2->length) {
		unsigned char check = 0x80;
		for (; check > 0; check >>= 1) {
			if (n1->number[n1->length - 1] & check ? 1 : 0) {
				break;
			}
			if (n2->number[n2->length - 1] & check ? 1 : 0) {
				sign ^= 1;
				return big_int_sub(n2, n1, sign);
			}
		}
	}
	unsigned int len = n1->length;
	big_int* result = (big_int*)malloc(sizeof(big_int));
	if (result) {
		result->length = len;
		result->number = (unsigned char*)malloc(len);
		if (result->number) {
			unsigned char reduce = 0;
			unsigned char c = 0;
			for (int i = 0; i < len; ++i) {
				unsigned char cont = 0;
				for (int j = 0; j < 8; ++j) {
					unsigned char a = 0, b = 0;
					if (n1->length > i) {
						a = (n1->number[i] & (1 << j) ? 1 : 0);
					}
					if (n2->length > i) {
						b = (n2->number[i] & (1 << j) ? 1 : 0);
					}
					c = (a != b ? 1 : 0);
					if (reduce) {
						c ^= reduce;
					}
					reduce = (((a == 0) && (b == 1)) || (reduce && (a == b)));
					cont |= (c << j);
				}
				result->number[i] = cont;
			}
			unsigned char d = 0xff;
			int extr = 0;
			for (int i = 0; i < result->length; ++i) {
				if ((result->number[result->length - 1 - i] & d) ? 1 : 0) {
					break;
				}
				extr++;
			}
			unsigned int len_new = result->length - extr;
			if (len_new > 0) {
				result->length = len_new;
			}
			else {
				result->length = 1;
			}
			if (result) {
				result->number = (unsigned char*)realloc(result->number, result->length);
			}
			result->sign = sign;
			if (n1->sign == 0 && n2->sign == 0) {
				result->sign ^= 1;
			}
		}

	}
	return result;
}

/*big_int* big_int_leftshift(big_int* n, int value) {
	big_int* result = big_int_get("0");
	for (int i = 0; i < value; i++) {
		unsigned char extr = 0;
		for (int j = 0; j < n->length; j++) {
			unsigned char cont = 0;

		}
	}
	result->sign = n->sign;
	return result;
}*/

/*big_int* big_int_multiply(big_int* n1, big_int* n2) {
	big_int* result = big_int_get("0");
	big_int* a = big_int_get("0");
	big_int_assign(a, n2);
	a->sign = 1;
	while (a != big_int_get("0")) {
		a = big_int_sub(a, big_int_get("1"));
		result = big_int_add(result, n1);
	}
	result->sign = (n1->sign ^ n2->sign) ^ 1;
	return result;
}*/

int main() {
	const char* a = "100000000000000000000000";
	const char* b = "-11111111111111111111111";

	big_int* n = big_int_get(a);
	big_int* m = big_int_get(b);

	big_int_print(n);
	printf("\n");
	big_int_print(m);
	printf("\n");

	std::cout << "add: ";
	big_int* s = big_int_add(n, m);
	big_int_print(s);
	printf("\n");

	std::cout << "sub: ";
	big_int* d = big_int_sub(n, m);
	big_int_print(d);
	printf("\n");

	/*big_int* f = big_int_multiply(n, m);
	big_int_print(f);
	printf("\n");*/

	//big_int_print(big_int_add(s, d));
	//printf("\n");

	//big_int_assign(m, n);
	//big_int_print(m);

	big_int_free(n);
	big_int_free(m);
	big_int_free(s);
	big_int_free(d);
	//big_int_free(f);
	return 0;
}