#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair <int, int>
#define fi first
#define se second
#define N 2010
int n;
vector <vector<pii>> vec;
struct Hash {
	int a[N], cnt;
	void init() {
		cnt = 0;
	}
	void add(int x) {
		a[++cnt] = x;
	}
	void work() {
		sort(a + 1, a + 1 + cnt);
		cnt = unique(a + 1, a + 1 + cnt) - a - 1;
	}
	int get(int x) {
		return lower_bound(a + 1, a + 1 + cnt, x) - a;
	}
}hx, hy;  

struct node {
	int x, y, w;
	node() {}
	void scan() {
		scanf("%d%d%d", &x, &y, &w);
		hx.add(x);
		hy.add(y);
	}
}a[N];

struct SEG {
	struct node {
		//0表示前缀最大  1表示后缀最大 2表示区间最大和 sum表示区间和
		ll Max[3], sum;
		node() {
			Max[0] = Max[1] = Max[2] = sum = 0;
		}
		void add(ll w) {
			sum += w;
			Max[0] = Max[1] = Max[2] = max(0ll, sum);
		}
		node operator + (const node &other) const {
			node res = node();
			res.Max[0] = max(Max[0], sum + other.Max[0]);
			res.Max[1] = max(other.Max[1], Max[1] + other.sum);
			res.Max[2] = max(Max[2], other.Max[2]);
			res.Max[2] = max(res.Max[2], Max[1] + other.Max[0]);
			res.sum = sum + other.sum;
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void update(int id, int l, int r, int pos, ll w) {
		if (l == r) {
			t[id].add(w);
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, w);
		else update(id << 1 | 1, mid + 1, r, pos, w);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
}seg;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		hx.init(); hy.init();
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) a[i].scan();
		hx.work(); hy.work();
		vec.clear(); vec.resize(hx.cnt + 10); 
		for (int i = 1; i <= n; ++i) {
		//	cout << hx.get(a[i].x) << " " << hy.get(a[i].y) << endl;
			vec[hx.get(a[i].x)].push_back(pii(hy.get(a[i].y), a[i].w));
		}
		ll res = 0;
		for (int i = 1; i <= hx.cnt; ++i) {
			seg.build(1, 1, hy.cnt);
			for (int j = i; j <= hx.cnt; ++j) {
				for (auto it : vec[j]) {
					seg.update(1, 1, hy.cnt, it.fi, it.se);
				}	
				res = max(res, seg.t[1].Max[2]);		
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
