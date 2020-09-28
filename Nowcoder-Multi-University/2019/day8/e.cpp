#include <bits/stdc++.h>
using namespace std;

#define pii pair <int, int>
#define fi first
#define se second
const int N = 3e5 + 10;
int n, m, M, res;
int e[N][4]; 
pii Sta[N << 2]; int Top;
struct Hash {
	int a[N], cnt;
	void init() { cnt = 0; }
	void add(int x) { a[++cnt] = x; }
	void gao() {
		sort(a + 1, a + 1 + cnt);
		cnt = unique(a + 1, a + 1 + cnt) - a- 1;
	}
	int get(int x) { return lower_bound(a + 1, a + 1 + cnt, x) - a; }
}hs;
int fa[N], sze[N];
int find(int x) {
	return fa[x] == x ? x : find(fa[x]); 
}

struct SEG {
	vector <vector<int>> t;
	void init(int n) { t.clear(); t.resize(n * 4 + 10); }
	void ins(int id, int l, int r, int ql, int qr, int p) {
		if (l >= ql && r <= qr) {
			t[id].push_back(p);
			return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid) ins(id << 1, l, mid, ql, qr, p);
		if (qr > mid) ins(id << 1 | 1, mid + 1, r, ql, qr, p);
	}
	void gao(int id, int l, int r) {
		int T = Top;
		for (int &it : t[id]) {
			int x = find(e[it][0]), y = find(e[it][1]);
		//	cout << "edfe: " << x << " " << y << endl;
			if (x != y) {
				if (sze[x] > sze[y]) swap(x, y);
				Sta[++Top] = pii(x, y);
				fa[x] = y;
				sze[y] += sze[x];
			}
		}
		if (l == r) {
			if (find(1) == find(n)) {
				res += hs.a[l + 1] - hs.a[l];
			}
		} else {
			int mid = (l + r) >> 1;
			gao(id << 1, l, mid);
			gao(id << 1 | 1, mid + 1, r);
		}
		while (Top != T) {
			int x = Sta[Top].fi, y = Sta[Top].se; --Top;
		//	printf("%d %d %d %d\n", l, r, x, y);
			fa[x] = x;
			sze[y] -= sze[x];
		}
	}
}seg;

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		hs.init();
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d%d%d", e[i], e[i] + 1, e[i] + 2, e[i] + 3);
			hs.add(e[i][2]); hs.add(e[i][3]);
			hs.add(e[i][3] + 1);
		}
		hs.gao(); res = 0; Top = 0;
		M = hs.cnt;
		hs.a[M + 1] = hs.a[M] + 1;
		for (int i = 1; i <= n; ++i) fa[i] = i, sze[i] = 1;
		seg.init(M); 
		for (int i = 1; i <= m; ++i) {
			e[i][2] = hs.get(e[i][2]);
			e[i][3] = hs.get(e[i][3]);
			seg.ins(1, 1, M, e[i][2], e[i][3], i);
		}
		seg.gao(1, 1, M);
		printf("%d\n", res);
	}
	return 0;
}
