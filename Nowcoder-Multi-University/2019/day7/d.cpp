#include <bits/stdc++.h>
using namespace std;

int n, p;
int f(int x) {
	int res = 0;
	while (x) {
		++res;
		x /= 10;
	}
	return res;
}

int main() {
	while (scanf("%d%d", &n, &p) != EOF) {
		if (f(p) > n) {
			puts("T_T");
		} else {
			int need = n - f(p);
			printf("%d", p);
			for (int i = 1; i <= need; ++i) putchar('0');
			puts("");
		}
	}
	return 0;
}
