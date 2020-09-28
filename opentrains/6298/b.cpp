#include <bits/stdc++.h>
using namespace std;
int a[110][110];

int main() {
	int n; 
	while (scanf("%d", &n) != EOF) {
		if (n == 1) puts("1\n1");
		else if (n >= 4) {
			printf("%d\n", n);
			int t = 0;
			for (int i = 2; i <= n; i += 2) a[1][++t] = i;
			for (int i = 1; i <= n; i += 2) a[1][++t] = i;
			for (int i = 2; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) {
					a[i][j] = a[i - 1][j] + n;
				}
			}
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j)
					printf("%d%c", a[i][j], " \n"[j == n]);
			}

		} else {
			puts("-1");
		}
	}
	return 0;
}
