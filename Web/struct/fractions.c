#include <stdio.h>
#include <stdlib.h>

struct fraction* init(int, int);
void print(const struct fraction* const);
struct fraction* add(const struct fraction* const, const struct fraction* const);

struct fraction {
    int num, den;
};

struct fraction* init(int num, int den) {
    struct fraction* fraction = malloc(sizeof(struct fraction));
    if (fraction) {
        fraction -> num = num;
        fraction -> den = den;
    }
    return fraction;
}

void print(const struct fraction* const f) {
    printf("%d/%d", f -> num, f -> den);
}

struct fraction* add(const struct fraction* const f1, const struct fraction* const f2) {
    return init(
        f1 -> num * f2 -> den + f2 -> num *f1 -> den, 
        f1 -> den * f2 -> den
    );
}

int main() {
    int num, den;
    printf("Enter fraction 1 (numerator denominator): ");
    scanf("%d%d", &num, &den);
    struct fraction* f1 = init(num, den);
    printf("Enter fraction 2 (numerator denominator): ");
    scanf("%d%d", &num, &den);
    struct fraction* f2 = init(num, den);
    print(f1); printf(" + "); print(f2); printf(" = "); print(add(f1, f2)); printf("\n");
    return 0;
}