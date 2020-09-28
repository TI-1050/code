#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
#define M 65
const ll p = 1e9 + 7;
int n;
ll a[N];
int vis[N];

void add(ll &x, ll y) {
	x += y;
	if (x >= p) x -= p;
}

struct LB {
	ll d[M]; int id[M];
	void init() {
		memset(d, 0, sizeof d);
		memset(id, -1, sizeof id);
	}
	bool insert(ll val, int _id = 1) {
		for (int i = 63; i >= 0; --i) {
			if (val & (1ll << i)) {
				if (!d[i]) {
					id[i] = _id; 
					d[i] = val;
					break;
				}
				val ^= d[i];
			}
		}
		return val > 0;
	}
}A, B, BB;

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) vis[i] = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", a + i);
		}
		ll res = 0;
		ll two = 5e8 + 4;
		A.init();
		int nullity = 0; 
		for (int i = 1; i <= n; ++i) {
			if (!A.insert(a[i], i)) {
				++nullity;
				add(two, two);
			}
		}
		add(res, two * nullity % p);
		B.init();
		for (int i = 0; i <= 63; ++i) {
			if (~A.id[i]) {
				vis[A.id[i]] = 1;
			}
		}
		vector <ll> vec;
		for (int i = 1; i <= n; ++i) {
			if (!vis[i]) {
				B.insert(a[i], i);
			} else {
				vec.push_back(a[i]);
			}
		}
		int sze = (int)vec.size();
		for (int i = 0; i < sze; ++i) {
			BB = B;
			for (int j = 0; j < sze; ++j) {
				if (i != j) {
					BB.insert(vec[j]); 
				}
			}
			if (!BB.insert(vec[i])) {
				add(res, two);
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
