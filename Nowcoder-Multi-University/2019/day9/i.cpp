#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
	ll n, m; cin >> n >> m;
	for (int i = 20; i >= 0; --i) if ((m >> i) & 1) {
		printf("######"); cout << i << endl;
		for (int j = 1; j <= n; ++j) {
			int res = 0;
			if (((1ll * j * m) >> i) & 1) { 
				res = 1;
			}
			cout << j << " " << res << endl;
		}
	}
	return 0;
}
