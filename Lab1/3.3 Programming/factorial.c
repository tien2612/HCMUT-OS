#include "factorial.h"

int factorial(const int aNumber) {
	long long int result = 1;
	for (int i = aNumber; i > 0; i--) {
		result *= i;
	}
	return result;
}
