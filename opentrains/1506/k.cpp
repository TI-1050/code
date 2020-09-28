#include <bits/stdc++.h>
using namespace std;

#define N 2000010
int n, t, a[N];

void DFS(int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	for (int i = l; i <= mid; ++i)
		swap(a[i], a[i + mid - l + 1]);
	DFS(l, mid); DFS(mid + 1, r);
}

int main() {
	while (scanf("%d%d", &n, &t) != EOF) {
		n = 1 << n;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		t %= 2;
		if (t) DFS(1, n);
		for (int i = 1; i <= n; ++i) printf("%d%c", a[i], " \n"[i == n]);
	}
	return 0;
}
