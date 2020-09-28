#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10;
int n, q, arr[N], S = (1 << 31) - 1; 

struct SEG {
	struct node {
		int Min, A, O, lazyA, lazyO;
		node() {}
		node(int x) {
			Min = A = O = x;
			lazyA = S;
			lazyO = 0;
		}
		node operator + (const node &r) const {
			node res = node(0);
			res.Min = min(Min, r.Min);
			res.A = A & r.A;
			res.O = O | r.O;
			return res;
		}
		void add(int And, int Or) {
			Min = Min & And | Or;
			A = A & And | Or;
			O = O & And | Or;
			lazyA = lazyA & And;
			lazyO = lazyO & And | Or;
		}
	}a[N << 2];
	void build(int id, int l, int r) {
		if (l == r) {
			a[id] = node(arr[l]);
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		a[id] = a[id << 1] + a[id << 1 | 1];
	}
	void pushdown(int id) {
		if (a[id].lazyA != S || a[id].lazyO) {
			a[id << 1].add(a[id].lazyA, a[id].lazyO);
			a[id << 1 | 1].add(a[id].lazyA, a[id].lazyO);
			a[id].lazyA = S;
			a[id].lazyO = 0;
		}
	}
	void updateA(int id, int l, int r, int ql, int qr, int val) {
		if (l >= ql && r <= qr && !((a[id].A ^ a[id].O) & (S ^ val))) {
			a[id].add(val, 0);
			return;
		}
		pushdown(id);
		int mid = (l + r) >> 1;
		if (ql <= mid) updateA(id << 1, l, mid, ql, qr, val);
		if (qr > mid) updateA(id << 1 | 1, mid + 1, r, ql, qr, val);
		a[id] = a[id << 1] + a[id << 1 | 1];
	}
	void updateO(int id, int l, int r, int ql, int qr, int val) {
		if (l >= ql && r <= qr && !((a[id].A ^ a[id].O) & val)) {
			a[id].add(S, val);
			return;
		}
		pushdown(id);
		int mid = (l + r) >> 1;
		if (ql <= mid) updateO(id << 1, l, mid, ql, qr, val);
		if (qr > mid) updateO(id << 1 | 1, mid + 1, r, ql, qr, val);
		a[id] = a[id << 1] + a[id << 1 | 1];
	}
	int query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) return a[id].Min;
		pushdown(id);
		int mid = (l + r) >> 1;
		int res = S;
		if (ql <= mid) res = min(res, query(id << 1, l, mid, ql, qr));
		if (qr > mid) res = min(res, query(id << 1 | 1, mid + 1, r, ql, qr));
		a[id] = a[id << 1] + a[id << 1 | 1];
		return res;
	}
}seg;

void Run() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", arr + i);
		seg.build(1, 1, n);
		scanf("%d", &q);
		char op[10]; int l, r, x;
		while (q--) {
			scanf("%s%d%d", op, &l, &r);
			if (op[0] == '?') {
				printf("%d\n", seg.query(1, 1, n, l, r));
			} else {
				scanf("%d", &x);
				if (op[0] == '&') seg.updateA(1, 1, n, l, r, x);
				else seg.updateO(1, 1, n, l, r, x);
			}
		}
	}
}

int main() {
	Run();
	return 0;
}
