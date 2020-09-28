#include <bits/stdc++.h>

using namespace std;

const int N = 10000;

char a[N][15];
int cnt[15], f[15], q[15];
int h[N];
int n, k, ans, flag, num;

void dfs(int t, int m, int p) {
	if (t > m) {
		int s = 0, r = 0, v = 0, y;
		for (int i = 1; i <= m; ++i) {
			if (a[num][f[i]] == 49)
				s += cnt[k - f[i]];
			for (int j = f[i - 1] + 1; j < f[i]; ++j)
				q[++r] = j;
		}
		for (int j = f[m] + 1; j <= k ; ++j)
			q[++r] = j;
		for (int i = 0; i < cnt[k - m]; ++i) {
			int x = i; y = 0;
			for (int j = r; j > 0; --j) {
				y += (x % 2) * cnt[k - q[j]];
				x = x / 2;
			}	
			v += h[s + y];
		}
		if (v == 1) flag = 0;
		return;
	}
	if (flag == 0) return;
	for (int i = p + 1; i <= k - (m - t); ++i) {
		f[t] = i; 
		dfs(t + 1, m, i);

	}
}

int main() {
	int T, t;
	char ch;
	scanf("%d", &T);
	cnt[0] = 1;
	for (int i = 1; i < 15; ++i) cnt[i] = cnt[i - 1] * 2;
	while (T--) {
		scanf("%d %d", &n, &k);
		scanf("%c", &ch);
		memset(h, 0, sizeof h);
		memset(f, 0, sizeof f);
		ans = 1;
		//while (cnt[ans] < n) ++ans;
		for (int i = 1; i <= n; ++i) {
			scanf("%s", a[i] + 1);
			t = 0;
			for (int j = 1; j <= k; ++j)
				t = t * 2 + a[i][j] - 48;
			h[t] = 1;
		}
		for (int i = 1; i <= n; ++i) {
			num = i;
			for (int j = ans; j <= k ; ++j) {
				if (j < k) flag = 1;
				else {
					ans = j;
				   	break;
				}
				dfs(1, j, 0);
				if (flag == 0) {
					ans = j;
				   	break;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
