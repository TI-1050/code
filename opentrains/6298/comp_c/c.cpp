#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0)
void err() { cout << "\033[39;0m" << endl; }
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
ll n; int ans; 
void gao(ll n, int f) {
	if (f == 0) {
		ll pre = n / 2 + 1;
	//	dbg(pre, n, f);
		if (pre == 1) {
			ans = f;
			return;
		}
		gao(pre - 1, f ^ 1);
	} else {
		ll pre = n / 9 + 1;
	//	dbg(pre, n, f);
		if (pre == 1) {
			ans = f;
			return;
		}
		gao(pre - 1, f ^ 1);
	}
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%lld", &n);
		gao(n, 0);
		puts(ans ? "YES" : "NO");
	}
	return 0;
}
