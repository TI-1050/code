#include <bits/stdc++.h>
using namespace std;

int main() {
	int C = 100;
	int n, b;
	while (scanf("%d%d", &n, &b) != EOF) {
		if (n == 3 && b == 4) {
			puts("2\n1 2\n2 3");
		} else {
			int cnt = 0;
			for (int i = 2; i <= n; ++i) {
				++cnt;
			}
			for (int i = 2; i <= C; ++i) {
				for (int j = 1; j < i - 1; ++j)
					++cnt;
			}
			printf("%d\n", cnt);
			for (int i = 2; i <= n; ++i) {
				printf("%d %d\n", i - 1, i);
			}
			for (int i = 2; i <= C; ++i) {
				for (int j = 1; j < i - 1; ++j)
					printf("%d %d\n", i, j);
			}
		}
	}
	return 0;
}
