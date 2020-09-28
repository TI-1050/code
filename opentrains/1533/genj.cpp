#include <bits/stdc++.h>
using namespace std;

int main() {
	int n = 100000; cout << n << "\n";
	for (int i = 2; i <= n; ++i) {
		printf("%d %d\n", i - 1, i);
	}
	for (int i = 1; i <= n; ++i) {
		printf("%d%c", 1, " \n"[i == n]);
	}
	int q = 100000; cout << q << "\n";
	for (int i = 1; i <= 100000; ++i) {
		printf("U %d %d\n", i, i);
	}
	return 0;
}
