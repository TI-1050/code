#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int n, m, a[N];
map <int, int> mp;

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		mp.clear();
		for (int i = 1; i <= m; ++i) scanf("%d", a + i), ++mp[a[i]];
		sort(a + 1, a + 1 + m);
		int x = a[m], y = 0;
		for (auto &it : mp) y = max(y, it.second);
		int cnt = 0;
		if (x > y) swap(x, y);
		for (int i = 1; 1ll * i * i <= n; ++i) {
			if (n % i == 0) {
				int a = i, b = n / i;
				if (a >= x && b >= y) ++cnt;
				if (a != b) {
					swap(a, b);
					if (a >= x && b >= y) ++cnt; 
				}
			}
		}
		if (cnt > 1 || cnt == 0) puts("NO");
		else puts("YES"); 
	}
	return 0;
}
