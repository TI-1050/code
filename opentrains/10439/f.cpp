#include <bits/stdc++.h>
using namespace std;

#define N 10010
int n;

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			if (x % 3 == 0 && x % 15) {
				putchar('F');
			} else if (x % 5 == 0) {
				putchar('B');
			}
		}
		puts("");
	}
	return 0;
}
