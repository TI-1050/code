#include <bits/stdc++.h>
using namespace std;
#define N 100010
int n, m, D, a[N], b[N];

struct SEG {
	struct node {
		int sum, ls, rs;
		node() {
			sum = 0;
			ls = rs = -1;
		}
	}t[N * 60];
	int rt[N], cnt = 0;
	void init() {
		cnt = 0;
		t[0] = node();
		for (int i = 0; i <= n; ++i) rt[i] = 0;
	}
	void pushup(int id, int l, int r) {
		t[id].sum = 0;
		if (l != -1) t[id].sum += t[l].sum;
		if (r != -1) t[id].sum += t[r].sum;
	}
	void update(int &now, int pre, int l, int r, int pos) {
		int tmp = ++cnt; 
		t[tmp] = t[pre];
		if (l == r) {
			++t[tmp].sum;
			now = tmp; 
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(t[tmp].ls, t[pre].ls, l, mid, pos);
		else update(t[tmp].rs, t[pre].rs, mid + 1, r, pos);
		pushup(tmp, t[tmp].ls, t[tmp].rs);
	    now = tmp;	
	}
	int query(int now, int l, int r, int ql, int qr) {
		if (ql > qr) return 0;
		if (now == -1) return 0;
		if (l >= ql && r <= qr) return t[now].sum;
		int mid = (l + r) >> 1;
		int res = 0;
		if (ql <= mid) res += query(t[now].ls, l, mid, ql, qr);
		if (qr > mid) res += query(t[now].rs, mid + 1, r, ql, qr);
		return res;
	}
}seg;

int check(int p, int x, int L, int R) {
	int l = lower_bound(b + 1, b + 1 + b[0], p - x) - b;
	l = max(1, l);
	int r = upper_bound(b + 1, b + 1 + b[0], p + x) - b - 1;
	r = min(D, r);
	return seg.query(seg.rt[R], 1, D, l, r) - seg.query(seg.rt[L - 1], 1, D, l, r);
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		seg.init();
		D = 0; b[0] = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), b[++b[0]] = a[i]; 
		sort(b + 1, b + 1 + b[0]);
		b[0] = unique(b + 1, b + 1 + b[0]) - b - 1;
		D = b[0];
		for (int i = 1; i <= n; ++i) a[i] = lower_bound(b + 1, b + 1 + b[0], a[i]) - b;
		for (int i = 1; i <= n; ++i) {
			seg.update(seg.rt[i], seg.rt[i - 1], 1, D, a[i]);
		}
		int lst = 0;	
		int L, R, p, k;
		while (m--) {
			scanf("%d%d%d%d", &L, &R, &p, &k);
			L ^= lst;
			R ^= lst;
			if (L > R) swap(L, R);
			p ^= lst;
			k ^= lst;
			int l = 0, r = 1e6, res = -1;
			while (r - l >= 0) {
				int mid = (l + r) >> 1;
				if (check(p, mid, L, R) >= k) {
					res = mid;
					r = mid - 1;
				} else {
					l = mid + 1;
				}
			}
			printf("%d\n", lst = res);
		}
	}
	return 0;
}
