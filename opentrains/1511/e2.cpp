#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 2e6 + 10;
const int INF = 0x3f3f3f3f;

int n, k;
char str[20];
int cnt[N];
int f[N];
int p[20];

inline int get(int x, int y) {
	return x / p[y] % 3;
}

int main() {
	p[0] = 1;
	for (int i = 1; i < 20; ++i) p[i] = p[i - 1] * 3ll;
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &k);
		int m = p[k];
		for (int i = 0; i < m; ++i) cnt[i] = f[i] = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%s", str + 1);
			int S = 0, tmp = 1;
			for (int j = 1; j <= k; ++j) {
				S = S + tmp * (str[j] - '0');
				tmp *= 3;
			}
			cnt[S]++;
		}
		for (int i = 0; i < k; ++i) {
			for (int S = 0; S < m; ++S) {
				if (get(S, i) == 2) {
					cnt[S] += cnt[S - p[i]] + cnt[S - p[i] * 2];
				}
			}
		}
		for (int S = 0; S < m; ++S) {
			if (cnt[S] <= 1) {
				f[S] = 0;
			} else {
				f[S] = INF;
				for (int i = 0; i < k; ++i) {
					if (get(S, i) == 2) {
						f[S] = min(f[S], max(f[S - p[i]], f[S - p[i] * 2]) + 1);		
					}
				}
			}
		}
		printf("%d\n", f[m - 1]);
	}
	return 0;
}
