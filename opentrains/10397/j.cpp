#include <bits/stdc++.h>
using namespace std;

int main() {
	char S[10], T[10];
	while (scanf("%s%s", S + 1, T + 1) != EOF) {
		int A = 0, B = 0;
		for (int i = 1; i <= 6; ++i) {
			if (S[i] < T[i]) ++A;
			if (S[i] > T[i]) ++B;
		}
		printf("%d\n%d\n", A, B);
	}
	return 0;
}
