//расширенный евклид ax + by = d

#include <iostream>

int extended_euclid(int a, int b, int* x, int* y) {
	int k = 0; int q; int M[4]; int temp; int d = 0;
	if ((a < 0) && (b > 0)) {
		*x *= -1; a = -a;
	}
	else if ((b < 0) && (a > 0)) {
		*y *= -1; b = -b;
	}
	if (a % b == 0) {
		*y *= -(a / b - 1);
		d = b;
		return d;
	}
	if (b % a == 0) {
		*x *= -(b / a - 1);
		d = a;
		return d;
	}
	q = a / b;
	int r = a % b;
	d = b;
	a = b; b = r;
	M[0] = q; M[1] = M[2] = 1; M[3] = 0;
	k++;
	while (r) {
		q = a / b;
		temp = M[0];
		M[0] = M[0] * q + M[1];
		M[1] = temp;
		temp = M[2];
		M[2] = M[2] * q + M[3];
		M[3] = temp;
		k++;
		r = a % b;
		a = b; b = r;
	}
	if (k&1) {
		*x *= -M[3]; *y *= M[1];
	}
	else {
		*x *= M[3]; *y *= -M[1];
	}
	return a;
}

int main() {
	int a; int b; int x = 1; int y = 1;
	std::cin >> a >> b;
	int d = extended_euclid(a, b, &x, &y);
	std::cout << a << "*" << x << " + " << b << "*" << y << " = " << d;
	return 0;
}

//обратный элемент в кольце остатков по модулю m 

int mul_inverse(int x, int m) {
	int a = 1; int b = 1;
	if (x > m) {
		x %= m;
	}
	int d = extended_euclid(x, m, &a, &b);
	if (d > 1) {
		return 0;
	}
	return a;
}

/*int main() {
	int x; int m;
	std::cin >> x >> m;
	int a = mul_inverse(x, m);
	std::cout << a;
}*/