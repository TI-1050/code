#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
int n, m;

ll res;
struct SEG {
	struct node {
		ll Max, sum, lazy; 
		int cnt;
		node () {
			Max = sum = 0;
			cnt = 0;
			lazy = -1;
		}
		void add(ll x) {
			if (x > Max) {
				sum = 1ll * cnt * x;
				Max = x;
				lazy = x;	
			}
		}
		node operator + (const node &other) const {
			node res = node();
			res.cnt = cnt + other.cnt;
			res.Max = max(Max, other.Max);     
			res.sum = sum + other.sum;
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		if (l == r) {
			t[id] = node();
			t[id].Max = l;
			t[id].sum = l;
			t[id].cnt = 1;  
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void pushdown(int id) {
		ll &lazy = t[id].lazy; 
	    if (lazy != -1) {
			t[id << 1].add(lazy);
			t[id << 1 | 1].add(lazy);
			lazy = -1;
		}
	}
	void update(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr && t[id].Max < qr) { 
			res += 1ll * t[id].cnt * qr - t[id].sum;    
			t[id].add(qr); 
			return;
		}
		if (l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (qr > mid && t[id << 1].Max < qr) update(id << 1 | 1, mid + 1, r, ql, qr); 
		if (ql <= mid) update(id << 1, l, mid, ql, qr);
		t[id] = t[id << 1] + t[id << 1 | 1];
	} 
}seg;

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		seg.build(1, 1, n);
		for (int i = 1, l, r; i <= m; ++i) {
			scanf("%d%d", &l, &r);
			res = 0;
			seg.update(1, 1, n, l, r);
			printf("%lld\n", res);
		}
	}
	return 0;
}
