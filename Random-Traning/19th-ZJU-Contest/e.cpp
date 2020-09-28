#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 110
int n, a[N], b[N];
bool ok() {
	ll tot = 0;
	for (int i = n; i >= 1; --i) {
		if (b[i] >= a[i]) {
			tot += b[i] - a[i];
		} else {
			tot += b[i] - a[i];
			if (tot < 0) {
				return false;
			}
		}
	}
	return true;
}

int main() {
	int T; cin >> T;
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", b + i);
		}
		puts(ok() ? "Yes" : "No");
	}
	return 0;
}
