#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int S = 1e3; 
const int N = 1e6 + 10;
ll res[N], f[N];
struct node {
	int p, q, n, id;
	node() {}
	node(int p, int q, int n, int id) : p(p), q(q), n(n), id(id) {}
};
vector <vector<node>> vec; 
ll sum_2(ll x) {
	return x * (x + 1) / 2; 
}
ll F(int n, int q) {
	ll res = 0;
	for (int i = 0, j = q, k = 0; i <= n; i += q, j += q, ++k) {
		res += k * (min(j, n + 1) - i);	
	}
	return res;
}

int main() {
	vec.clear(); vec.resize(N);
	int T; scanf("%d", &T);
	for (int i = 1, p, q, n; i <= T; ++i) {
		scanf("%d%d%d", &p, &q, &n);
		vec[q].push_back(node(p, q, n, i));
	}
	for (int q = 1; q < N; ++q) if (!vec[q].empty()) {
		if (q <= S) {
			f[0] = 0;
			for (int j = 1; j < N; ++j) {
				f[j] = f[j - 1] + j / q; 
			}
			for (auto it : vec[q]) {
				ll p = it.p % q, n = it.n;
				res[it.id] = p * (sum_2(n) - 1ll * q * f[n]);
			}
		} else {
			for (auto it : vec[q]) {
				ll p = it.p % q, n = it.n;
				res[it.id] = p * (sum_2(n) - 1ll * q * F(n, q));
			}
		}
	}
	for (int i = 1; i <= T; ++i) printf("%lld\n", res[i]);
	return 0;
}
