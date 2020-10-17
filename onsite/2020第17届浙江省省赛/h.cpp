#include <bits/stdc++.h>

using namespace std;

using db = long double;

const db eps = 1e-6;
const db E9 = 3e9;
const int N = 5e6 + 10;

#define dbg(x...) do { cout << #x << " -> "; err(x); } while (0)
void err() { cout << endl; }
template <class T, class... Ts> 
void err(const T& arg, const Ts&... args) {
	cout << arg << ' '; err(args...);
}

int sgn(db x) {
	if (fabs(x) < eps) return 0;
	return x > 0 ? 1 : -1;
}

struct Hash {
	db a[N];
	int tot = 0;
	void init() { tot = 0; }
	int size() { return tot; }
	void add(db x) { a[++tot] = x; }
	void gao() {
		sort(a + 1, a + 1 + tot);
		tot = unique(a + 1, a + 1 + tot) - a - 1;
	} 
	int get(db x) {
		return lower_bound(a + 1, a + 1 + tot, x) - a;
	}
}hs;

struct Point {
	int x, y;
	
	Point() {}
	
	Point(int x, int y): x(x), y(y) {}

	void input() {
		scanf("%d %d", &x , &y);
	}
	
	Point operator - (const Point &b) const {
		return Point(x - b.x, y - b.y);
	}
	
	int operator ^ (const Point &b) const {
		return x * b.y - y * b.x;
	}
	
	int operator * (const Point &b) const {
		return x * b.x + y * b.y;
	}
}p[N];

struct Line {
	Point s, e;
	
	Line() {}
	
	Line(Point _s, Point _e) {
		s = _s, e = _e;
	}
	
	void input() {
		s.input();
		e.input();
		if (s.x > e.x) swap(s, e);
	}
	
	bool pointonseg(Point p) {
		return sgn((p - s) ^ (e - s)) == 0 && sgn((p - s) * (p - e)) <= 0;
	}
}e[N];

struct Seg {
	db l, r;
	
	Seg() {}
	
	Seg(db _l, db _r) {
		l = _l, r = _r;
	}
	
	bool operator < (const Seg &other) const {
		if (sgn(l - other.l)) return l < other.l;
		else return r < other.r;
	}
};

int n, m;
vector<Seg> vec, t;

db gao(Point p1, Point p2) {
	if (sgn(p1.x - p2.x) == 0) return p1.x;
	if (sgn(p1.y - p2.y) <= 0) {
		return E9;
	}
	db dy = p2.y - p1.y;
	db dx = p2.x - p1.x;
	db x = p1.x + dx / dy * (-1.0 * p1.y);
	return x;
}

int f[N];

int main() {
	int _T;
	scanf("%d", &_T);
	while (_T--) {
		hs.init();
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			p[i].input();
		}
		for (int i = 1; i <= m; ++i) {
			e[i].input();
		}
		vec.clear();
		for (int i = 1; i <= n; ++i) {
			t.clear();
			for (int j = 1; j <= m; ++j) {
				if (e[j].pointonseg(p[i])) {
					t.clear();
					t.push_back(Seg(-E9, E9));
					break;
				}
				db l = gao(p[i], e[j].s);
				db r = gao(p[i], e[j].e);
//				dbg(i, j, l, r);
				if (sgn(r - l) == 0) continue;
				if (sgn(l - E9) == 0) l = E9 * sgn(e[j].e.x - p[i].x);
				if (sgn(r - E9) == 0) r = E9 * sgn(e[j].s.x - p[i].x);
				if (sgn(r - l) < 0) swap(l, r);
//				dbg("2", i, j, l, r);
				t.push_back(Seg(l, r));
			}
			sort(t.begin(), t.end());
			if (t.empty()) continue;
			db l = t[0].l, r = t[0].r;
			for (auto it : t) {
				if (sgn(r - it.l) >= 0) r = max(r, it.r);
				else {
					vec.push_back(Seg(l, r));
					l = it.l, r = it.r;
				}
			}
			vec.push_back(Seg(l, r));
		}
		for (auto it : vec) {
			hs.add(it.l);
			hs.add(it.r);
//			dbg(it.l, it.r);
		}
		hs.gao();
		int sze = hs.size();
		for (int i = 0; i <= sze; ++i) {
			f[i] = 0;
		}
		for (auto it : vec) {
			int l = hs.get(it.l);
			int r = hs.get(it.r);
			f[l]++, f[r]--;
		}
		for (int i = 1; i <= sze; ++i) {
			f[i] += f[i - 1];
		}
		db res = 0;
		for (int i = 1; i < sze; ++i) {
			if (f[i] == n) {
				res += hs.a[i + 1] - hs.a[i];
			}
		}
		if (sgn(res - 1e9) >= 0) puts("-1");
		else printf("%.10Lf\n", res);
	}
	return 0;
}
