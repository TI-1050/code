#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, l, r;
	cin >> n >> l >> r;
	int res = 0;
	for (int i = l; i <= r; ++i) {
		res += __gcd(n, i);
	}
	cout << res << endl;
	return 0;
}
