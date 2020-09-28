#include <bits/stdc++.h>
using namespace std;

#define N 110
int n, m, k;
char s[N];

int main() {
	while (scanf("%d%d%d", &n, &m, &k) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%s", s);
			for (int j = 1; j <= k; ++j) {
				for (int o = 0; o < m; ++o) {
					for (int q = 1; q <= k; ++q) {
						putchar(s[o]);
					}
				}
				puts("");
			}
		}
	}		
	return 0;
}
