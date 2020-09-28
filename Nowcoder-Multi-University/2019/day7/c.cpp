#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n; ll tot;
struct Hash {
	int a[N], cnt;
	void init() { cnt = 0; }
	void add(int x) { a[++cnt] = x; }
	void work() {
		sort(a + 1, a + 1 + cnt);
		cnt = unique(a + 1, a + 1 + cnt) - a - 1;
	}
	int get(int x) {
		return lower_bound(a + 1, a + 1 + cnt, x) - a;
	}
}hs;
struct node {
	int h, c, p;
	void scan() {
		scanf("%d%d%d", &h, &c, &p);
		hs.add(h);		
		tot += p; 
	}
}a[N];
vector <vector<node>> vec;

struct SEG {
	struct node {
		ll sum, num, base;
		node() {
			sum = num = base = 0; 
		}
		void add(ll x) {
			num += x;
			sum += base * x;
		}
		node operator + (const node &other) const {
			node res = node();
			res.sum = sum + other.sum;
			res.num = num + other.num;
			return res;
		}
	}t[10010];
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
	void update(int id, int l, int r, int pos, ll x) {
		if (l == r) {
			t[id].add(x);
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, x);
		else update(id << 1 | 1, mid + 1, r, pos, x);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	ll query(int id, int l, int r, ll k) {
		if (k <= 0) return 0;
		if (l == r) {
			return k * t[id].base;
		}
		int mid = (l + r) >> 1;
		if (t[id << 1].num >= k) {
			return query(id << 1, l, mid, k);
		} else {
			return t[id << 1].sum + query(id << 1 | 1, mid + 1, r, k - t[id << 1].num);
		}
	}
}seg;

int main() {
	while (scanf("%d", &n) != EOF) {
		tot = 0;
		hs.init();
		for (int i = 1; i <= n; ++i) a[i].scan();
		hs.work();
		vec.clear(); vec.resize(n + 1);
		for (int i = 1; i <= n; ++i) {
			vec[hs.get(a[i].h)].push_back(a[i]);
		}
		int m = 200;
		seg.build(1, 1, m);	
		ll fee = 0, res = INF;
		for (int i = 1; i <= n; ++i) {
			seg.update(1, 1, m, a[i].c, a[i].p); 
		}
		for (int i = hs.cnt; i >= 1; --i) {
			ll tmp = 0, now = 0;
			for (auto it : vec[i]) {
				now += it.p;
				tmp += 1ll * it.c * it.p; 
				seg.update(1, 1, m, it.c, -it.p);	
			}
			tot -= now;
			res = min(res, fee + seg.query(1, 1, m, tot - now + 1));
			fee += tmp;
		}	
		printf("%lld\n", res);
	}
	return 0;
}
