#include <bits/stdc++.h>
using namespace std;

#define N 50
#define ll long long
int n, k, a[N], vis[N];
ll fac[N];

bool check(int x, int now) {
	for (int i = 1; i <= n; ++i) vis[i] = 0;
	vis[now] = 1;
	for (int i = 1; i <= x; ++i) {
		int nx = now + a[i];
		if (nx < 1 || nx > n) return 0;
		if (vis[nx]) return 0;
		vis[nx] = 1;
		now = nx;
	}
	return 1;
}

ll work(int x) {
	ll res = 0;
	for (int i = 1; i <= n; ++i) {
		if (check(x, i)) {
			res += fac[n - x - 1];
		}
	}
	return res;
}

void out() {
	for (int i = 1; i <= n; ++i) {
		if (check(n - 1, i)) {
			vector <int> vec;
			int now = i;
			vec.push_back(now);
			for (int j = 1; j < n; ++j) {
				now += a[j];
				vec.push_back(now);
			}
			for (int j = 0; j < n; ++j)
				printf("%d%c", vec[j], " \n"[j == n - 1]);
			return;
		}
	}
}

int main() {
	ll fac[N]; fac[0] = 1;
	for (int i = 1; i <= 20; ++i)
		fac[i] = fac[i - 1] * i;
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; ++i) {
			ll tot = 0, now = 0;
			for (int j = -n + 1; j < n; ++j) {
				a[i] = j; 
				now = work(i);
				if (tot + now >= k) {
					k -= tot;
					break;
				} else {
					tot += now;
				}
			}	
		}
		for (int i = 1; i < n; ++i)
			printf("%d%c", a[i], " \n"[i == n - 1]);
		out();
	}
	return 0;
}
