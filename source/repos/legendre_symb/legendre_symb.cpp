#include <iostream>
#include "time.h"
#include "mod_pow.h"
int legendre_euler(int a, int p) {
	int x = mod_pow2(a, ((p - 1) / 2), p);
	if (a % p == 0) {
		return 0;
	}
	else if (x % p == 1) {
		return 1;
	}
	else {
		return -1;
	}
}

int legendre_sqr_bitwise(int a, int p) {
	int temp; int sign = 1; int j = 0;
	if (a % p == 0) {
		return 0;
	}
	if (a > p) {
		a %= p;
	}
	while ((a > 1) && (p > 1)) {
		if ((a & 1) == 1) {
			if (((p & 3) == 3) && ((a & 3) == 3)) {
				sign *= -1;
			}
			temp = p;
			p = a;
			a = temp;
			a %= p;
		}
		else if ((a & 1) == 0) {
			while ((a & 1) == 0) {
				a >>= 1;
				j++;
			}
			if (((j & 1) == 1) && (((p & 3) == 3) || ((p & 7) == 5))) {
				sign *= -1;
			}
		}
	}
	return (a * sign);
}

int main() {
	int p, a;
	std::cin >> a;
	std::cin >> p;
	std::cout << legendre_euler(a, p) << std::endl;
	std::cout << legendre_sqr_bitwise(a, p) << std::endl;
	clock_t time1, time2;
	time1 = clock();
	for (int i = 0; i < pow(10, 7); ++i) {
		legendre_euler(a, p);
	}
	time2 = clock();
	std::cout << (double)(time2 - time1) / CLOCKS_PER_SEC << std::endl;
	time1 = clock();
	for (int i = 0; i < pow(10, 7); ++i) {
		legendre_sqr_bitwise(a, p);
	}
	time2 = clock();
	std::cout << (double)(time2 - time1) / CLOCKS_PER_SEC;
}

/*int legendre_sqr(int a, int p) {
	int temp; int sign = 1;
	if ((a * a) % p == 0) {
		return 0;
	}
	if (a > p) {
		a %= p;
	}
	while ((a > 1) && (p > 1)) {
		if ((a & 1) != 0) {
			if ((p % 4 == 3) && (a % 4 == 3)) {
				sign *= -1;
			}
			temp = p;
			p = a;
			a = temp;
			a %= p;
		}
		else if ((a & 1) == 0) {
			while ((a & 1) == 0) {
				a /= 2;
			}
			if ((p % 8 == 3) || (p % 8 == 5)) {
				sign *= -1;
			}
		}
	}
	return (a * sign);
}*/