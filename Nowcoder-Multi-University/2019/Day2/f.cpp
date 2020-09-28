#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define N 40

int n;
ll ans;
int mp[N][N];
map <int, int> used;

void DFS(int S, int x, ll v) {
	used[S] = 1;
	for (int i = x; i < n; ++i) {
		if (!((S >> i) & 1)) {
			continue;
		}
		for (int j = i + 1; j < n; ++j) {
			if (((S >> j) & 1)) {
				continue;
			}
			int tS = S;
			ll tv = v;
			for (int o = 0; o < n; ++o) {
				if (o == i || o == j) {
					continue;
				}
				if ((S >> o) & 1) {
					tv += mp[o + 1][i + 1];
					tv -= mp[o + 1][j + 1];
				} else {
					tv += mp[o + 1][j + 1];
					tv -= mp[o + 1][i + 1];
				}
			}
			tS -= (1 << i);
			tS += (1 << j);
			ans = max(ans, tv);
			if (used[tS] == 0) 
			DFS(tS, i + 1, tv);
		}
	}
}

int main() {
	used.clear();
	scanf("%d", &n);
	n <<= 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			scanf("%d", &mp[i][j]);
		}
	}
	int S = (1 << (n / 2)) - 1;
	ll tmp = 0;
	for (int i = 0; i < n; ++i) {
		if ((S >> i) & 1) {
			for (int j = 0; j < n; ++j) {
				if ((S >> j) & 1) {
					continue;
				}
				tmp += mp[i + 1][j + 1];
			}
		}
	}
	ans = tmp;
	used[S] = 1; 
	DFS(S, 0, tmp);
	printf("%lld\n", ans);
	return 0;
}
