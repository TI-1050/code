#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 50010
const ll p = 1e9 + 7;
int n, q, m;
int a[N][12];

template <class T1, class T2>
void add(T1 &x, T2 y) {
	x += y;
	if (x >= p) x -= p;
}
struct SEG {
	struct node {
		int a[11][11];
		node() {
			memset(a, 0, sizeof a);
		}
		void modify(int *b) {
			memset(a, 0, sizeof a);
			for (int j = 1; j <= m; ++j) {
				for (int i = j; i <= m && b[i] == 0; ++i) {
					a[i][j] = 1;
				}
				for (int i = j; i >= 1 && b[i] == 0; --i) {
					a[i][j] = 1;
				}
			}
		}
		node operator * (const node &other) const {
			node res = node();
			for (int i = 1; i <= m; ++i) {
				for (int j = 1; j <= m; ++j) {
					for (int k = 1; k <= m; ++k) {
						add(res.a[i][j], 1ll * a[i][k] * other.a[k][j] % p);
					}
				}
			}
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		if (l == r) {
			t[id].modify(a[l]);
			return;	
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] * t[id << 1 | 1];
	}
	void update(int id, int l, int r, int pos) {
		if (l == r) {
			t[id].modify(a[l]);
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos);
		else update(id << 1 | 1, mid + 1, r, pos);
		t[id] = t[id << 1] * t[id << 1 | 1];
	}
}seg;

int main() {
	while (scanf("%d%d%d", &n, &m, &q) != EOF) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%1d", a[i] + j);
			}
		}
		seg.build(1, 1, n);
		int op, x, y;
		while (q--) {
			scanf("%d%d%d", &op, &x, &y);
			if (op == 1) {
				a[x][y] ^= 1;
				seg.update(1, 1, n, x);
			} else {
				printf("%d\n", seg.t[1].a[x][y]);
			}
		}
	}
	return 0;
}
