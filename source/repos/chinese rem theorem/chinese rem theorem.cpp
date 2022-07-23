#include "euclid_extended.h"
#include "euclid.h"

//1
int chinese_rem(const int *a, const int *m, int n) {
	int d, x = 0; int m1; int M = m[0];
	for (int i = 1; i < n; ++i) {
		//for (int j = i + 1; j < n; ++j) {
		d = euclid_binary(m[i], M);
		if (d != 1) {
			return -1;
		}
		M *= m[i];
	}
	for (int i = 0; i < n; ++i) {
		m1 = mul_inverse((M / m[i]), m[i]);
		x += a[i] * (M / m[i]) * m1;
	}
	x %= M;
	if (x < 0) {
		x += M;
	}
	return x;
}

//2
int chinese_rem1(const int *a, const int *m, int n) {
	int d;
	for (int i = 0; i < (n - 1); ++i) {
		for (int j = i + 1; j < n; ++j) {
			d = euclid_binary(m[i], m[j]);
			if (d != 1) {
				return -1;
			}
		}
	}
	int k = 1; int l = 1;
	d = extended_euclid(m[0], m[1], &k, &l);
	int x = k * m[0] * a[1] + l * m[1] * a[0];
	int M = m[0] * m[1];
	for (int i = 2; i < n; ++i) {
		k = 1; l = 1;
		d = extended_euclid(M, m[i], &k, &l);
		x = k * M * a[i] + l * m[i] * x;
		M *= m[i];
	}
	x %= M;
	if (x < 0) {
		x += M;
	}
	return x;
}

#include <iostream>
int main() {
	int n;
	std::cout << "n: ";
	std::cin >> n;
	int* a = new int[n];
	int* m = new int[n];
	int M = 1;
	for (int i = 0; i < n; ++i) {
		std::cout << "a" << i + 1 << ", m" << i + 1 << ": ";
		std::cin >> a[i];
		std::cin >> m[i];
		M *= m[i];
	}
	int ans = chinese_rem1(&a[0], &m[0], n);
	std::cout << "x = " << ans << " (mod " << M << ") ";
	return 0;
}