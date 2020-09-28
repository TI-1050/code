#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, k, a[N], c[N];
int res;
int que[N];

void solve(int l, int r, int dep) {
	if (dep >= 3) return;
	if (r - l + 1 <=res) return;
	for (int i = l; i <= r; ++i) c[a[i]] = 0;
	for (int i = l; i <= r; ++i) ++c[a[i]];
	int lst = 0;
	que[++lst] = l - 1;
	bool F = 0;
	for (int i = l; i <= r; ++i) {
		if (c[a[i]] < k) {
			que[++lst] = i;
			F = 1;
		}
	}
	if (F == 0) {
		res = r - l + 1;
		return;
	}
	if (que[lst] != r) que[++lst] = r + 1;
	for (int i = 1; i < lst; ++i) 
		solve(que[i] + 1, que[i + 1] - 1, dep + 1);
}

int main() {
	while (scanf("%d%d%d", &n, &k, &k) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		res = 0;
		solve(1, n, 1);
		printf("%d\n", res); 	
	}
	return 0;
}
