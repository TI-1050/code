#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
int n, q;
struct node {
	int e, l, c;
	void scan() {
		scanf("%d%d%d", &e, &l, &c);
	}
}a[N];
vector <vector<int>> add, del;

struct SEG {
	struct node {
		ll sum, num;
		int base;
		node() {
			sum = num = 0;
		}
		void add(ll x) {
			sum += x * base;
			num += x;
		}
		node operator + (const node &other) const {
			node res = node();
			res.sum = sum + other.sum;
			res.num = num + other.num;
			return res;
		}
	}t[N << 2], res;
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			t[id].base = l;
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void update(int id, int l, int r, int pos, int x) {
		if (pos == 0) return;
		if (l == r) {
			t[id].add(x);
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, x);
		else update(id << 1 | 1, mid + 1, r, pos, x);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void query(int id, int l, int r, int ql, int qr) {
		if (ql > qr) return;
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
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase) {
		printf("Case #%d: ", kase);
		scanf("%d", &n);
		add.clear(); del.clear();
		add.resize(n + 10); del.resize(n + 10);
		for (int i = 1; i <= n; ++i) a[i].scan();
		scanf("%d", &q);
		for (int i = 1, S, T, t; i <= q; ++i) {
			scanf("%d%d%d", &t, &S, &T);
			add[S].push_back(t);
			del[T + 1].push_back(t);
		}		
		int m = 200000;
		ll res = 0;
		seg.build(1, 1, m);	
		set <int> se;
		int Fi = 0;
		for (int i = 1; i <= n; ++i) {
			for (auto it : add[i]) {
				if (se.empty()) {
					se.insert(it);
					Fi = it;  
				} else {
					auto pos = se.lower_bound(it);
					if (pos == se.begin()) {
						Fi = it;
						seg.update(1, 1, m, *pos - it, 1);
						se.insert(it);
					} else if (pos == se.end()) {
						--pos;
						seg.update(1, 1, m, it - *pos, 1);
						se.insert(it);
					} else {
						auto pos2 = pos;
						--pos2;
						seg.update(1, 1, m, it - *pos2, 1);
						seg.update(1, 1, m, *pos - it, 1);
						seg.update(1, 1, m, *pos - *pos2, -1);
						se.insert(it);
					}
				}
			}
			for (auto it : del[i]) {
				auto pos = se.lower_bound(it);
				auto nx = pos; ++nx;
				if (pos == se.begin()) {
					if (nx == se.end()) {
						Fi = 0;
					} else {
						Fi = *nx;
						seg.update(1, 1, m, *nx - *pos, -1);
					}
					se.erase(pos);
				} else if (nx == se.end()) {
					auto pre = pos; --pre;
					seg.update(1, 1, m, *pos - *pre, -1);
					se.erase(pos);
				} else {
					auto pre = pos; --pre;
					seg.update(1, 1, m, *pos - *pre, -1);
					seg.update(1, 1, m, *nx - *pos, -1);
					seg.update(1, 1, m, *nx - *pre, 1); 
					se.erase(pos);
				}
			}
		//	if (Fi == 0) continue;
			res += min(1ll * a[i].e + 1ll * a[i].l * Fi, 1ll * a[i].c);
			if (a[i].l == 0) continue;
			int t = ((a[i].c + a[i].l - 1) / a[i].l);    
			seg.res = SEG::node();
			//大于等于t的
			seg.query(1, 1, m, t, m);
			res += 1ll * a[i].c * seg.res.num;
			//小于t的
			seg.res = SEG::node();
			seg.query(1, 1, m, 1, t - 1);
			res += 1ll * seg.res.sum * a[i].l;
		}
		printf("%lld\n", res);
	}
	return 0;
}
