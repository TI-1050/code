#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll C[110][110];

int main() {
	C[0][0] = 1;
	for (int i = 1; i < 110; ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; ++j)
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	}
	int n;
	cin >> n;
	ll res = 0;
	for (int i = n; i <= 12; ++i) {
		res += C[13][i] * (1 << (13 - i));
	}
	res = 1ll * 20 * (1 << n) * 13 * res;
	cout << res << endl;
}
