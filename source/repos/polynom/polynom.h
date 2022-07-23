#define IS_SIGN(x)   (x == '-' || x == '+')
#define IS_DIGIT(x)  (x >= '0' && x <= '9')

typedef struct poly {
	int coeff;
	int exp;
	poly* next;
} poly;

enum poly_parseer { NUMBER, SIGN, X, EXP };

poly* monomial_build(int c, int e);

poly* poly_add_monomial(poly* p, poly* m);

poly* monomial_get(const char* str, char** e = NULL);

void exception_handle(const char* str, char* e);

poly* poly_get(const char* str, char** e);

void poly_print(const poly* p);

poly* poly_add(poly* m, poly* n);

poly* poly_mul(poly* m, poly* n);

void poly_free(poly* p);