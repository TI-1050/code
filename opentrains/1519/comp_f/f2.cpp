#include <bits/stdc++.h>
using namespace std;

const int N = 110 + 10;
int n, q, x[N], y[N];

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> x[i] >> y[i];
	cin >> q;
	int a, b, d;
	while (q--) {
		cin >> a >> b >> d;
		int res = 0;
		for (int i = 1; i <= n; ++i)
			if (abs(a - x[i]) + abs(b - y[i]) <= d)
				++res;
		cout << res << "\n";
	}
}
