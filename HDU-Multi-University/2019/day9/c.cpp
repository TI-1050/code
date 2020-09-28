#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define N 50

struct node {
	ll l, r;

	node() {}

	node(ll l, ll r): l(l), r(r) {}
};

ll gao0(const vector<node> &A, const vector<node> &B, ll limit) {
	ll res = 0;
	int p = B.size() - 1;
	for (auto &it : A) {
		while (p >= 0 && it.r + B[p].r >= limit) --p;
		res += (p + 1);
	}
	return res;
}

ll gao1(const vector<node> &A, const vector<node> &B, ll limit) {
	ll res = 0;
	int sze1 = A.size() - 1, sze2 = B.size() - 1, p = 0;
	for (int i = sze1; i >= 0; --i) {
		while (p <= sze2 && A[i].r + B[p].r < limit) ++p;
		res += sze2 - p + 1;
	}
	return res;
}

int n;
ll a[N];
vector<node> A, B;
vector<node> AA[10], BB[10];

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		A.clear(), B.clear();
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", a + i);
		}
		int m = n / 2;
		for (int S = 0; S < (1 << m); ++S) {
			ll tmp = 0;
			for (int i = 0; i < m; ++i) {
				if ((S >> i) & 1) {
					tmp += a[i + 1];
				}
			}
			A.push_back(node(tmp, 0));
		}
		m = n - m;
		for (int S = 0; S < (1 << m); ++S) {
			ll tmp = 0;
			for (int i = 0; i < m; ++i) {
				if ((S >> i) & 1) {
					tmp += a[i + 1 + n / 2];
				}
			}
			B.push_back(node(tmp, 0));
		}
		ll res = 0;
		ll p10 = 1;
		for (int o = 1; o <= 10; ++o) {
			for (auto &it : A) {
				AA[it.l % 10].push_back(node(it.l / 10, it.r));
			}
			for (auto &it : B) {
				BB[it.l % 10].push_back(node(it.l / 10, it.r));
			}

			for (int i = 0; i < 10; ++i) {
				//不进位
				res += gao0(AA[i], BB[(14 - i) % 10], p10);
				//进位
				res += gao1(AA[i], BB[(13 - i) % 10], p10);
			}

			A.clear(), B.clear();
			for (int i = 0; i < 10; ++i) {
				for (auto it : AA[i]) {
					A.push_back(node(it.l, it.r + i * p10));
				}
				AA[i].clear();
			}
			for (int i = 0; i < 10; ++i) {
				for (auto it : BB[i]) {
					B.push_back(node(it.l, it.r + i * p10));
				}
				BB[i].clear();
			}
			p10 *= 10ll;
		}
		printf("%lld\n", res);
	}
	return 0;
}
