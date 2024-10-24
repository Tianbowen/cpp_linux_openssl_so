#include<cstdio>

extern "C" {
	int TestAddFuc(int a, int b) {
		printf("Write Something\n");
		printf("%d + %d = %d\n", a, b, a + b);
		return a + b;
	}
}