#include <bits/stdc++.h>
using namespace std;

#define N 50010
#define u32 unsigned int
int n, q;
u32 a[N][33];

struct Base {
	static const int L = 32;
	u32 a[L];
	Base() {
		memset(a, 0, sizeof a);
	}
	u32& operator [](int x) {
		return a[x];
	}
	u32 operator [](int x) const {
		return a[x];
	}
	void insert(u32 x) {
		for (int i = L - 1; i >= 0; --i) {
			if ((x >> i) & 1) {
				if (a[i]) x ^= a[i];
				else {
					a[i] = x;
					break;
				}
			}
		}
	}
	//判断当前线性基能否表示出x
	bool check(u32 x) {
		for (int i = L - 1; i >= 0; --i) {
			if ((x >> i) & 1) {
				if (a[i]) x ^= a[i];
				else return 0;
			}
		}
		return 1;
	}
	//线性基求交
	friend Base intersection(const Base &a, const Base &b) {
		Base ans = Base(), c = b, d = b;
		for (int i = 0; i <= L - 1; ++i) {
			u32 x = a[i];
			if (!x) continue;
			int j = i; u32 T = 0;
			for (; j >= 0; --j) {
				if ((x >> j) & 1) {
					if (c[j]) {
						x ^= c[j];
						T ^= d[j];   
					} else {
						break;
					}
				}
			}
			if (!x) ans[i] = T;
			else {
				c[j] = x;
				d[j] = T;
			}
		}
		return ans;
	}
};

struct SEG {
	Base t[N << 2];
	void build(int id, int l, int r) {
		if (l == r) {
			t[id] = Base(); 
			for (int j = 1; j <= a[l][0]; ++j) {
				t[id].insert(a[l][j]);
			}
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = intersection(t[id << 1], t[id << 1 | 1]);
	}
	bool query(int id, int l, int r, int ql, int qr, int x) {
		if (l >= ql && r <= qr) {
			return t[id].check(x);
		}
		int mid = (l + r) >> 1;
		if (ql <= mid && !query(id << 1, l, mid, ql, qr, x)) return 0;
		if (qr > mid && !query(id << 1 | 1, mid + 1, r, ql, qr, x)) return 0;
		return 1;
	}
}seg;

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%u", a[i]);
			for (int j = 1; j <= a[i][0]; ++j) {
				scanf("%u", a[i] + j);
			}
		}
		seg.build(1, 1, n);
		int l, r, x;
		while (q--) {
			scanf("%d%d%d", &l, &r, &x);
			puts(seg.query(1, 1, n, l, r, x) ? "YES" : "NO");
		}
	}
	return 0;
}
