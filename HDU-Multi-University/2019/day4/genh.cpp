#include <bits/stdc++.h>
using namespace std;

int main() {
	cout << "3\n";
	for (int o = 1; o <= 3; ++o) {
		int n = 100000, m = 100000;
		printf("%d %d\n", n, m);
		for (int i = 1; i <= n; ++i) {
			printf("1000000%c", " \n"[i == n]);
		}
		for (int i = 1; i <= m; ++i) {
			printf("%d %d %d %d\n", 1, n, 1000000, 1);
		}
	}
	return 0;
}
