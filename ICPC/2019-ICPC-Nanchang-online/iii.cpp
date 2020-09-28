#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
int n, a[N];
ll sum[N];
int f[N], g[N];
int Sta[N], top;

struct SEG {
	struct node {
		ll Max, Min;
		node () {
			Min = INFLL;
			Max = -INFLL;
		}
		node (ll Max, ll Min) : Max(Max), Min(Min) {}
		node operator + (const node &other) const {
			node res = node();
			res.Max = max(Max, other.Max);
			res.Min = min(Min, other.Min);
			return res;
		}
	}t[N << 2], res;
	void build(int id, int l, int r) {
		if (l == r) {
			t[id] = node(sum[l], sum[l]);
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void query(int id, int l, int r, int ql, int qr) {
		if (ql > qr) {
			return;
		}
		if (l >= ql && r <= qr) {
			res = res + t[id];
			return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid) query(id << 1, l, mid, ql, qr);
		if (qr > mid) query(id << 1 | 1, mid + 1, r, ql, qr);
	}
}seg;

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		for (int i = 1; i <= n; ++i) {
			sum[i] = sum[i - 1] + a[i];
		}
		seg.build(1, 1, n);
		ll res = 0;

		a[0] = a[n + 1] = -INF;
		top = 0;
		Sta[++top] = 0;
		for (int i = 1; i <= n; ++i) {
			while (a[i] <= a[Sta[top]]) {
				--top;
			}
			f[i] = Sta[top];
			Sta[++top] = i;
		}
		
		top = 0;
		Sta[++top] = n + 1;
		for (int i = n; i >= 1; --i) {
			while (a[i] <= a[Sta[top]]) {
				--top;
			}
			g[i] = Sta[top];
			Sta[++top] = i;
		}
	//	for (int i = 1; i <= n; ++i) {
	//		printf("%d %d %d\n", i, f[i], g[i]);
	//	}
		for (int i = 1; i <= n; ++i) {
			if (a[i] == 0) {
				continue;
			} else if (a[i] < 0) {
				seg.res = SEG::node();
				ll x = 0, y = 0;	
				seg.query(1, 1, n, f[i], i);
				if (f[i] == 0) {
					x = max(x, seg.res.Max);
				} else {
					x = seg.res.Max;
				}
				seg.res = SEG::node();
				seg.query(1, 1, n, i, g[i] - 1);
				y = seg.res.Min;
				res = max(res, (y - x) * a[i]);
			} else {
				seg.res = SEG::node();
				ll x = 0, y = 0;
				seg.query(1, 1, n, f[i], i);
				if (f[i] == 0) {
					x = min(x, seg.res.Min);
				} else {
					x = seg.res.Min;
				}
				seg.res = SEG::node();
				seg.query(1, 1, n, i, g[i] - 1);
				y = seg.res.Max;
				res = max(res, (y - x) * a[i]);
			}
		}
			
		printf("%lld\n", res);
	}
	return 0;
}
