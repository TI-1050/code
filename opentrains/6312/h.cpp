#include <bits/stdc++.h>
using namespace std;

typedef pair <int, int> pII;
#define fi first
#define se second
const int N = 1e5 + 10;
int n, k, a[N], b[N];
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
	for (int l = 1; l <= n; ++l) {
		for (auto &it : qvec[l]) {
			int &r = it.fi;
			int &w = it.se;
			int sum = bit.query(l, r);
			if (sum < w) return false;
			w = (r - l + 1 - w) / 2;
		}
	}
	return true;
}

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		qvec.clear(); qvec.resize(n + 1);
		memset(b, 0, sizeof b);
		bit.init();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			if (!a[i]) a[i] = b[i] = 1;
			bit.update(i, a[i]);
		}
		for (int i = 1, l, r, v; i <= k; ++i) {
			scanf("%d%d%d", &l, &r, &v);
			qvec[l].push_back(pII(r, v));
		}
		if (!No()) {
			puts("Impossible");
			continue;
		}
		int lazy = 0; 
		priority_queue <pII> se;
		for (int i = 1; i <= n; ++i) {
			for (auto &it : qvec[i]) {
				se.push(pII(it.se + lazy, it.fi)); 
			}
			if (!b[i]) {
				lazy += a[i] == -1;
				continue;
			}	
			bit.update(i, -2);  
			++lazy;
			bool F = 1;
			while (!se.empty()) {
				pII tmp = se.top(); 
				if (tmp.fi < i) {
					se.pop(); 
					continue;
				} 
				if (tmp.se - lazy < 0) F = 0;
				break;
			}
			if (!F) bit.update(i, 2), --lazy;  
			else a[i] = -1;
		}
		for (int i = 1; i <= n; ++i)
			printf("%d%c", a[i], " \n"[i == n]);
	}
	return 0;
}
