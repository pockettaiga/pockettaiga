#include <iostream>
#include "legendre_symb.h"

int square_comparison(int a, int p) {
	if (a > p) {
		a %= p;
	}
	int k = 0; int h = p - 1;
	while ((h & 1) == 0) {
		h >>= 1;
		k++;
	}
	if ((mod_pow2(a, (1 << (k - 1)) * h, p)) != 1) {
		return -1;
	}
	int r = k - 1;
	int b = 1;
	int c = 2;
	for (; c < (p - 1); c++) {
		if (legendre_sqr_bitwise(c, p) != 1) {
			break;
		}
	}
	while (r) {
		for (int i = 0; i < r; i++) {
			if (mod_pow2(pow(a, h) * pow(b, 2), (1 << i), p) == 1){
				r = i;
				break;
			}
			b *= mod_pow2(c, (1 << (k - r - 1)) * h, p);
			--r;
		}
	}
	int x1 = mod_pow2(a, ((h + 1) >> 1), p) * (b % p);
	x1 %= p;
	int x2 = (-x1) % p + p;
	return x1;
}

int main() {
	int a; int p;
	std::cin >> a >> p;
	int x = square_comparison(a, p);
	std::cout << x << std::endl;
	std::cout << mod_pow2(x, 2, p);
}
