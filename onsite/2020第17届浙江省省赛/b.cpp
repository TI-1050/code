#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int n, C;
int a[N];

struct SEG {
	int t[N << 2];
	void build(int id, int l, int r) {
		t[id] = 0;
		if (l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void update(int id, int l, int r, int pos, int v) {
		if (l == r) {
			t[id] += v;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, v);
		else update(id << 1 | 1, mid + 1, r, pos, v);
		t[id] = max(t[id << 1], t[id << 1 | 1]);
	}
	int query(int id, int l, int r, int v) {
		if (l == r) return l;
		int mid = (l + r) >> 1;
		if (t[id << 1] >= v) return query(id << 1, l, mid, v);
		return query(id << 1 | 1, mid + 1, r, v);
	}
}seg;

int gao() {
	int m = 0;
	seg.build(1, 1, n);
	seg.update(1, 1, n, m + 1, C); m += 1;
	for (int i = 1; i <= n; ++i) {
		if (seg.t[1] < a[i]) {
			seg.update(1, 1, n, m + 1, C);
			m += 1;
		}
		int pos = seg.query(1, 1, n, a[i]);
		seg.update(1, 1, n, pos, -a[i]);
	}
	return m;
}

int gao1() {
	multiset <int> se;
	for (int i = 1; i <= n; ++i) {
		auto pos = se.lower_bound(a[i]);
		if (pos == se.end()) {
			se.insert(C);
			pos = se.lower_bound(a[i]);
		}
		int now = *pos - a[i];
		se.erase(pos);
		se.insert(now);
//		cout << now << endl;
	}
//	cout << "----\n";
//	for (auto &it : se)
//		cout << it << endl;
	return int(se.size());
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d", &n, &C);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		int A = gao();
		int B = gao1();
		printf("%d %d\n", A, B);
	}
	return 0;
}
