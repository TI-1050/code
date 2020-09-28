#include <bits/stdc++.h>

using namespace std;

const int N = 1e2 + 10;

int n;
int a[N], b[N];
double res;

void gao(int pos, int A, int B, int C, double ans) {
	if (pos > n) {
		res = max(res, ans);
		return ;
	}
	if (A < n / 3) {
		gao(pos + 1, A + 1, B, C, ans + a[pos]);
	}
	if (B < n / 3) {
		gao(pos + 1, A, B + 1, C, ans + b[pos]);
	}
	if (C < n / 3) {
		gao(pos + 1, A, B, C + 1, ans + (a[pos] + b[pos]) * 0.5);
	}
}

int main() {
	while (cin >> n) {
		for (int i = 1; i <= n; ++i) cin >> a[i];
		for (int i = 1; i <= n; ++i) cin >> b[i];
		res = 0;
		gao(1, 0, 0, 0, 0);
		cout << res << endl;
	}
	return 0;
}
