#include <stdio.h>
#define DELTA .00001

double pow1(double, unsigned int);
long fact(unsigned int);
double sin1(double);
double cos(int);

/**
 * Return x ^ n
 * @param x Base
 * @param n Exponent
 * @return x ^ n
 */ 
double pow1(double x, unsigned int n) {
	if (n == 0) {
		return 1.0;
	} else if (n == 1) {
		return (long)x;
	} else {
		double res = x;
		for (; n > 1; n--) {
			res *= x;
		}
		return res;
	}
}

/**
 * Return n!
 * @param n The number
 * @return n!
 */ 
long fact(unsigned int n) {
	if (n == 0 || n == 1) {
		return 1;
	} else {
		long fact = 1;
		for (int i = 1; i <= n; i ++) {
			fact *= i;
		}
		return fact;
	}
}

/**
 * Return sin(x)
 * @param x The angle (in radiants)
 * @return sin(x)
 */ 
double sin1(double x) {
	int i = 3, sign = -1;
	double approx1 = x, approx2, difference;
	do {
		approx2 = approx1;
		approx1 = approx2 + (pow1(x, i)/fact(i) * sign);
		difference = approx1 - approx2;
		if (difference < 0) {
			difference *= -1;
		}
		i += 2;
		sign *= -1;
	} while (difference > DELTA && i < 16);
	return approx1;
}

/**
 * Return cos(x)
 * @param x The angle (in radiants)
 * @return cos(x)
 */
double cos1(double x) {
	int i = 2, sign = -1;
	double approx1 = 1, approx2, difference;
	do {
		approx2 = approx1;
		approx1 = approx2 + (pow1(x, i)/fact(i) * sign);
		difference = approx1 - approx2;
		if (difference < 0) {
			difference *= -1;
		}
		i += 2;
		sign *= -1;
	} while (difference > DELTA && i < 16);
	return approx1;
}

int main() {
	printf("Test sin 1: sin(pi) = %f\n", sin1(3.141592));
	printf("Test sin 2: sin(pi/2) = %f\n", sin1(3.141592/2));
	printf("Test sin 3: sin(0) = %f\n", sin1(0));
	printf("Test cos 1: sin(pi) = %f\n", cos1(3.141592));
	printf("Test cos 2: sin(pi/2) = %f\n", cos1(3.141592/2));
	printf("Test cos 3: sin(0) = %f\n", cos1(0));
}
