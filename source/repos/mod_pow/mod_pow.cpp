//возведение в степень mod m
#include <iostream>

int mod_pow1(int x, long y, int m) {
	if (x > m) {
		x %= m;
	}
	if (y == 0) {
		return 1;
	}
	if (y == 1) {
		return x % m;
	}
	else if ((y & 1) == 0) {
		return mod_pow1(x * x, y / 2, m) % m;
	}
	else {
		return (mod_pow1(x, y - 1, m) * x) % m;
	}
}

//алгоритм 2
int mod_pow2(int x, long y, int m) {
	int k = 1;
	if (x > m) {
		x %= m;
	}
	while (y) {
		if ((y & 1) != 0) {
			k *= (x % m);
			k %= m;
		}
		y >>= 1;
		x *= (x % m);
		x %= m;
	}
	return k % m;
}

int main()
{
	int x; long y; int m;
	std::cin >> x >> y >> m;
	std::cout << (mod_pow1(x, y, m)) << std::endl;
	std::cout << (mod_pow2(x, y, m)) << std::endl;
}