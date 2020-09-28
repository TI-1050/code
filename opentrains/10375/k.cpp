#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair <int, int> 
#define fi first
#define se second
int n;
int cnt[110];
ll S;
__int128 T, W, x;

bool ok(ll need, int x) {
	vector <int> c(65, 0);
	vector <pii> vec;
	W = 0;
	for (int i = x; i >= 0; --i) {
		int a = cnt[i], b = n - cnt[i];
		if (a < b) swap(a, b);
		x = a;
		W += x * (1ll << x);
		
		
	}
}

void work() { 
	T = 0;  
	ll res = 0;
	for (int i = 60; i >= 0; --i) {
		if (T > S) {
			puts("-1"); 
			return;
		}
		if (ok(S - T, i - 1)) {
			x = cnt[i];
			T += x * (1ll << i);  	
		} else {
			x = n - cnt[i];
			T += x * (1ll << i); 
			res |= (1ll << i);
		}
	}
	if (T > S) res = -1;
	printf("%lld\n", res);
}

int main() {
	while (scanf("%d%lld", &n, &S) != EOF) {
		memset(cnt, 0, sizeof cnt);
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", &x);
			for (int i = 60; i >= 0; --i) {
				if ((x >> i) & 1) {
					++cnt[i];  
				}
			}
		}
		work();
	}
	return 0;
}
