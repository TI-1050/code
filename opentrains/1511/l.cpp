#include <bits/stdc++.h>

using namespace std;

const int N = 5e3 + 10;

int n, m, k;
char s[N], t[N];
int w[N][N], f[N << 1], remind[N << 1];

int main() {
	int _T;
	scanf("%d", &_T);
	while (_T--) {
		scanf("%d %d %d", &n, &m, &k);
		scanf("%s", s + 1);
		scanf("%s", t + 1);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				w[i][j] = (s[i] != t[j]);
			}
		}
		for (int i = 0; i < (N << 1); ++i) {
			f[i] = 0, remind[i] = 0;
		}
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				int sub = i - j + N;
				f[sub]++;
			   	remind[sub] += w[i][j];
				int &L = f[sub], &W = remind[sub];
				while (L > 0 && W > k) {
					L--;
					W -= w[i - L][j - L];
				}
				res = max(res, L);
			}
		}
		printf("%d\n", res);
	}	
	return 0;
}
