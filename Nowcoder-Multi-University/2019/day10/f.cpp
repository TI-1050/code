#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 10;
int n, m, r, cntx[N], cnty[N];
vector <vector<int>> vec;

struct SEG {
	int t[N << 2];
	void build(int id, int l, int r) {
		t[id] = 0;
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void update(int id, int l, int r, int x, int v) {
		if (l == r) {
			t[id] += v;
			return;
		}
		int mid = (l + r) >> 1;
		if (x <= mid) update(id << 1, l, mid, x, v);
		else update(id << 1 | 1, mid + 1, r, x, v);
		t[id] = max(t[id << 1], t[id << 1 | 1]); 
	}
}seg;

int main() {
	while (scanf("%d%d", &n, &r) != EOF) {
		vec.clear(); vec.resize(N);
		memset(cntx, 0, sizeof cntx);
		memset(cnty, 0, sizeof cnty);
		for (int i = 1, x, y; i <= n; ++i) {
			scanf("%d%d", &x, &y);
			++x, ++y;  
			vec[x].push_back(y);
			++cntx[x]; ++cnty[y]; 
		}
		m = 1e5 + 1;
		seg.build(1, 1, m);
		for (int i = 1; i <= m; ++i) {
			seg.update(1, 1, m, i, cnty[i] + cnty[i + r] + cnty[i + 2 * r]);
		} 
		int res = 0;
		for (int i = 1; i <= m; ++i) {
			for (auto o : {i, i + r, i + 2 * r}) {
				for (auto it : vec[o]) {
					for (auto x : {it, it - r, it - 2 * r}) {
						if (x >= 1) seg.update(1, 1, m, x, -1);
						else break;
					}
				}
			}
			int num = 0;
			for (auto it : {i, i + r, i + 2 * r}) {
				if (it <= m) num += cntx[it];
				else break;
			}
			res = max(res, num + seg.t[1]);
			for (auto o : {i, i + r, i + 2 * r}) {
				for (auto it : vec[o]) {
					for (auto x : {it, it - r, it - 2 * r}) {
						if (x >= 1) seg.update(1, 1, m, x, 1);
						else break;
					}
				}
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
