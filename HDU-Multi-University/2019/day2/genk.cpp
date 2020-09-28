#include <bits/stdc++.h>
using namespace std;

int f[100010];

int main() {
	int n = 100000, q = 100000;
	printf("%d %d\n", n, q);
	f[1] = 1, f[2] = 1;
	for (int i = 1; i <= n; ++i) {
		if (i >= 2) {
			if (i <= 44) f[i] = f[i - 1] + f[i - 2];
			else f[i] = 1;
		}
		printf("%d%c", f[i], " \n"[i == n]); 
	}
	int a = (n + 1) / 2, b = 3 * (n + 1) / 4;
	for (int i = 1; i <= q; ++i) printf("%d %d\n", 1, 45);
	return 0;
}
