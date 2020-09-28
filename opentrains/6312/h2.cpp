#include <bits/stdc++.h>
using namespace std;

typedef pair <int, int> pII;
#define fi first
#define se second
const int N = 1e5 + 10;
int n, k, a[N], b[N], pre[N], lst; 
vector <vector<pII>> qvec;
struct BIT {
	int a[N];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, int v) {
		for (; x < N; x += x & -x)
			a[x] += v;
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x)
			res += a[x];
		return res;
	}
	int query(int l, int r) {
		if (l > r) return 0;
		return query(r) - query(l - 1);
	}
}bit;

bool No() {
	for (int r = 1; r <= n; ++r) {
		for (auto &it : qvec[r]) {
			int &l = it.fi;
			int &w = it.se;
			int sum = bit.query(l, r);
			if (sum < w) return false;
		}
	}
	return true;
}

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		qvec.clear(); qvec.resize(n + 1);
		memset(b, 0, sizeof b);
		bit.init();
		lst = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			if (!a[i]) {
				bit.update(i, 1); 
				a[i] = -1;
				b[i] = 1;
			} else {
				bit.update(i, a[i]);
			}
		}
		for (int i = 1, l, r, v; i <= k; ++i) {
			scanf("%d%d%d", &l, &r, &v);
			qvec[r].push_back(pII(l, v)); 
		}
		if (!No()) {
			puts("Impossible");
			continue;
		}
		bit.init();
		lst = 0;
		for (int i = 1; i <= n; ++i) {
			bit.update(i, a[i]);
			if (b[i]) {
				pre[i] = lst;
				lst = i; 
			}
			for (auto &it : qvec[i]) {
				int l = it.fi, w = it.se;
				while (bit.query(l, i) < w) {
					a[lst] = 1;
					bit.update(lst, 2);
					lst = pre[lst];
				}
			}
		}
		for (int i = 1; i <= n; ++i)
			printf("%d%c", a[i], " \n"[i == n]);
	}
	return 0;
}
