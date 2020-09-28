#include <bits/stdc++.h>
using namespace std;

#define N 10010
int n;

int main() {
	srand(time(NULL));
	char *s = "FB";
	while (scanf("%d", &n) != EOF) {
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			if (x % 15 == 0) {
				putchar('B');
			} else if (x % 3 == 0) {
				putchar('F');
			} else {
				putchar('B');
			}
		}
		puts("");
	}
	return 0;
}
