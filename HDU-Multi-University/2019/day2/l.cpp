#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define INF 0x3f3f3f3f
int n, c, k, a[N], L[N], R[N], cnt[N]; 
vector <vector<int>> vec;

struct SEG {
	struct node {
		int Min, pos, lazy; 
		node(int pos = INF) {
			Min = INF;
			this->pos = pos;
			lazy = 0;
		}
		void add(int x) {
			Min += 1ll * x;
			lazy += x;
		}
		node (int Min, int pos) : Min(Min), pos(pos) {}
		node operator + (const node &other) const {
			node res = node();
			if (Min < other.Min) {
				res.Min = Min;
				res.pos = pos;
			} else if (Min > other.Min) {
				res.Min = other.Min;
				res.pos = other.pos;
			} else if (Min == other.Min) {
				res.Min = Min;
				if (pos < other.pos) {
					res.pos = pos;
				} else {
					res.pos = other.pos;
				}
			}
			return res;
		}
	}t[N << 2], res;
	void build(int id, int l, int r) {
		if (l == r) {
			t[id] = node(l);
			t[id].Min = 0;
			return;  
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];  
	}
	void pushdown(int id) {
		int &lazy = t[id].lazy;
		if (!lazy) return;
		t[id << 1].add(lazy);
		t[id << 1 | 1].add(lazy);
		lazy = 0;
	}
	void update(int id, int l, int r, int ql, int qr, int x) {
		if (ql > qr) return;
		if (l >= ql && r <= qr) {
			t[id].add(x);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, x);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, x);
		t[id] = t[id << 1] + t[id << 1 | 1]; 
	}
	void query(int id, int l, int r, int ql, int qr) {
		if (ql > qr) return;
		if (l >= ql && r <= qr) {
			res = res + t[id];
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) query(id << 1, l, mid, ql, qr);
		if (qr > mid) query(id << 1 | 1, mid + 1, r, ql, qr);
	}
}seg;

int main() {
	while (scanf("%d%d%d", &n, &c, &k) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		if (k == 1) {
			printf("%d\n", n);
			continue;
		}
		vec.clear(); vec.resize(c + 1);  
		for (int i = n; i >= 1; --i) {
			vec[a[i]].push_back(i); 
		} 
		for (int i = 1; i <= c; ++i) {
			cnt[i] = 0;
			L[i] = 1;
			R[i] = 0; 
		}
		seg.build(1, 1, n);  
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			int C = a[i];
			seg.update(1, 1, n, L[C], R[C], -1);  
			if (cnt[C] < k - 1) { 
				if (cnt[C] == 0) L[C] = 1;
				++cnt[C];
				R[C] = i;
			} else if (cnt[C] == k - 1){
			    L[C] = vec[C].back() + 1;	
				++cnt[C];
				R[C] = i; 
			} else {
				vec[C].pop_back();
				L[C] = vec[C].back() + 1;
				R[C] = i;
			}
			seg.update(1, 1, n, L[C], R[C], 1);
			seg.res = SEG::node();
			seg.query(1, 1, n, 1, L[C] - 1);
			if (seg.res.Min == 0) {
				res = max(res, i - seg.res.pos + 1);
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
