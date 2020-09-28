#include <bits/stdc++.h>
using namespace std;
const int N = 1e7 + 10;
int n, f[N];

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d", &n);
		memset(f, 0, sizeof f);
		for (int i = n; i >= 1; --i) {
			if (i * 2 > n) f[i] = 0;
			else {
				int t = 0;
				for (int j = 2; j <= 9; ++j) {
					int nx = i * j;
					if (nx > n) break;
					if (f[nx] == 0) t = 1;
				}
				f[i] = t;
			}
		}
		puts(f[1] ? "YES" : "NO");
	}
	return 0;
}
