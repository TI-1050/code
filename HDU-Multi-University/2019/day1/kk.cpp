#include <bits/stdc++.h>
using namespace std;

int main() {
	int res = 0;
	int n, m; cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			res += __gcd(i, j);
		}
	}
	cout << res << endl;
	return 0;
}
