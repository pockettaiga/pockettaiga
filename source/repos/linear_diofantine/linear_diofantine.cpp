#include "euclid_extended.h"

int linear_diofantine(const int* a, int* x, int n, int b) {
	int k = 1;
	int t = extended_euclid(a[0], a[1], x, x + 1);
	for (int i = 2; i < n; ++i) {
		t = extended_euclid(t, a[i], &k, x + i);
		for (int j = 0; j < i; ++j) {
			x[j] *= k;
		}
		k = 1;
	}
	if (b % t != 0) {
		return 1;
	}
	if (b > 1) {
		for (int i = 0; i < n; i++) {
			x[i] *= b / t;
		}
	}
	return 0;
}

#include <iostream>
int main() {
	int n;
	int b;
	std::cout << "n: ";
	std::cin >> n;
	std::cout << "b: ";
	std::cin >> b;
	int* a = new int[n];
	int* x = new int[n];
	for (int i = 0; i < n; i++) {
		std::cout << "a" << i + 1 << ": ";
		std::cin >> a[i];
		x[i] = 1;
	}
	int d = linear_diofantine(&a[0], &x[0], n, b);
	std::cout << d << std::endl;
	if (d == 0) {
		for (int i = 0; i < n; i++) {
			std::cout << "x" << i + 1 << "=" << x[i] << "  ";
		}
	}
	return 0;
}