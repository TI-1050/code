#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 10;
int n, a[N]; ll S[N], Min[2];

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d", &n);
		S[0] = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			S[i] = S[i - 1] + a[i];
		}
		ll res = -1e18;
		Min[0] = 0;
		Min[1] = 1e18;
		for (int i = 1; i <= n; ++i) {
			res = max(res, S[i] - Min[(i & 1) ^ 1]);
			Min[i & 1] = min(Min[i & 1], S[i]);
		}
		printf("%lld\n", res);
	}
	return 0;
}
